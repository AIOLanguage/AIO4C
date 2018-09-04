cmake_minimum_required(VERSION 3.12)

project(AIO_v_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers lib)

add_executable(AIO_v_2
        #---------------------------------------------------------------------------------------------------------------
        #MAIN:
        main/main.cpp
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #HEADERS:
        headers
        #lang:
        #tools:
        #lib:
        lib/headers/utils/log_utils/log_utils.h
        lib/headers/utils/memory_utils/memory_utils.h
        lib/headers/utils/string_list_cls/string_list_cls.h
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #SOURCES:
        sources
        #lang:
        #tools:
        #lib:
        lib/sources/utils/log_utils/log_utils.cpp
        lib/sources/utils/memory_utils/memory_utils.cpp
        lib/sources/utils/string_list_cls/string_list_cls.cpp
        #---------------------------------------------------------------------------------------------------------------
        )