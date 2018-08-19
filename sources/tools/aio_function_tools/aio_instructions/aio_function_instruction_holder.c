#include <malloc.h>
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h"
#include "../../../../headers/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h"
#include "../../../../headers/tools/aio_function_tools/aio_definition_rippers/aio_function_definition_rippers.h"


#define AIO_FUNCTION_INSTRUCTION_HOLDER_DEBUG

#define AIO_FUNCTION_INSTRUCTION_HOLDER_TAG "AIO_FUNCTION_INSTRUCTION_HOLDER"

#ifdef AIO_FUNCTION_INSTRUCTION_HOLDER_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Constructor.
 */

aio_function_instruction_holder *new_aio_function_instruction_holder(
        const_aio_function_instruction_holder *parent_holder) {
    aio_function_instruction_holder *holder = new_object(sizeof(aio_function_instruction_holder));
    holder->parent = parent_holder;
    holder->variable_definition_list = new_aio_variable_definition_list();
    holder->instruction_list = new_aio_function_instruction_list();
    return holder;
}

/**
 * Create root function holder.
 * @param source_code - file content.
 * @param start_code_pointer_ref - pointer.
 * @param arg_definitions - found args.
 * @return new holder.
 */

aio_function_instruction_holder *inflate_root_aio_instruction_holder(const_string source_code,
                                                                     int *start_code_pointer_ref,
                                                                     aio_variable_definition_list *arg_definitions) {
#ifdef AIO_FUNCTION_INSTRUCTION_HOLDER_DEBUG
    log_info(AIO_FUNCTION_INSTRUCTION_HOLDER_TAG, "Dig root root_holder...");
#endif
    //보유자를 파다 (Dig a instruction root_holder):
    aio_function_instruction_holder *parent_holder = NULL;
    //시작 및 종료 인덱스 초기화 (Init start & end indexes):
    int start_index = *start_code_pointer_ref;
    int end_index = 0;
#ifdef AIO_FUNCTION_INSTRUCTION_HOLDER_DEBUG
    log_info(AIO_FUNCTION_INSTRUCTION_HOLDER_TAG, "Explore function body...");
#endif
    //시작 및 종료 인덱스 찾다 (Search start & end indexes):
    explore_aio_block_bounds(source_code, &start_index, &end_index);
    *start_code_pointer_ref = end_index;
    aio_function_instruction_holder *root_holder = new_object(sizeof(aio_function_instruction_holder));
    root_holder->parent = parent_holder;
    root_holder->variable_definition_list = arg_definitions;
    root_holder->instruction_list = new_aio_function_instruction_list();
    dig_aio_instructions_for(root_holder, source_code, start_index, end_index);
    return root_holder;
}

/**
 * Create local holder in function body.
 * @param source_code - file content
 * @param parent_holder - parent block.
 * @param start_index - start pointer in file content.
 * @param end_index - end pointer in file content.
 * @return new holder.
 */

aio_function_instruction_holder *inflate_local_aio_instruction_holder(const_string source_code,
                                                                      const_aio_function_instruction_holder
                                                                      *parent_holder,
                                                                      const int start_index, const int end_index) {
    aio_function_instruction_holder *holder = new_aio_function_instruction_holder(parent_holder);
    dig_aio_instructions_for(holder, source_code, start_index, end_index);
    return holder;
}

void free_aio_function_instruction_holder(aio_function_instruction_holder *holder) {

}