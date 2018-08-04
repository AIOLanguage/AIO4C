cmake_minimum_required(VERSION 3.10)
project(AIO C)

set(CMAKE_C_STANDARD 11)

add_executable(AIO sources/main/main.c
        headers/lang/aio_annotation/aio_annotation.h
        headers/lang/aio_reserved_names/aio_reserved_names_container.h
        headers/lang/aio_context/aio_context.h headers/lib/collections/lists/string_list.h
        sources/lib/collections/lists/string_list.c
        headers/lang/aio_function/aio_bundle/aio_bundle.h
        headers/lang/aio_function/aio_function_definition/aio_function_definition.h
        headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h
        headers/lib/collections/lists/aio_instruction_list.h
        headers/lang/aio_types/aio_type.h
        sources/lib/collections/maps/aio_context_map.c
        headers/lib/collections/maps/aio_context_map.h headers/lang/aio_core/aio_core.h
        sources/lang/aio_core/aio_core.c
        headers/lib/collections/maps/aio_function_definition_map.h
        sources/lib/collections/maps/aio_function_definition_map.c
        sources/lang/aio_context/aio_context.c
        sources/lang/aio_context/aio_context_builder.c
        sources/lang/aio_annotation/aio_annotation.c
        headers/lib/collections/lists/aio_annotation_list.h
        sources/lib/collections/lists/aio_annotation_list.c
        sources/lib/utils/string_utils/string_utils.c headers/lib/utils/string_utils/string_utils.h
        headers/lang/aio_function/aio_function_definition/aio_function_definition_builder.h
        headers/lang/aio_function/aio_function.h
        headers/tools/analysis/function_reproducer/aio_function_reproducer.h
        headers/lib/collections/maps/aio_variable_map.h
        headers/lib/collections/maps/aio_variable_definition_map.h
        sources/lib/collections/maps/aio_variable_map.c
        headers/lib/utils/operation_utils/operation_utils.h
        sources/lib/utils/operation_utils/operation_utils.c
        sources/lib/utils/file_utils/file_reader.c
        headers/lib/utils/file_utils/file_reader.h
        sources/lib/utils/string_utils/split.c
        sources/lib/utils/string_utils/trim.c
        sources/lib/utils/string_utils/prefix_suffix.c
        headers/tools/parsers/aio_parser.h
        sources/lang/aio_function/aio_bundle/aio_bundle.c
        sources/lang/aio_function/aio_function_definition/aio_function_definition.c
        sources/lang/aio_function/aio_function_definition/aio_builder/aio_function_definition_builder.c
        sources/lang/aio_function/aio_result/aio_result.c
        headers/lang/aio_function/aio_result/aio_result.h
        sources/lang/aio_function/aio_value/aio_value.c
        sources/lang/aio_function/aio_variable/aio_variable.c
        sources/lang/aio_function/aio_variable/aio_variable_definition.c
        headers/lang/aio_function/aio_value/aio_value.h
        headers/lang/aio_function/aio_variable/aio_variable.h
        headers/lang/aio_function/aio_variable/aio_variable_definition.h
        sources/lang/aio_function/aio_function.c
        sources/lang/aio_reserved_names/aio_reserved_names_container.c
        sources/lang/aio_function/aio_function_definition/aio_builder/aio_ripper/aio_annotation_ripper.c
        sources/lang/aio_function/aio_function_definition/aio_builder/aio_ripper/aio_arg_ripper.c
        sources/lang/aio_function/aio_function_definition/aio_builder/aio_ripper/aio_function_name_ripper.c
        sources/lang/aio_function/aio_function_definition/aio_builder/aio_ripper/aio_instruction_ripper.c
        sources/lang/aio_function/aio_function_definition/aio_builder/aio_ripper/aio_output_ripper.c
        headers/lib/pair/string_pair.h
        sources/lib/pair/string_pair.c
        sources/lib/utils/double_utils/double_utils.c
        headers/lib/utils/boolean_utils/boolean_utils.h
        headers/lib/utils/int_utils/int_utils.h
        headers/lib/utils/double_utils/double_utils.h
        headers/lib/utils/error_utils/error_utils.h
        headers/lib/collections/sets/string_set.h
        sources/lib/collections/sets/string_set.c
        sources/lib/utils/int_utils/int_utils.c sources/lib/utils/boolean_utils/boolean_utils.c
        sources/tools/analysis/method_reproducer/aio_function_reproducer.c
        headers/lib/point_watcher/point_watcher.h sources/lib/point_watcher/point_watcher.c)