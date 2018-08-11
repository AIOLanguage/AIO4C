


/**
 * Reset.
 */

void reset_assign_spider(aio_spider *spider) {
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    aio_assign_materials *materials = spider->get.assign_materials;
    reset_point_watcher(materials->watcher);
    materials->scope_type = AIO_ASSIGN_DECLARATION_SCOPE;
    materials->declaration_type = AIO_ASSIGN_UNDEFINED_DECLARATION;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free(materials->value);
    free_strings_in_list(materials->variable_data_list);
}

/**
 * Free spider.
 */

void free_assign_spider(aio_spider *spider) {
    aio_assign_materials *materials = spider->get.assign_materials;
    free_point_watcher(materials->watcher);
    free_strings_in_list(materials->variable_data_list);
    free_string_list(materials->variable_data_list);
    free(materials->value);
    free(materials);
    free(spider);
}

/**
 * Constructor.
 */

aio_spider *new_aio_assign_spider() {
    aio_spider *spider = calloc(1, sizeof(aio_spider));
    //Bind spider's functions:
    spider->reset = reset_assign_spider;
    spider->is_found_instruction = is_found_assign_instruction;
    spider->weave_instruction_for = weave_assign_instruction_for;
    spider->free = free_assign_spider;
    //Create materials:
    aio_assign_materials *materials = calloc(1, sizeof(aio_assign_materials));
    materials->watcher = new_point_watcher();
    materials->scope_type = AIO_ASSIGN_DECLARATION_SCOPE;
    materials->declaration_type = AIO_ASSIGN_UNDEFINED_DECLARATION;
    materials->variable_data_list = new_string_list();
    //Set materials:
    spider->get.assign_materials = materials;
    //Init start message:
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

/**
 * Searching.
 */

const aio_spider_message is_found_assign_instruction(const_string string_web, aio_spider *spider) {
    //Extract spider fields:
    const aio_assign_materials *materials = spider->get.assign_materials;
    const aio_assign_scope_type scope_type = materials->scope_type;
    point_watcher *watcher = materials->watcher;
    watcher->end_index++;
    //Prepare to scanning:
    const char last_symbol = string_web[watcher->end_index - 1];
    //Spider waits string data:
    if (watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(last_symbol)) {
            //Spider waiting:
            watcher->start_index++;
        } else {
            //Spider is ready for analysing:
            watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    //Spider works:
    if (watcher->mode == POINT_ACTIVE_MODE) {
        switch (scope_type) {
            case AIO_ASSIGN_DECLARATION_SCOPE:
                handle_declaration_scope(string_web, spider);
                break;
            case AIO_ASSIGN_EQUAL_SIGN_IN_SCOPE:
                handle_equal_sign_scope(string_web, spider);
                break;
            case AIO_ASSIGN_VALUE_SCOPE:
                handle_assign_scope(string_web, spider);
                break;
            case AIO_ASSIGN_WEAVING_SCOPE:
                break;
        }
    }
    return spider->message;
}

/**
 * Extra handlers:
 **/

void handle_declaration_scope(const_string string_web, aio_spider *spider) {
    //Extract materials:
    aio_assign_materials *materials = spider->get.assign_materials;
    aio_assign_variable_declaration_type declaration_type = materials->declaration_type;
    point_watcher *watcher = materials->watcher;
    //Check string web:
    const char last_symbol = string_web[watcher->end_index - 1];
    //If was word:
    if (is_space_or_line_break(last_symbol)) {
        string chunk = substring(string_web, watcher->start_index, watcher->end_index - 1);
        //Check conditions:
        const_boolean is_mutable_modifier = is_aio_mutable_modifier(string_web);
        const_boolean is_type = contains_aio_type_in_set(string_web);
        const_boolean is_variable_name = is_word(string_web) && can_use_name(string_web);
        switch (declaration_type) {
            case AIO_ASSIGN_UNDEFINED_DECLARATION:
                //Maybe string is the "mu" modifier?
                if (is_mutable_modifier) {
                    refresh_declaration_scope(spider, chunk, AIO_ASSIGN_WAS_MUTABLE_MODIFIER,
                                              AIO_SPIDER_FOUND_MATERIALS);
                }
                //Maybe string is a type?
                if (is_type) {
                    refresh_declaration_scope(spider, chunk, AIO_ASSIGN_IMMUTABLE, AIO_SPIDER_NOT_FOUND_MATERIALS);
                }
                //Maybe is a variable name?
                if (is_variable_name) {
                    refresh_declaration_scope(spider, chunk, AIO_ASSIGN_WILL_DEFINED, AIO_SPIDER_NOT_FOUND_MATERIALS);
                    //Change scope:
                    materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_IN_SCOPE;
                } else {
                    //Not a variable name:
                    //--------------------------------------------------------------------------------------------------
                    //찌꺼기 수집기 (Garbage collector):
                    free(chunk);
                }
            case AIO_ASSIGN_WAS_MUTABLE_MODIFIER:
                //Maybe string is a type?
                if (is_type) {
                    refresh_declaration_scope(spider, chunk, AIO_ASSIGN_IMMUTABLE, AIO_SPIDER_NOT_FOUND_MATERIALS);
                }
                //Maybe string is a variable name?
                if (is_variable_name) {
                    refresh_declaration_scope(spider, chunk, AIO_ASSIGN_WILL_DEFINED, AIO_SPIDER_NOT_FOUND_MATERIALS);
                    //Change scope:
                    materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_IN_SCOPE;
                } else {
                    //Not a variable name:
                    //--------------------------------------------------------------------------------------------------
                    //찌꺼기 수집기 (Garbage collector):
                    free(chunk);
                }
                //Mutable by value mode:
            case AIO_ASSIGN_MUTABLE:
                //Must be variable name:
                if (is_variable_name) {
                    refresh_declaration_scope(spider, chunk, AIO_ASSIGN_MUTABLE, AIO_SPIDER_FOUND_MATERIALS);
                    //Change scope:
                    materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_IN_SCOPE;
                } else {
                    throw_error("ASSIGN SPIDER invalid variable name!");
                }
            default:
                throw_error("ASSIGN SPIDER: Unreachable case!");
        }
    }
}

void refresh_declaration_scope(aio_spider *spider, string chunk, aio_assign_variable_declaration_type type,
                               aio_spider_message message) {
    //Extract materials:
    aio_assign_materials *materials = spider->get.assign_materials;
    string_list *variable_data_list = materials->variable_data_list;
    point_watcher *watcher = materials->watcher;
    //Change declaration type:
    materials->declaration_type = type;
    //Put "mu" modifier in list:
    add_string_in_list(variable_data_list, chunk);
    //Shift watcher:
    watcher->start_index = watcher->end_index;
    watcher->mode = POINT_PASSIVE_MODE;
    //Set message:
    spider->message = message;
}

void handle_equal_sign_scope(const_string string_web, aio_spider *spider) {
    aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *watcher = materials->watcher;
    const int start_scanning_index = watcher->start_index;
    const_boolean is_equal_sign_symbol = is_equal_sign(string_web[start_scanning_index]);
    if (is_equal_sign_symbol) {
        //Set value scope:
        materials->scope_type = AIO_ASSIGN_VALUE_SCOPE;
        //Shift start index to end index:
        watcher->start_index = watcher->end_index;
        watcher->mode = POINT_PASSIVE_MODE;
        //Set message:
        spider->message = AIO_SPIDER_FOUND_MATERIALS;
    } else {
        if (spider->message == AIO_SPIDER_FOUND_MATERIALS) {
            throw_error("ASSIGN SPIDER: invalid variable definition!");
        }
    }
}

void handle_assign_scope(const_string string_web, aio_spider *spider) {
    //Extract fields:
    aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *watcher = materials->watcher;
    //Check last symbol:
    const int last_position = watcher->end_index - 1;
    const char last_symbol = string_web[last_position];
    const int hold_positions = watcher->end_index - watcher->start_index;
    //Try to find regex: "//w|)//s+//w|(|{":
    int whitespace_counter = 0;
    if (isalpha(last_symbol)
        || is_open_parenthesis(last_symbol)
        || is_open_brace(last_symbol) && hold_positions >= 3) {
        for (int i = last_position - 1; i > 0; --i) {
            const char symbol = string_web[i];
            const_boolean is_space_or_line_break_condition = is_space_or_line_break(symbol);
            if (is_space_or_line_break_condition) {
                whitespace_counter++;
            }
            if (!is_space_or_line_break_condition && whitespace_counter > 0) {
                if (isalnum(symbol) || is_close_parenthesis(symbol)) {
                    watcher->end_index = i;
                    materials->scope_type = AIO_ASSIGN_WEAVING_SCOPE;
                    materials->value = substring(string_web, watcher->start_index, watcher->end_index);
                    watcher->start_index = watcher->end_index;
                    spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
                }
            }
        }
    }
}

/**
 * Instruction weaving.
 */

void weave_assign_instruction_for(aio_instruction_holder *holder, const_string _,
                                  int *next_ripper_point_reference, aio_spider *spider) {
    //Extract spider fields:
    const aio_assign_materials *materials = spider->get.assign_materials;
    const_string_array variable_data = materials->variable_data_list->strings;
    const_string value_string = materials->value;
    const point_watcher *watcher = materials->watcher;
    const aio_assign_variable_declaration_type declaration_type = materials->declaration_type;
    const_boolean is_ready_for_weaving = materials->scope_type == AIO_ASSIGN_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        *next_ripper_point_reference += watcher->end_index;
        //Weave variable definition:
        aio_variable_definition *new_definition = create_local_variable_definition(declaration_type, variable_data);
        const_string variable_name = new_definition->name;
        aio_variable_definition *definition = get_local_variable_definition_in_function_tree(variable_name, holder);
        if (definition == NULL) {
            definition = new_definition;
            //Put local definition in holder variable definition map:
            aio_variable_definition_map *map = holder->local_variable_definition_map;
            put_aio_variable_definition_in_map(map, definition);
        } else {
            if (!declaration_type == AIO_ASSIGN_WILL_DEFINED) {
                throw_error("ASSIGN SPIDER: variable already was defined in function tree!");
            }
            if (!definition->is_mutable_by_value) {
                throw_error("ASSIGN SPIDER: immutable variable can not change value!");
            }
            //----------------------------------------------------------------------------------------------------------
            //찌거기 수집기 (Garbage collector):
            free_aio_variable_definition(new_definition);
        }
        //Weave assign instruction:
        const_string assign_task_source = new_string(value_string);
        const_string assign_task_destination = new_string(variable_name);
        aio_instruction *assign_instruction = new_aio_assign_instruction(holder, assign_task_source,
                                                                         assign_task_destination);
        //Add assign instruction in holder's instructions:
        aio_instruction_list *instruction_list = holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, assign_instruction);
        //Weaving complete!
    } else {
        throw_error("ASSIGN SPIDER: not ready for weaving!");
    }
}

