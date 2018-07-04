cmake_minimum_required(VERSION 3.10)
project(AIO C)

set(CMAKE_C_STANDARD 11)

add_executable(AIO sources/main/main.c
        sources/lang/reserved_names/aio_reserved_names_container.c
        headers/lang/aio_annotation/aio_annotation.h
        headers/lang/aio_reserved_names/aio_reserved_names_container.h
        headers/lang/aio_file/aio_file.h headers/lib/collections/lists/string_list.h
        sources/lib/collections/lists/string_list.c
        headers/lang/aio_method/bundle/aio_bundle.h
        headers/lang/aio_method/method_definition/aio_method_size_type.h
        headers/lang/aio_method/method_definition/aio_method_definition.h
        headers/lang/aio_method/variable/aio_variable.h headers/lang/aio_types/aio_type.h
        sources/lang/types/aio_type.c sources/lib/collections/maps/aio_object_map.c
        headers/lib/collections/maps/aio_object_map.h headers/lang/aio_core/aio_core.h
        sources/lang/object/objectManager/aio_core.c
        headers/lib/collections/maps/aio_method_definition_map.h
        sources/lib/collections/maps/aio_method_definition_map.c
        sources/lang/object/aio_file.c
        sources/lang/methods/method_definition/aio_method_definition.c
        sources/lang/annotations/aio_annotation.c
        headers/lib/collections/lists/aio_annotation_list.h
        sources/lib/collections/lists/aio_annotation_list.c
        sources/lang/methods/bundle/aio_bundle.c
        sources/lang/methods/variable/aio_variable.c
        headers/lang/aio_method/result/aio_result.h sources/lang/methods/result/aio_result.c
        headers/lang/aio_native/aio_default_method_container/aio_default_method_container.h
        sources/lang/methods/default_method_container/aio_default_method_container.c
        sources/lib/utils/string_utils/string_utils.c headers/lib/utils/string_utils/string_utils.h
        headers/lang/aio_method/method_definition/aio_method_definition_builder.h
        sources/lang/methods/method_definition/aio_method_definition_builder.c
        headers/lang/aio_method/aio_method.h sources/lang/methods/aio_method.c
        headers/tools/analysis/method_reproducer/aio_method_reproducer.h
        sources/lang/methods/analysis/method_reproducer/aio_method_reproducer.c
        headers/lib/collections/maps/aio_variable_map.h
        sources/lib/collections/maps/aio_variable_map.c
        headers/lang/aio_method/aio_method_container.h
        headers/tools/analysis/method_reproducer/the_shortest/aio_the_shortest_reproducer.h
        headers/tools/analysis/method_reproducer/default/aio_default_reproducer.h
        headers/tools/analysis/method_reproducer/short/aio_short_reproducer.h
        headers/lib/utils/operation_utils/operation_utils.h
        sources/lib/utils/operation_utils/operation_utils.c
        headers/tools/analysis/method_reproducer/the_shortest/plus_for_each_reproducer/aio_plus_for_each_reproducer.h
        headers/tools/analysis/method_reproducer/the_shortest/multiply_for_each_reproducer/aio_multiply_for_each_reproducer.h
        headers/tools/analysis/method_reproducer/the_shortest/concat_for_each_reproducer/aio_concat_for_each_reproducer.h
        sources/lib/utils/file_utils/file_reader.c
        headers/lib/utils/file_utils/file_reader.h
        sources/lang/methods/analysis/method_reproducer/the_shortest/aio_the_shortest_reproducer.c
        sources/lang/methods/analysis/method_reproducer/the_shortest/plus_for_each_reproducer/aio_plus_for_each_reproducer.c
        sources/lang/methods/analysis/method_reproducer/default/aio_default_reproducer.c
        sources/lang/methods/analysis/method_reproducer/short/aio_short_reproducer.c
        sources/lang/methods/analysis/method_reproducer/the_shortest/concat_for_each_reproducer/aio_concat_for_each_reproducer.c
        sources/lang/methods/analysis/method_reproducer/the_shortest/multiply_for_each_reproducer/aio_multiply_for_each_reproducer.c
        headers/tools/parsers/aio_parser.h sources/tools/parsers/aio_parser.c
        sources/tools/parsers/int_parser/aio_int_parser.c
        sources/tools/parsers/dou_parser/aio_dou_parser.c
        sources/tools/parsers/cha_parser/aio_cha_parser.c
        sources/tools/parsers/str_parser/aio_str_parser.c
        sources/lib/utils/string_utils/split.c
        sources/lib/utils/string_utils/trim.c
        sources/lib/utils/string_utils/prefix_suffix.c
        headers/lib/pair/string_pair.h sources/lib/pair/string_pair.c
        sources/lib/utils/double_utils/string_to_double.c
        headers/lib/utils/boolean_utils/boolean_utils.h
        headers/lib/utils/int_utils/int_utils.h
        headers/lib/utils/double_utils/double_utils.h
        headers/lib/utils/error_utils/error_utils.h
        headers/lang/aio_method/value/aio_value.h)