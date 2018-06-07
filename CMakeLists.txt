cmake_minimum_required(VERSION 3.10)
project(AIO C)

set(CMAKE_C_STANDARD 11)

add_executable(AIO sources/main/main.c
        sources/lang/reservedNames/AIOReservedNamesContainer.c
        headers/lang/declarations/AIODeclaration.h
        headers/lang/annotations/AIOAnnotation.h
        headers/reservedNames/AIOReservedNamesContainer.h
        headers/lang/object/AIOObject.h headers/lib/collections/lists/StringList.h
        sources/lib/collections/lists/StringList.c
        headers/lang/methods/bundle/AIOBundle.h
        headers/lang/methods/methodDefinition/AIOMethodSizeType.h
        headers/lang/methods/methodDefinition/AIOMethodDefinition.h
        headers/lang/methods/variable/AIOVariable.h headers/lang/types/AIOType.h
        sources/lang/types/AIOType.c sources/lib/collections/maps/AIOObjectMap.c
        headers/lib/collections/maps/AIOObjectMap.h headers/lang/object/objectManager/AIOObjectManager.h
        sources/lang/object/objectManager/AIOObjectManager.c
        headers/lib/collections/maps/AIOMethodDefinitionMap.h
        sources/lib/collections/maps/AIOMethodDefinitionMap.c
        sources/lang/object/AIOObject.c
        sources/lang/declarations/AIODeclaration.c
        sources/lang/methods/methodDefinition/AIOMethodDefinition.c
        sources/lang/annotations/AIOAnnotation.c
        headers/lib/collections/lists/AIOAnnotationList.h
        sources/lib/collections/lists/AIOAnnotationList.c
        sources/lang/methods/bundle/AIOBundle.c
        sources/lang/methods/variable/AIOVariable.c
        headers/lang/methods/result/AIOResult.h sources/lang/methods/result/AIOResult.c headers/lang/methods/defaultMethodContainer/AIODefaultMethodContainer.h sources/lang/methods/defaultMethodContainer/AIODefaultMethodContainer.c sources/lib/utils/stringUtils/StringUtils.c headers/lib/utils/StringUtils.h headers/lang/methods/methodDefinition/AIOMethodDefinitionBuilder.h sources/lang/methods/methodDefinition/AIOMethodDefinitionBuilder.c)