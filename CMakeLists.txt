cmake_minimum_required(VERSION 3.10)
project(AIO C)

set(CMAKE_C_STANDARD 11)

add_executable(AIO sources/main/main.c
        sources/lang/reservedNames/aio_reserved_names_container.c
        headers/lang/declarations/aio_declaration.h
        headers/lang/annotations/aio_annotation.h
        headers/reserved_names/aio_reserved_names_container.h
        headers/lang/object/aio_object.h headers/lib/collections/lists/string_list.h
        sources/lib/collections/lists/string_list.c
        headers/lang/methods/bundle/aio_bundle.h
        headers/lang/methods/method_definition/aio_method_size_type.h
        headers/lang/methods/method_definition/aio_method_definition.h
        headers/lang/methods/variable/aio_variable.h headers/lang/types/aio_type.h
        sources/lang/types/aio_type.c sources/lib/collections/maps/aio_object_map.c
        headers/lib/collections/maps/aio_object_map.h headers/lang/object/object_manager/aio_object_manager.h
        sources/lang/object/objectManager/aio_object_manager.c
        headers/lib/collections/maps/aio_method_definition_map.h
        sources/lib/collections/maps/aio_method_definition_map.c
        sources/lang/object/aio_object.c
        sources/lang/declarations/aio_declaration.c
        sources/lang/methods/methodDefinition/aio_method_definition.c
        sources/lang/annotations/aio_annotation.c
        headers/lib/collections/lists/aio_annotation_list.h
        sources/lib/collections/lists/aio_annotation_list.c
        sources/lang/methods/bundle/aio_bundle.c
        sources/lang/methods/variable/aio_variable.c
        headers/lang/methods/result/aio_result.h sources/lang/methods/result/aio_result.c
        headers/lang/methods/default_method_container/aio_default_method_container.h
        sources/lang/methods/defaultMethodContainer/aio_default_method_container.c
        sources/lib/utils/stringUtils/string_utils.c headers/lib/utils/string_utils/string_utils.h
        headers/lang/methods/method_definition/aio_method_definition_builder.h
        sources/lang/methods/methodDefinition/aio_method_definition_builder.c
        headers/lang/methods/aio_method.h sources/lang/methods/aio_method.c
        headers/lang/methods/analysis/method_reproducer/aio_method_reproducer.h
        sources/lang/methods/analysis/methodReproducer/aio_method_reproducer.c
        headers/lib/collections/maps/aio_variable_map.h
        sources/lib/collections/maps/aio_variable_map.c
        headers/lang/methods/aio_method_container.h
        headers/lang/methods/analysis/method_reproducer/the_shortest/aio_the_shortest_reproducer.h
        headers/lang/methods/analysis/method_reproducer/default/aio_default_reproducer.h
        headers/lang/methods/analysis/method_reproducer/short/aio_short_reproducer.h
        headers/lib/utils/operation_utils/operation_utils.h
        sources/lib/utils/operationUtils/operation_utils.c
        headers/lang/methods/analysis/method_reproducer/the_shortest/plus_for_each_reproducer/aio_plus_for_each_reproducer.h
        headers/lang/methods/analysis/method_reproducer/the_shortest/multiply_for_each_reproducer/aio_multiply_for_each_reproducer.h
        headers/lang/methods/analysis/method_reproducer/the_shortest/concat_for_each_reproducer/aio_concat_for_each_reproducer.h sources/lib/utils/fileUtils/file_utils.c headers/lib/utils/file_utils/file_utils.h
        sources/lang/methods/analysis/methodReproducer/theShortest/aio_the_shortest_reproducer.c sources/lang/methods/analysis/methodReproducer/theShortest/plusForEachReproducer/aio_plus_for_each_reproducer.c sources/lang/methods/analysis/methodReproducer/default/aio_default_reproducer.c sources/lang/methods/analysis/methodReproducer/short/aio_short_reproducer.c sources/lang/methods/analysis/methodReproducer/theShortest/concatForEachReproducer/aio_concat_for_each_reproducer.c sources/lang/methods/analysis/methodReproducer/theShortest/multiplyForEachReproducer/aio_multiply_for_each_reproducer.c headers/tools/parsers/aio_parser.h sources/tools/parsers/aio_parser.c sources/tools/parsers/intParser/AIOIntParser.c sources/tools/parsers/douParser/AIODouParser.c sources/tools/parsers/chaParser/AIOChaParser.c sources/tools/parsers/strParser/AIOStrParser.c sources/lib/utils/stringUtils/split.c sources/lib/utils/stringUtils/trim.c sources/lib/utils/stringUtils/prefix_suffix.c headers/lib/pair/string_pair.h sources/lib/pair/string_pair.c)