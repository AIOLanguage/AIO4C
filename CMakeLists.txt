cmake_minimum_required(VERSION 3.10)
project(AIO C)

set(CMAKE_C_STANDARD 11)

add_executable(AIO sources/interpreter/main.c sources/lang/reservedNames/AIOReservedNamesContainer.c headers/lang/declarations/AIODeclaration.h headers/lang/annotations/AIOAnnotation.h headers/reservedNames/AIOReservedNamesContainer.h sources/utils/stringUtils/StringUtils.cpp headers/utils/stringUtils/StringUtils.h)