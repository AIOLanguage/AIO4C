cmake_minimum_required(VERSION 3.10)
project(AIO C)

set(CMAKE_C_STANDARD 11)

add_executable(AIO sources/main/main.c
        sources/lang/reservedNames/AIOReservedNamesContainer.c
        headers/lang/declarations/aio_declaration.h
        headers/lang/annotations/aio_annotation.h
        headers/reservedNames/AIOReservedNamesContainer.h
        headers/lang/object/AIOObject.h headers/lib/collections/lists/string_list.h
        sources/lib/collections/lists/string_list.c
        headers/lang/methods/bundle/aio_bundle.h
        headers/lang/methods/methodDefinition/aio_method_size_type.h
        headers/lang/methods/methodDefinition/aio_method_definition.h
        headers/lang/methods/variable/aio_variable.h headers/lang/types/aio_type.h
        sources/lang/types/aio_type.c sources/lib/collections/maps/AIOObjectMap.c
        headers/lib/collections/maps/AIOObjectMap.h headers/lang/object/objectManager/AIOObjectManager.h
        sources/lang/object/objectManager/AIOObjectManager.c
        headers/lib/collections/maps/AIOMethodDefinitionMap.h
        sources/lib/collections/maps/AIOMethodDefinitionMap.c
        sources/lang/object/AIOObject.c
        sources/lang/declarations/aio_declaration.c
        sources/lang/methods/methodDefinition/aio_method_definition.c
        sources/lang/annotations/aio_annotation.c
        headers/lib/collections/lists/AIOAnnotationList.h
        sources/lib/collections/lists/AIOAnnotationList.c
        sources/lang/methods/bundle/aio_bundle.c
        sources/lang/methods/variable/aio_variable.c
        headers/lang/methods/result/aio_result.h sources/lang/methods/result/aio_result.c
        headers/lang/methods/defaultMethodContainer/aio_default_method_container.h
        sources/lang/methods/defaultMethodContainer/aio_default_method_container.c
        sources/lib/utils/stringUtils/string_utils.c headers/lib/utils/stringUtils/string_utils.h
        headers/lang/methods/methodDefinition/aio_method_definition_builder.h
        sources/lang/methods/methodDefinition/aio_method_definition_builder.c
        headers/lang/methods/aio_method.h sources/lang/methods/aio_method.c
        headers/lang/methods/analysis/methodReproducer/aio_method_reproducer.h
        sources/lang/methods/analysis/methodReproducer/aio_method_reproducer.c
        headers/lib/collections/maps/AIOVariableMap.h
        sources/lib/collections/maps/AIOVariableMap.c
        headers/lang/methods/AIOMethodContainer.h
        headers/lang/methods/analysis/methodReproducer/theShortest/aio_the_shortest_reproducer.h
        headers/lang/methods/analysis/methodReproducer/default/aio_default_reproducer.h
        headers/lang/methods/analysis/methodReproducer/short/aio_short_reproducer.h
        headers/lib/utils/operationUtils/OperationUtils.h
        sources/lib/utils/operationUtils/OperationUtils.c
        headers/lang/methods/analysis/methodReproducer/theShortest/plusForEachReproducer/aio_plus_for_each_reproducer.h
        headers/lang/methods/analysis/methodReproducer/theShortest/multiplyForEachReproducer/aio_multiply_for_each_reproducer.h
        headers/lang/methods/analysis/methodReproducer/theShortest/concatForEachReproducer/aio_concat_for_each_reproducer.h sources/lib/utils/fileUtils/FileUtils.c headers/lib/utils/fileUtils/FileUtils.h
        sources/lang/methods/analysis/methodReproducer/theShortest/aio_the_shortest_reproducer.c sources/lang/methods/analysis/methodReproducer/theShortest/plusForEachReproducer/aio_plus_for_each_reproducer.c sources/lang/methods/analysis/methodReproducer/default/aio_default_reproducer.c sources/lang/methods/analysis/methodReproducer/short/aio_short_reproducer.c sources/lang/methods/analysis/methodReproducer/theShortest/concatForEachReproducer/aio_concat_for_each_reproducer.c sources/lang/methods/analysis/methodReproducer/theShortest/multiplyForEachReproducer/aio_multiply_for_each_reproducer.c headers/tools/parsers/AIOParser.h sources/tools/parsers/AIOParser.c sources/tools/parsers/intParser/AIOIntParser.c sources/tools/parsers/douParser/AIODouParser.c sources/tools/parsers/chaParser/AIOChaParser.c sources/tools/parsers/strParser/AIOStrParser.c sources/lib/utils/stringUtils/split.c sources/lib/utils/stringUtils/trim.c sources/lib/utils/stringUtils/prefix_suffix.c headers/lib/pair/string_pair.h sources/lib/pair/string_pair.c)