aio_variable_definition *create_local_variable_definition(const aio_assign_variable_declaration_type declaration_type,
                                                          const_string_array variable_materials) {
    string variable_name = NULL;
    string variable_type = NULL;
    boolean is_mutable = FALSE;
    switch (declaration_type) {
        case AIO_ASSIGN_WILL_DEFINED:
            variable_name = new_string(variable_materials[0]);
            variable_type = AIO_WILL_DEFINED;
            is_mutable = FALSE;
            break;
        case AIO_ASSIGN_REFERENCE:
            variable_name = new_string(variable_materials[1]);
            variable_type = VOID;
            is_mutable = TRUE;
            break;
            //Immutable mode:
        case AIO_ASSIGN_IMMUTABLE:
            variable_name = new_string(variable_materials[1]);
            variable_type = new_string(variable_materials[0]);
            is_mutable = FALSE;
            break;
            //Mutable by value mode:
        case AIO_ASSIGN_MUTABLE:
            variable_name = new_string(variable_materials[1]);
            variable_type = new_string(variable_materials[0]);
            is_mutable = TRUE;
            break;
        default:
            throw_error("ASSIGN SPIDER: undefined variable declaration mode for weaving!");
    }
    return new_aio_variable_definition(variable_name, variable_type, is_mutable);
}

