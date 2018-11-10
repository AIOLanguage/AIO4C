//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
//parsing:
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.h>
//runtime:
#include <aio_runtime/aio_task/aio_return/aio_return_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>

#define AIO_FUNCTION_PARTICLE_ERROR_TAG "AIO_FUNCTION_PARTICLE_ERROR_TAG"

#define AIO_FUNCTION_PARTICLE_DEBUG

#ifdef AIO_FUNCTION_PARTICLE_DEBUG

#define AIO_FUNCTION_PARTICLE_INFO_TAG "AIO_FUNCTION_PARTICLE_INFO"

//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

aio_function_particle::aio_function_particle()
{
    this->function = new aio_function();
    this->monitor_mode = AIO_MONITOR_MODIFIER;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->signal = AIO_PARTICLE_SIGNAL_UNDEFINED;
}

aio_function_particle::~aio_function_particle()
{
    delete this->function;
}

void aio_function_particle::reset()
{
    aio_function *old_function = this->function;
    this->function = new aio_function();
    this->counter_trigger = 0;
    this->monitor_mode = AIO_MONITOR_MODIFIER;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->signal = AIO_PARTICLE_SIGNAL_UNDEFINED;
    delete old_function;
}

unsigned aio_function_particle::illuminate(aio_space *space)
{
    //TODO: Make put for schemable:
    space->functions->add(this->function);
    this->function = new aio_function();
    return this->token_holder->end;
}

/**
 * Clean code:
 */

const aio_particle_signal aio_function_particle::handle_symbol(const unsigned position)
{
    const char symbol = this->radius_ptr->get_string()[position];
    switch (this->monitor_mode) {
        case AIO_MONITOR_MODIFIER:
            this->monitor_modifier(symbol, position);
            break;
        case AIO_MONITOR_NAME:
            this->monitor_name(symbol, position);
            break;
        case AIO_MONITOR_ARGS:
            this->monitor_args(symbol, position);
            break;
        case AIO_MONITOR_TYPE_OR_COLON_OR_EQUAL_SIGN_OR_OPENING_BRACE:
            this->monitor_type_or_colon_or_equal_sign_or_opening_brace(symbol, position);
            break;
        case AIO_MONITOR_ATTRIBUTE:
            this->monitor_attribute(symbol, position);
            break;
        case AIO_MONITOR_BODY:
            this->monitor_body(symbol, position);
            break;
        case AIO_MONITOR_VALUE:
            this->monitor_value(symbol, position);
            break;
        case AIO_MONITOR_COLON_OR_EQUAL_SIGN_OR_OPENING_BRACE:
            this->monitor_colon_or_equal_sign_or_opening_brace(symbol, position);
    }
    return this->signal;
}

void aio_function_particle::monitor_modifier(const char symbol, const unsigned position)
{
    const bool is_separator_cond = is_space_or_line_break(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE: {
            if (!is_separator_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
        }
            break;
        case AIO_TRIGGER_MODE_ACTIVE: {
            if (is_separator_cond) {
                //Capture modifier:
                this->token_holder->end = position;

#ifdef AIO_FUNCTION_PARTICLE_DEBUG
                log_info_str_hook(AIO_FUNCTION_PARTICLE_INFO_TAG, "Modifier:", this->token_holder);
#endif
                if (is_aio_function_modifier(this->token_holder)) {
                    //Go to name state:
                    this->go_to_name_state();
                }
            }
        }
    }
}

void aio_function_particle::go_to_name_state()
{
    this->monitor_mode = AIO_MONITOR_NAME;
    this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
}

void aio_function_particle::monitor_name(const char symbol, const unsigned position)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (!is_space_or_line_break(symbol)) {
                if (isalpha(symbol)) {
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                    this->token_holder->start = position;
                }
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (!isalnum(symbol)) {
                //Capture name:
                this->token_holder->end = position;
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
                log_info_str_hook(AIO_FUNCTION_PARTICLE_INFO_TAG, "Token name:", this->token_holder);
#endif
                //Set name for field:
                this->function->name = new str_hook(this->token_holder);
                //Switch to [<type>:=]:
                this->go_to_args_state(symbol, position);
            }
    }
}

