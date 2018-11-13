cmake_minimum_required(VERSION 3.10.3)

project(aio)

set(CMAKE_CXX_STANDARD 17)

#project:
add_subdirectory(com)

add_subdirectory(tests)

include_directories(com/headers com/sources)

include_directories(tests)

#lib4aio:
add_subdirectory(libs/lib4aio)

include_directories(libs/lib4aio)

#google test:
add_subdirectory(libs/googletest)

include_directories(
        libs/googletest/googletest/include
        libs/googletest/googlemock/include
)

#project:
add_executable(
        #---------------------------------------------------------------------------------------------------------------
        #PROJECT NAME:
        aio
        #---------------------------------------------------------------------------------------------------------------
        #MAIN:
        main/main.cpp
        #---------------------------------------------------------------------------------------------------------------
        ${aioheaders}
        ${aiosources}
        ${aiotest}
        com/headers/aio_parsing/aio_expression/aio_expression_parser.h com/sources/aio_parsing/aio_expression/aio_expression_parser.cpp com/sources/aio_parsing/aio_expression/aio_parsers/aio_int_parser.cpp com/headers/aio_runtime/aio_result/aio_result.h com/sources/aio_parsing/aio_expression/aio_assistant/aio_expression_assistant.cpp com/sources/aio_parsing/aio_expression/aio_parsers/aio_double_parser.cpp com/sources/aio_parsing/aio_expression/aio_parsers/aio_string_parser.cpp com/sources/aio_parsing/aio_expression/aio_parsers/aio_boolean_parser.cpp com/sources/aio_parsing/aio_expression/aio_analyser/aio_analyser.cpp)

#link google test:
target_link_libraries(aio gtest gtest_main)

#link lib4aio:
target_link_libraries(aio lib4aio)