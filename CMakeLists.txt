cmake_minimum_required(VERSION 3.12)

project(AIO_v_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers lib4aio)

add_executable(AIO_v_2
        #---------------------------------------------------------------------------------------------------------------
        #MAIN:
        main/main.cpp
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #HEADERS:
        headers
        #lang:
        #aio_tools:
        #lib4aio:
        lib4aio/lib4aio_cpp_headers/utils/log_utils/log_utils.h
        lib4aio/lib4aio_cpp_headers/utils/memory_utils/memory_utils.h
        lib4aio/lib4aio_cpp_headers/utils/str_hook/str_hook.h
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #SOURCES:
        sources
        #lang:
        #aio_tools:
        #lib4aio:
        lib4aio/lib4aio_cpp_sources/utils/log_utils/log_utils.cpp
        lib4aio/lib4aio_cpp_sources/utils/memory_utils/memory_utils.cpp
        #---------------------------------------------------------------------------------------------------------------
        )