void aio_function_particle::go_to_args_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_ARGS;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    //Prepare counter:
    this->counter_trigger = 0;
    this->monitor_args(symbol, position);
}

void aio_function_particle::monitor_args(const char symbol, const unsigned position)
{
    const bool is_opening_parenthesis_cond = is_opening_parenthesis(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (is_opening_parenthesis_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                //Take start of args content without '(':
                this->token_holder->start = position + 1;
                this->counter_trigger++;
            } else if (!is_space_or_line_break(symbol)) {
                throw_error_with_tag(AIO_FUNCTION_PARTICLE_ERROR_TAG, "Expected opening parenthesis or separator!");
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (is_opening_parenthesis_cond) {
                this->counter_trigger++;
            } else if (is_closing_parenthesis(symbol)) {
                this->counter_trigger--;
                if (this->counter_trigger == 0) {
                    this->token_holder->end = position;
                    this->set_args();
                    this->go_to_type_or_colon_or_equal_sign_or_opening_brace_state(symbol, position);
                }
            }
            break;
    }
}

#define ARRAY_BRACKETS "[]"

#define ARRAY_BRACKET_SIZE 2

#define ARG_PART_COUNT 2

#define ARG_NAME_INDEX 0

#define ARG_TYPE_INDEX 1

#define ARG_STABILITY true

#define IS_GLOBAL_ARG false

void aio_function_particle::set_args()
{
    this->token_holder
            ->split_by_comma()
            ->foreach([this](str_hook *chunk) {
                array_list<str_hook> *arg_content = chunk
                        ->split_by_whitespace()
                        ->filter_itself([](const str_hook *token) -> bool {
                            return token->is_not_empty();
                        });
                if (arg_content->get_size() == ARG_PART_COUNT) {
                    //Create arg by AIO standard:
                    aio_field *arg = new aio_field();
                    arg->is_const = ARG_STABILITY;
                    arg->visibility_type = AIO_VISIBILITY_LOCAL;
                    arg->is_static = IS_GLOBAL_ARG;
                    //Check name:
                    str_hook *name = arg_content->get(ARG_NAME_INDEX);
                    if (name->is_word()) {
                        arg->name = name;
                    } else {
                        throw_error_with_tag(AIO_FUNCTION_PARTICLE_ERROR_TAG, "Incorrect arg name!");
                    }
                    //Check type:
                    str_hook *type = arg_content->get(ARG_TYPE_INDEX);
                    bool is_array = false;
                    if (type->ends_with(ARRAY_BRACKETS)) {
                        type->end -= ARRAY_BRACKET_SIZE;
                        is_array = true;
                    }
                    if (type->is_word()) {
                        arg->type = type;
                        arg->is_array = is_array;
                    } else {
                        throw_error_with_tag(AIO_FUNCTION_PARTICLE_ERROR_TAG, "Incorrect arg type!");
                    }
                    //Put arg:
                    this->function->fields->add(arg);
                } else {
                    throw_error_with_tag(AIO_FUNCTION_PARTICLE_ERROR_TAG, "Expected 'name' 'type'");
                }
                delete arg_content;
            })
            ->free_elements()
            ->~array_list();
}

void aio_function_particle::go_to_type_or_colon_or_equal_sign_or_opening_brace_state(
        const char symbol,
        const unsigned position
)
{
    this->monitor_mode = AIO_MONITOR_TYPE_OR_COLON_OR_EQUAL_SIGN_OR_OPENING_BRACE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->monitor_type_or_colon_or_equal_sign_or_opening_brace(symbol, position);
}

void aio_function_particle::monitor_type_or_colon_or_equal_sign_or_opening_brace(
        const char symbol,
        const unsigned position
)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (is_equal_sign(symbol)) {
                //Capture '=':
                this->go_to_value_state(position);
            } else if (is_colon(symbol)) {
                //Capture ':':
                //Switch to 'private|protected':
                this->go_to_attribute_state();
            } else if (is_opening_brace(symbol)) {
                //Capture '{':
                this->go_to_body_state(symbol, position);
            } else if (!is_space_or_line_break(symbol)) {
                if (isalpha(symbol)) {
                    //Collect <type>:
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                    this->token_holder->start = position;
                } else {
                    throw_error_with_tag(AIO_FUNCTION_PARTICLE_ERROR_TAG, "The output type must start with letter!");
                }
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (!isalnum(symbol) && !is_opening_bracket(symbol) && !is_closing_bracket(symbol)) {
                //Capture type:
                this->token_holder->end = position;
                //Get type:
                str_hook *type = new str_hook(this->token_holder);
                //Check type:
                const bool is_array = type->ends_with(ARRAY_BRACKETS);
                if (is_array) {
                    type->end -= ARRAY_BRACKET_SIZE;
                    if (!type->is_word()) {
                        throw_error_with_tag(
                                AIO_FUNCTION_PARTICLE_ERROR_TAG, "The output type must contain only letters & numbers!"
                        );
                    }
                }
                //Set type to field:
                this->function->output_type = type;
                this->function->is_array_output = is_array;
                //Switch to [:=;]:
                this->go_to_colon_or_equal_sign_or_opening_brace_state(symbol, position);
            }
    }
}

