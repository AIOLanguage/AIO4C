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
        headers/aio_lang/aio_lexer/aio_lexer.h
        #aio_utils:
        headers/aio_utils/aio_value/aio_value.h
        headers/aio_utils/aio_bundle/aio_bundle.h
        #aio_tools:
        #lib4aio:
        lib4aio/lib4aio_cpp_headers/utils/char_utils/char_utils.h
        lib4aio/lib4aio_cpp_headers/utils/log_utils/log_utils.h
        lib4aio/lib4aio_cpp_headers/utils/memory_utils/memory_utils.h
        lib4aio/lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h
        lib4aio/lib4aio_cpp_headers/utils/array_list_utils/array_list.h
        lib4aio/lib4aio_cpp_headers/utils/point_watcher/point_watcher.h
        lib4aio/lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h
        lib4aio/lib4aio_cpp_headers/utils/point_watcher/str_hook_watcher/str_point_watcher.h
        lib4aio/lib4aio_cpp_headers/utils/str_hook_utils/str_hook_iterator/str_hook_iterator.h
        lib4aio/lib4aio_cpp_headers/utils/struct_list/struct_list.h
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #SOURCES:
        sources
        #lang:
        sources/aio_lang/aio_lexer/aio_lexer.cpp
        sources/aio_utils/aio_bundle/aio_bundle.cpp
        #aio_utils:
        #aio_tools:
        #lib4aio:
        lib4aio/lib4aio_cpp_sources/utils/char_utils/char_utils.cpp
        lib4aio/lib4aio_cpp_sources/utils/log_utils/log_utils.cpp
        lib4aio/lib4aio_cpp_sources/utils/memory_utils/memory_utils.cpp
        lib4aio/lib4aio_cpp_sources/utils/point_watcher/str_hook_watcher/str_point_watcher.cpp
        lib4aio/lib4aio_cpp_sources/utils/point_watcher/point_watcher.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook/str_hook.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook/advanced_functions/str_hook_cast.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook/advanced_functions/str_hook_error.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook/advanced_functions/str_hook_log.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook/advanced_functions/str_hook_matcher.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook/advanced_functions/str_hook_split.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook/advanced_functions/str_hook_trim.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook_iterator/str_hook_iterator.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook_list/advanced_functions/str_hook_list_log.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook_list/advanced_functions/str_hook_trim.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_hook_utils/str_hook_list/str_hook_list.cpp
        lib4aio/lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp
        lib4aio/lib4aio_cpp_sources/utils/struct_list/struct_list.cpp
        #---------------------------------------------------------------------------------------------------------------
        sources/aio_utils/aio_value/aio_value.cpp sources/aio_utils/aio_value/advanced_functions/compare_aio_value.cpp sources/aio_utils/aio_value/advanced_functions/cast_aio_value.cpp sources/aio_utils/aio_value/advanced_functions/log_aio_value.cpp headers/aio_lang/aio_types/aio_type.h lib4aio/lib4aio_cpp_headers/utils/string_utils/match.h lib4aio/lib4aio_cpp_headers/utils/string_utils/common.h lib4aio/lib4aio_cpp_headers/utils/string_utils/cast.h lib4aio/lib4aio_cpp_headers/utils/string_utils/split.h lib4aio/lib4aio_cpp_headers/utils/string_utils/trim.h lib4aio/lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h lib4aio/lib4aio_cpp_headers/utils/error_utils/error_utils.h headers/aio_utils/aio_value/advanced_functions/compare_aio_value.h headers/aio_utils/aio_value/advanced_functions/cast_aio_value.h headers/aio_utils/aio_value/advanced_functions/log_aio_value.h)