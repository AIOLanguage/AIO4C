#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"

aio_function_instruction * new_aio_break_instruction(
        aio_function_instruction_holder *holder) {
    return new_aio_function_instruction(holder, AIO_BREAK_TASK);
}