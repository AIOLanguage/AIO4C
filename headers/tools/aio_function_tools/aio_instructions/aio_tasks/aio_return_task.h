#ifndef AIO_RETURN_INSTRUCTION_H
#define AIO_RETURN_INSTRUCTION_H

#include "../../../../lib/utils/collections/lists/string_list.h"
#include "../aio_function_instruction_holder.h"
#include "../aio_function_instruction.h"

typedef struct aio_return_task {
    string_list *return_values;
} aio_return_task;

aio_function_instruction * new_aio_return_instruction(aio_function_instruction_holder *holder,
                                                      const_string_list *return_value_list);

#endif //AIO_RETURN_INSTRUCTION_H