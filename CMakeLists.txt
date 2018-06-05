cmake_minimum_required(VERSION 3.10)
project(AIO C)

set(CMAKE_C_STANDARD 11)

add_executable(AIO sources/interpreter/main.c
        sources/lang/reservedNames/AIOReservedNamesContainer.c
        headers/lang/declarations/AIODeclaration.h
        headers/lang/annotations/AIOAnnotation.h
        headers/reservedNames/AIOReservedNamesContainer.h
        headers/lang/object/AIOObject.h headers/lib/lists/AIOMutableListOfString.h sources/lib/lists/AIOMutableListOfString.c headers/lang/methods/bundle/AIOBundle.h headers/lang/methods/methodDefinition/AIOMethodSizeType.h headers/lang/methods/methodDefinition/AIOMethodDefinition.h headers/lang/methods/variable/AIOVariable.h headers/lang/types/AIOType.h sources/lang/types/AIOType.c sources/lib/maps/AIOMutableObjectMap.c headers/lib/maps/AIOMutableObjectMap.h headers/lang/object/objectManager/AIOObjectManager.h sources/lang/object/objectManager/AIOObjectManager.c headers/lib/maps/AIOMutableMethodDefinitionMap.h sources/lib/maps/AIOMutableMethodDefinitionMap.c sources/lang/object/AIOObject.c sources/lang/declarations/AIODeclaration.c sources/lang/methods/methodDefinition/AIOMethodDefinition.c sources/lang/annotations/AIOAnnotation.c headers/lib/lists/AIOMutableListOfAnnotations.h sources/lib/lists/AIOMutableListOfAnnotations.c)