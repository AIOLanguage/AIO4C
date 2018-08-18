aio_instruction_list *new_aio_instruction_list() {
    aio_instruction_list *list = calloc(1, sizeof(aio_instruction_list));
    list->capacity = 2;
    list->size = 0;
    list->instructions = calloc(2, sizeof(aio_instruction *));
    return list;
}

//Passed JUnitTest!
void update_memory_in_instruction_list(aio_instruction_list *list) {
    if (list->size + 1 == list->capacity) {
        list->capacity = list->capacity * 2;
        list->instructions = realloc(list->instructions, list->capacity * sizeof(aio_instruction *));
    }
}

void add_aio_instruction_in_list(aio_instruction_list *list, aio_instruction *instruction){
    //Check from update capacity:
    update_memory_in_instruction_list(list);
    //Set annotation:
    list->instructions[list->size] = instruction;
    list->size++;
}

void free_aio_instruction_list(aio_instruction_list *list){
    free(list->instructions);
    free(list);
}