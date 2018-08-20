#ifndef AIO_SWITCH_INSTRUCTION_H
#define AIO_SWITCH_INSTRUCTION_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../../../../lib/utils/collections/lists/string_list.h"
#include "../aio_function_instruction_holder.h"
#include "../aio_function_instruction.h"

typedef struct aio_switch_task {
    const_string switch_value;
    string_list *case_keys;
    aio_function_instruction_holder **case_holders;
    aio_function_instruction_holder *else_holder;
    boolean is_not_equals_any_cases;
} aio_switch_task;

aio_function_instruction * new_aio_switch_instruction(aio_function_instruction_holder *holder,
                                                      const_string switch_value,
                                                      string_list *case_keys,
                                                      aio_function_instruction_holder **case_holders,
                                                      aio_function_instruction_holder *else_holder);

void perform_aio_switch_instruction(const_aio_function_instruction *instruction,
                                    const_aio_function_control_graph *control_graph);

#endif //AIO_SWITCH_INSTRUCTION_H