project(AIO C)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra")

add_definitions(-DSOME_IMPORTANT_DEFINITION)

add_executable(${PROJECT_NAME}
        #---------------------------------------------------------------------------------------------------------------
        #MAIN:
        main/main.c
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #HEADERS:
        headers
        #lang:
        headers/lang/aio_annotation/aio_annotation.h
        headers/lang/aio_context/aio_context.h
        headers/lang/aio_core/aio_core.h
        headers/lang/aio_function/aio_bundle/aio_bundle.h
        headers/lang/aio_function/aio_function_definition/aio_function_definition.h
        headers/lang/aio_function/aio_function_definition/aio_function_definition_builder.h
        headers/lang/aio_function/aio_result/aio_result.h
        headers/lang/aio_function/aio_value/aio_value.h
        headers/lang/aio_function/aio_variable/aio_variable.h
        headers/lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h
        headers/lang/aio_function/aio_function.h
        headers/lang/aio_reserved_names/aio_reserved_names_container.h
        headers/lang/aio_type/aio_type.h
        #tools:
        headers/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h
        headers/tools/aio_common_tools/aio_spider_nest/aio_function_instruction_spider_nest.h
        headers/tools/aio_common_tools/aio_spider_nest/aio_spider.h
        headers/tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h
        headers/tools/aio_function_tools/aio_definition_rippers/aio_function_definition_rippers.h
        headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_assign_spider/aio_assign_spider.h
        headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_break_spider/aio_break_spider.h
        headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_if_spider/aio_if_spider.h
        headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_loop_spider/aio_loop_spider.h
        headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_procedure_spider/aio_procedure_spider.h
        headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_return_spider/aio_return_spider.h
        headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_switch_spider/aio_switch_spider.h
        headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_function_instruction_spider_nest.h
        headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h
        headers/tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.h
        headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_assign_task.h
        headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_break_task.h
        headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_if_task.h
        headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_loop_task.h
        headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_procedure_task.h
        headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_return_task.h
        headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_switch_task.h
        headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h
        #lib:
        headers/lib/utils/boolean_utils/boolean_utils.h
        headers/lib/utils/char_utils/char_utils.h
        headers/lib/utils/collections/lists/string_list.h
        headers/lib/utils/collections/sets/string_set.h
        headers/lib/utils/double_utils/double_utils.h
        headers/lib/utils/error_utils/error_utils.h
        headers/lib/utils/file_utils/file_reader.h
        headers/lib/utils/int_utils/int_utils.h
        headers/lib/utils/log_utils/log_utils.h
        headers/lib/utils/memory_utils/memory_utils.h
        headers/lib/utils/operation_utils/operation_utils.h
        headers/lib/utils/point_watcher/point_watcher.h
        headers/lib/utils/str_hook/str_hook.h
        headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h
        headers/lib/utils/string_pair/string_pair.h
        headers/lib/utils/string_utils/string_builder.h
        headers/lib/utils/string_utils/string_utils.h
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #SOURCES:
        sources
        #lang:
        sources/lang/aio_annotation/aio_annotation.c
        sources/lang/aio_context/aio_context.c
        sources/lang/aio_context/aio_context_builder.c
        sources/lang/aio_core/aio_core.c
        sources/lang/aio_function/aio_bundle/aio_bundle.c
        sources/lang/aio_function/aio_function_definition/aio_function_definition.c
        sources/lang/aio_function/aio_function_definition/aio_function_definition_builder.c
        sources/lang/aio_function/aio_result/aio_result.c
        sources/lang/aio_function/aio_value/aio_value.c
        sources/lang/aio_function/aio_variable/aio_variable_definition/aio_variable_definition.c
        sources/lang/aio_function/aio_variable/aio_variable.c
        sources/lang/aio_function/aio_function.c
        sources/lang/aio_reserved_names/aio_reserved_names_container.c
        sources/lang/aio_type/aio_type.c
        #tools:
        sources/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.c
        sources/tools/aio_common_tools/aio_spider_nest/aio_spider_nest.c
        sources/tools/aio_function_tools/aio_control_graph/aio_function_control_graph.c
        sources/tools/aio_function_tools/aio_definition_rippers/aio_annotation_ripper.c
        sources/tools/aio_function_tools/aio_definition_rippers/aio_arg_ripper.c
        sources/tools/aio_function_tools/aio_definition_rippers/aio_function_name_ripper.c
        sources/tools/aio_function_tools/aio_definition_rippers/aio_instruction_ripper.c
        sources/tools/aio_function_tools/aio_definition_rippers/aio_output_ripper.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_assign_spider/aio_assign_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_break_spider/aio_break_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_if_spider/aio_if_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_loop_spider/aio_loop_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_loop_spider/aio_inner_spiders/aio_default_loop_header_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_loop_spider/aio_inner_spiders/aio_in_loop_header_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_loop_spider/aio_inner_spiders/aio_tiny_loop_header_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_procedure_spider/aio_procedure_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_return_spider/aio_return_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_switch_spider/aio_switch_spider.c
        sources/tools/aio_function_tools/aio_instruction_spider_nest/aio_function_instruction_spider_nest.c
        sources/tools/aio_function_tools/aio_instructions/aio_function_instruction.c
        sources/tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.c
        sources/tools/aio_function_tools/aio_instructions/aio_tasks/aio_assign_task.c
        sources/tools/aio_function_tools/aio_instructions/aio_tasks/aio_break_task.c
        sources/tools/aio_function_tools/aio_instructions/aio_tasks/aio_if_task.c
        sources/tools/aio_function_tools/aio_instructions/aio_tasks/aio_loop_task.c
        sources/tools/aio_function_tools/aio_instructions/aio_tasks/aio_procedure_task.c
        sources/tools/aio_function_tools/aio_instructions/aio_tasks/aio_return_task.c
        sources/tools/aio_function_tools/aio_instructions/aio_tasks/aio_switch_task.c
        #lib:
        sources/lib/utils/boolean_utils/boolean_utils.c
        sources/lib/utils/char_utils/char_utils.c
        sources/lib/utils/collections/lists/string_list.c
        sources/lib/utils/collections/sets/string_set.c
        sources/lib/utils/double_utils/double_utils.c
        sources/lib/utils/error_utils/error_utils.c
        sources/lib/utils/file_utils/file_reader.c
        sources/lib/utils/int_utils/int_utils.c
        sources/lib/utils/log_utils/log_utils.c
        sources/lib/utils/memory_utils/memory_utils.c
        sources/lib/utils/operation_utils/operation_utils.c
        sources/lib/utils/point_watcher/point_watcher.c
        sources/lib/utils/str_hook/str_hook.c
        sources/lib/utils/str_hook/str_hook_utils/str_hook_split.c
        sources/lib/utils/str_hook/str_hook_utils/str_hook_trim.c
        sources/lib/utils/str_hook/str_hook_utils/str_hook_utils.c
        sources/lib/utils/string_pair/string_pair.c
        sources/lib/utils/string_utils/prefix_suffix.c
        sources/lib/utils/string_utils/split.c
        sources/lib/utils/string_utils/string_builder.c
        sources/lib/utils/string_utils/string_utils.c
        sources/lib/utils/string_utils/trim.c
        sources/lib/utils/str_hook/str_hook_utils/str_hook_iterator.c
        sources/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.c
        sources/tools/aio_function_tools/aio_expression_parser/aio_inner_parcers/aio_int_parser.c
        sources/tools/aio_function_tools/aio_expression_parser/aio_inner_parcers/aio_double_parser.c
        sources/tools/aio_function_tools/aio_expression_parser/aio_inner_parcers/aio_string_parser.c
        sources/tools/aio_function_tools/aio_expression_parser/aio_inner_parcers/aio_boolean_parser.c
        sources/tools/aio_function_tools/aio_expression_parser/aio_inner_parcers/aio_type_parser.c
        sources/tools/aio_function_tools/aio_expression_parser/aio_expression_assistant.c
        sources/tools/aio_function_tools/aio_expression_parser/aio_inner_parcers/aio_void_parser.c
        #---------------------------------------------------------------------------------------------------------------
        )


#TODO: How make it???
#-I C:/Users/StarKRE/CLionProjects/AIO/headers

#add_definitions(-I headers-)
