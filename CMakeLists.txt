project(AIO C)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -I/headers")

add_definitions(-DSOME_IMPORTANT_DEFINITION)

add_executable(${PROJECT_NAME}
        #---------------------------------------------------------------------------------------------------------------
        #MAIN:
        main/main.c
        #---------------------------------------------------------------------------------------------------------------


        #---------------------------------------------------------------------------------------------------------------
        #HEADERS:
        #lang:
        headers/lang/aio_annotation/aio_annotation.h
        headers/lang/aio_context/aio_context.h
        headers/lang/aio_core/aio_core.h
        headers/lang/aio_function/aio_bundle/aio_bundle.h
        headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h
        headers/lang/aio_function/aio_function_definition/aio_function_definition.h
        headers/lang/aio_function/aio_function_definition/aio_function_definition_builder.h
        headers/lang/aio_function/aio_result/aio_result.h
        headers/lang/aio_function/aio_value/aio_value.h
        headers/lang/aio_function/aio_function.h
        headers/lang/aio_function/aio_variable/aio_variable.h
        headers/lang/aio_function/aio_variable/aio_variable_definition.h
        headers/lang/aio_reserved_names/aio_reserved_names_container.h
        headers/lang/aio_types/aio_type.h
        #tools:
        headers/tools/aio_parsers/aio_block_body_explorer/aio_block_body_explorer.h
        headers/tools/aio_parsers/aio_function_rippers/aio_function_rippers.h
        headers/tools/aio_parsers/aio_spiders/aio_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_spider_nest.h
        headers/tools/aio_parsers/aio_spiders/aio_assign_spider/aio_assign_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_break_spider/aio_break_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_if_spider/aio_if_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_loop_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_default_loop_header_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_in_loop_header_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_tiny_loop_header_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_procedure_spider/aio_procedure_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_switch_spider/aio_switch_spider.h
        headers/tools/aio_parsers/aio_spiders/aio_return_spider/aio_return_spider.h
        #lib:
        headers/lib/collections/lists/aio_annotation_list.h
        headers/lib/collections/lists/aio_instruction_list.h
        headers/lib/collections/lists/string_list.h
        headers/lib/collections/maps/aio_context_map.h
        headers/lib/collections/maps/aio_function_definition_map.h
        headers/lib/collections/maps/aio_variable_definition_map.h
        headers/lib/collections/maps/aio_variable_map.h
        headers/lib/collections/sets/string_set.h
        headers/lib/pair/string_pair.h
        headers/lib/point_watcher/point_watcher.h
        headers/lib/utils/boolean_utils/boolean_utils.h
        headers/lib/utils/char_utils/char_utils.h
        headers/lib/utils/double_utils/double_utils.h
        headers/lib/utils/error_utils/error_utils.h
        headers/lib/utils/file_utils/file_reader.h
        headers/lib/utils/int_utils/int_utils.h
        headers/lib/utils/operation_utils/operation_utils.h
        headers/lib/utils/string_utils/string_builder.h
        headers/lib/utils/string_utils/string_utils.h
        headers/lib/utils/memory_utils/memory_utils.h
        headers/lib/utils/log_utils/log_utils.h
        #---------------------------------------------------------------------------------------------------------------


        #---------------------------------------------------------------------------------------------------------------
        #SOURCES:
        #lang:
        sources/lang/aio_context/aio_context_builder.c
        sources/lang/aio_annotation/aio_annotation.c
        sources/lang/aio_context/aio_context.c
        sources/lang/aio_core/aio_core.c
        sources/lang/aio_function/aio_bundle/aio_bundle.c
        sources/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.c
        sources/lang/aio_function/aio_function_definition/aio_function_definition.c
        sources/lang/aio_function/aio_function_definition/aio_function_definition_builder.c
        sources/lang/aio_function/aio_result/aio_result.c
        sources/lang/aio_function/aio_value/aio_value.c
        sources/lang/aio_function/aio_function.c
        sources/lang/aio_function/aio_variable/aio_variable.c
        sources/lang/aio_function/aio_variable/aio_variable_definition.c
        sources/lang/aio_reserved_names/aio_reserved_names_container.c
        #tools:
        sources/tools/aio_parsers/aio_block_body_explorer/aio_block_body_explorer.c
        sources/tools/aio_parsers/aio_function_rippers/aio_annotation_ripper.c
        sources/tools/aio_parsers/aio_function_rippers/aio_arg_ripper.c
        sources/tools/aio_parsers/aio_function_rippers/aio_function_name_ripper.c
        sources/tools/aio_parsers/aio_function_rippers/aio_instruction_ripper.c
        sources/tools/aio_parsers/aio_function_rippers/aio_output_ripper.c
        sources/tools/aio_parsers/aio_spiders/aio_assign_spider/aio_assign_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_break_spider/aio_break_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_if_spider/aio_if_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_loop_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_default_loop_header_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_in_loop_header_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_tiny_loop_header_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_return_spider/aio_return_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_procedure_spider/aio_procedure_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_switch_spider/aio_switch_spider.c
        sources/tools/aio_parsers/aio_spiders/aio_spider_nest.c
        #lib:
        sources/lib/collections/lists/aio_annotation_list.c
        sources/lib/collections/lists/aio_instruction_list.c
        sources/lib/collections/lists/string_list.c
        sources/lib/collections/maps/aio_context_map.c
        sources/lib/collections/maps/aio_function_definition_map.c
        sources/lib/collections/maps/aio_variable_definition_map.c
        sources/lib/collections/maps/aio_variable_map.c
        sources/lib/collections/sets/string_set.c
        sources/lib/pair/string_pair.c
        sources/lib/point_watcher/point_watcher.c
        sources/lib/utils/boolean_utils/boolean_utils.c
        sources/lib/utils/char_utils/char_utils.c
        sources/lib/utils/double_utils/double_utils.c
        sources/lib/utils/error_utils/error_utils.c
        sources/lib/utils/file_utils/file_reader.c
        sources/lib/utils/int_utils/int_utils.c
        sources/lib/utils/operation_utils/operation_utils.c
        sources/lib/utils/string_utils/string_builder.c
        sources/lib/utils/string_utils/string_utils.c
        sources/lib/utils/string_utils/prefix_suffix.c
        sources/lib/utils/string_utils/split.c
        sources/lib/utils/string_utils/trim.c
        sources/lib/utils/memory_utils/memory_utils.c
        sources/lib/utils/log_utils/log_utils.c
        sources/lib/collections/lists/aio_instruction_list.c
        sources/lib/utils/error_utils/error_utils.c
        )