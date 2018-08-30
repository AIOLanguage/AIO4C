
#include <tools/aio_function_tools/aio_instructions/aio_function_instruction.h>
#include <lib/utils/string_utils/string_utils.h>
#include <tools/aio_function_tools/aio_instructions/aio_tasks/aio_procedure_task.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h>

aio_function_instruction *new_aio_procedure_instruction(
        aio_function_instruction_holder *holder,
        string procedure
)
{
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_PROCEDURE_TASK);
    //Init task:
    aio_procedure_task *task = new_object(sizeof(aio_procedure_task));
    task->procedure = procedure;
    instruction->get.procedure_task = task;
    return instruction;
}

void perform_aio_procedure_instruction(
        const_aio_function_instruction *instruction,
        const_aio_function_control_graph *control_graph
)
{
    const aio_procedure_task *procedure_task = instruction->get.procedure_task;
    const_string procedure_string = procedure_task->procedure;
    parse_value_string(procedure_string, control_graph);
}