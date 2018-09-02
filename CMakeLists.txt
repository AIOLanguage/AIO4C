project(AIO C)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -pedantic -Wall -Wextra")

add_definitions(-DSOME_IMPORTANT_DEFINITION)

include_directories(headers)

add_executable(${PROJECT_NAME}
        #---------------------------------------------------------------------------------------------------------------
        #MAIN:
        main/main.c
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #HEADERS:
        headers
        #lang:
        #tools:
        #lib:
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #SOURCES:
        sources
        #lang:
        #tools:
        #lib:
        #---------------------------------------------------------------------------------------------------------------
        headers/lib/utils/type_utils/type.utils.h)


#TODO: How make it???
#-I C:/Users/StarKRE/CLionProjects/AIO/headers

#add_definitions(-I headers-)