/**
 * Material weaving.
 */

void weave_assign_materials_for(aio_spider *dst_spider, aio_spider *src_spider, const_string source_code,
                                int *next_spider_point_reference, aio_task_type task_type) {
    switch (task_type) {
        case AIO_LOOP_TASK:
            weave_assign_materials_for_loop_spider(dst_spider, src_spider, next_spider_point_reference);
            break;
        default:
            break;
    }
}

void weave_assign_materials_for_loop_spider(aio_spider *dst_spider, aio_spider *src_spider,
                                            int *next_spider_point_reference) {
    //Extract source spider fields:
    const aio_assign_materials *src_materials = src_spider->get.assign_materials;
    const_string_array variable_data = src_materials->variable_data_list->strings;
    const_string value_string = src_materials->value;
    const point_watcher *watcher = src_materials->watcher;
    const aio_assign_variable_declaration_type declaration_type = src_materials->declaration_type;
    const_boolean is_ready_for_weaving = src_materials->scope_type == AIO_ASSIGN_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        *next_spider_point_reference += watcher->end_index;
        aio_loop_materials *dst_materials = dst_spider->get.loop_materials;
        aio_loop_header_scope_type header_scope_type = dst_materials->header_scope_type;
        aio_variable_definition *pointer_definition = create_local_variable_definition(declaration_type, variable_data);
        aio_instruction *assign_instruction = new_aio_assign_instruction(NULL, value_string, pointer_definition->name);
        switch (header_scope_type) {
            case AIO_LOOP_HEADER_DEFINE: {
                dst_materials->start_assign_instruction = assign_instruction;
                dst_materials->pointer_definition = pointer_definition;
            }
                break;
            case AIO_LOOP_HEADER_CONDITION:
                throw_error("ASSIGN SPIDER: Ops! It's a bug!");
                break;
            case AIO_LOOP_HEADER_STEP: {
                aio_variable_definition* dst_pointer_definition = dst_materials->pointer_definition;
                if (dst_pointer_definition->is_mutable_by_value){
                    throw_error("ASSIGN SPIDER: mutable pointer can not be changed in loop header!");
                }
                dst_materials->step_assign_instruction = assign_instruction;
            }
        }
    } else {
        throw_error("ASSIGN SPIDER: not ready for weaving!");
    }
}