void aio_function_particle::go_to_value_state(const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_VALUE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->counter_trigger = 0;
    this->token_holder->start = position + 1;
}

void aio_function_particle::go_to_attribute_state()
{
    this->monitor_mode = AIO_MONITOR_ATTRIBUTE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
}

void aio_function_particle::go_to_body_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_ARGS;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    //Prepare counter:
    this->counter_trigger = 0;
    this->monitor_body(symbol, position);
}

void aio_function_particle::go_to_colon_or_equal_sign_or_opening_brace_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_COLON_OR_EQUAL_SIGN_OR_OPENING_BRACE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->monitor_colon_or_equal_sign_or_opening_brace(symbol, position);
}

void aio_function_particle::monitor_attribute(const char symbol, const unsigned position)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (!is_space_or_line_break(symbol)) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (!isalnum(symbol)) {
                //Capture attribute:
                this->token_holder->end = position;
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
                log_info_str_hook(AIO_FUNCTION_PARTICLE_INFO_TAG, "Attribute:", this->token_holder);
#endif
                //Check attribute:
                const bool is_private = is_aio_private_modifier(this->token_holder);
                const bool is_protected = is_aio_protected_modifier(this->token_holder);
                if (is_private || is_protected) {
                    if (this->function->visibility_type == AIO_VISIBILITY_UNDEFINED) {
                        //Set attribute:
                        if (is_private) {
                            this->function->visibility_type = AIO_VISIBILITY_PRIVATE;
                        } else {
                            this->function->visibility_type = AIO_VISIBILITY_PROTECTED;
                        }
                        //Switch to [:=;]:
                        this->monitor_colon_or_equal_sign_or_opening_brace(symbol, position);
                    } else {
                        throw_error_with_tag(
                                AIO_FUNCTION_PARTICLE_ERROR_TAG, "Function visibility is already defined!"
                        );
                    }
                } else {
                    throw_error_with_tag(
                            AIO_FUNCTION_PARTICLE_ERROR_TAG, "Expected attribute 'protected' or 'private'"
                    );
                }
            }
    }
}

void aio_function_particle::monitor_colon_or_equal_sign_or_opening_brace(const char symbol, const unsigned position)
{
    if (is_equal_sign(symbol)) {
        //Capture '=':
        this->go_to_value_state(position);
    } else if (is_colon(symbol)) {
        //Capture ':':
        this->go_to_attribute_state();
    } else if (is_opening_brace(symbol)) {
        //Capture ';':
        this->go_to_body_state(symbol, position);
    } else if (!is_space_or_line_break(symbol)) {
        throw_error_with_tag(AIO_FUNCTION_PARTICLE_ERROR_TAG, "Expected [=:{]");
    }
}

