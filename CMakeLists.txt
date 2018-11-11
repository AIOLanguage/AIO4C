cmake_minimum_required(VERSION 3.10.3)

project(aio)

set(CMAKE_CXX_STANDARD 17)

#project:
add_subdirectory(com)

add_subdirectory(tests)

include_directories(com/headers com/sources)

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
)

#link google test:
target_link_libraries(aio gtest gtest_main)

#link lib4aio:
target_link_libraries(aio lib4aio)