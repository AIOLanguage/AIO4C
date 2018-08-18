#include <malloc.h>
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_instruction_holder *new_aio_instruction_holder(aio_instruction_holder *parent_holder) {
    aio_instruction_holder *holder = new_object(sizeof(aio_instruction_holder));
    holder->parent = parent_holder;
    holder->variable_definition_map = new_aio_variable_definition_map();
    holder->instruction_list = new_aio_instruction_list();
    return holder;
}

aio_instruction_holder *inflate_aio_root_instruction_holder(const_string source_code, int *start_code_pointer_ref,
                                                            struct aio_variable_definition_list *arg_definition_map) {
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
    log_info(AIO_INSTRUCTION_RIPPER_TAG, "Dig root root_holder...");
#endif
    //보유자를 파다 (Dig a instruction root_holder):
    aio_instruction_holder *parent_holder = NULL;
    //시작 및 종료 인덱스 초기화 (Init start & end indexes):
    int start_index = *start_code_pointer_ref;
    int end_index = 0;
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
    log_info(AIO_INSTRUCTION_RIPPER_TAG, "Explore function body...");
#endif
    //시작 및 종료 인덱스 찾다 (Search start & end indexes):
    explore_block_body(source_code, &start_index, &end_index);
    *start_code_pointer_ref = end_index;
    aio_instruction_holder *root_holder = new_object(sizeof(struct aio_instruction_holder));
    root_holder->parent = parent_holder;
    root_holder->variable_definition_map = arg_definition_map;
    root_holder->instruction_list = new_aio_instruction_list();
    dig_aio_instructions_for(root_holder, source_code, start_index, end_index);
    return root_holder;
}

aio_instruction_holder *inflate_local_aio_instruction_holder(const_string source_code,
                                                             struct aio_instruction_holder *parent_holder,
                                                             const int start_index, const int end_index) {
    aio_instruction_holder *holder = new_aio_local_instruction_holder(parent_holder);
    dig_aio_instructions_for(holder, source_code, start_index, end_index);
    return holder;
}