void aio_function_particle::monitor_value(const char symbol, const unsigned position)
{
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
    log_info_char(AIO_FUNCTION_PARTICLE_INFO_TAG, "Char:", symbol);
#endif

    const bool is_single_quote_cond = is_single_quote(symbol);
    if (is_single_quote_cond) {
        this->is_inside_string = !this->is_inside_string;
    }
    const bool in_expression_scope = !this->is_inside_string;
    const bool is_end_of_holder = position == this->radius_ptr->end - 1;
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_letter_or_number = isalnum(symbol);
    if (is_end_of_holder) {
        this->set_single_return_instruction(true, position);
    }
    if (in_expression_scope) {
        switch (this->trigger_mode) {
            case AIO_TRIGGER_MODE_PASSIVE:
                if (is_letter_or_number || is_closing_parenthesis(symbol) || is_single_quote_cond) {
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;

#ifdef AIO_FUNCTION_PARTICLE_DEBUG
                    log_info(AIO_FUNCTION_PARTICLE_INFO_TAG, "SUPPOSE END");
#endif
                }
                break;
            case AIO_TRIGGER_MODE_ACTIVE:
                if (is_whitespace_cond) {
                    this->counter_trigger++;
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
                    log_info(AIO_FUNCTION_PARTICLE_INFO_TAG, "COUNTER");
#endif
                } else if (is_sign(symbol)) {
                    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
                    log_info(AIO_FUNCTION_PARTICLE_INFO_TAG, "RESET");
#endif
                } else if ((is_letter_or_number && this->counter_trigger > 0) || is_closing_brace(symbol)) {
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
                    log_info(AIO_FUNCTION_PARTICLE_INFO_TAG, "SET VALUE");
#endif
                    this->set_single_return_instruction(false, position);
                }
        }
    }
}

void aio_function_particle::set_single_return_instruction(const bool is_end_of_holder, const unsigned position)
{
    if (is_end_of_holder) {
        this->token_holder->end = this->radius_ptr->end;
    } else {
        this->token_holder->end = position - this->counter_trigger;
    }
    char *dirty_value = this->token_holder->to_string();
    char *clean_value = squeeze_string_for_expression(dirty_value);
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
    log_info_string(AIO_FUNCTION_PARTICLE_INFO_TAG, "Value:", clean_value);
#endif
    aio_return_task *task = new aio_return_task();
    task->set_value(clean_value);
    this->function->instructions->add(task);
    this->token_holder->start = this->token_holder->end;
    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
    //------------------------------------------------------------------------------------------------------------------
    //찌거기 수집기:
    free_string(dirty_value);
}

void aio_function_particle::monitor_body(const char symbol, const unsigned position)
{

    const bool is_opening_brace_cond = is_opening_brace(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (is_opening_brace_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                //Take start of args content without '{':
                this->token_holder->start = position + 1;
                this->counter_trigger++;
            } else if (!is_space_or_line_break(symbol)) {
                throw_error_with_tag(AIO_FUNCTION_PARTICLE_ERROR_TAG, "Expected opening brace or separator!");
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (is_opening_brace_cond) {
                this->counter_trigger++;
            } else if (is_closing_brace(symbol)) {
                this->counter_trigger--;
                if (this->counter_trigger == 0) {
                    this->token_holder->end = position;
                    this->set_body();
                }
            }
            break;
    }
}

void aio_function_particle::set_body()
{
    //Launch particles:
    aio_orbit<aio_schemable>::create()
            ->set_pivot(this->function)
            ->set_radius(this->token_holder)
//            ->set_particle()
//            ->spin()
            ->finish();
    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
}