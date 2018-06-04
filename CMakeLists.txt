cmake_minimum_required(VERSION 3.10)
project(AIO C)

set(CMAKE_C_STANDARD 11)

add_executable(AIO sources/interpreter/main.c
        sources/lang/reservedNames/AIOReservedNamesContainer.c
        headers/lang/declarations/AIODeclaration.h
        headers/lang/annotations/AIOAnnotation.h
        headers/reservedNames/AIOReservedNamesContainer.h
        headers/lang/object/AIOObject.h headers/lib/AIOMutableListOfString.h sources/lib/AIOMutableListOfString.c headers/lang/methods/bundle/AIOBundle.h headers/lang/methods/methodDefinition/AIOMethodSizeType.h headers/lang/methods/methodDefinition/AIOMethodDefinition.h headers/lang/methods/variable/AIOVariable.h)