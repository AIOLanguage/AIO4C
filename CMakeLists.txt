cmake_minimum_required(VERSION 3.10.3)

project(AIO_v_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers lib4aio)

add_executable(AIO_v_2

        main/main.cpp
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #HEADERS:
        headers
        #core:
        headers/aio_core/aio_core.h
        #lang:
        headers/aio_lang/aio_space/aio_file/aio_file.h
        headers/aio_lang/aio_types/aio_types.h
        headers/aio_runtime/aio_variable/aio_variable.h
        headers/aio_lang/aio_modifiers/aio_modifiers.h
        headers/aio_lang/aio_visibility/aio_visibility.h
        headers/aio_lang/aio_space/aio_space.h
        headers/aio_lang/aio_space/aio_scope/aio_scope.h
        headers/aio_lang/aio_space/aio_initializable/aio_class/aio_class.h
        headers/aio_lang/aio_field/aio_field.h
        headers/aio_lang/aio_invokable/aio_function/aio_function.h
        #aio_runtime:
        headers/aio_runtime/aio_bundle/aio_bundle.h
        headers/aio_runtime/aio_value/aio_value.h
        headers/aio_runtime/aio_value/advanced_functions/log_aio_value.h
        headers/aio_runtime/aio_value/advanced_functions/cast_aio_value.h
        headers/aio_runtime/aio_value/advanced_functions/compare_aio_value.h
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
        lib4aio/lib4aio_cpp_headers/utils/error_utils/error_utils.h
        lib4aio/lib4aio_cpp_headers/utils/string_utils/match.h
        lib4aio/lib4aio_cpp_headers/utils/string_utils/common.h
        lib4aio/lib4aio_cpp_headers/utils/string_utils/cast.h
        lib4aio/lib4aio_cpp_headers/utils/string_utils/split.h
        lib4aio/lib4aio_cpp_headers/utils/string_utils/trim.h
        lib4aio/lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h
        lib4aio/lib4aio_cpp_headers/utils/str_builder/str_builder.h
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #SOURCES:
        sources
        #lang:
        sources/aio_lang/aio_modifiers/aio_modifiers.cpp
        sources/aio_lang/aio_space/aio_scope/aio_scope.cpp
        sources/aio_lang/aio_space/aio_space.cpp
        #aio_runtime:
        sources/aio_runtime/aio_bundle/aio_bundle.cpp
        sources/aio_runtime/aio_value/aio_value.cpp
        sources/aio_runtime/aio_value/advanced_functions/log_aio_value.cpp
        sources/aio_runtime/aio_value/advanced_functions/cast_aio_value.cpp
        sources/aio_runtime/aio_value/advanced_functions/compare_aio_value.cpp
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
        lib4aio/lib4aio_cpp_sources/utils/string_utils/common.cpp
        lib4aio/lib4aio_cpp_sources/utils/string_utils/match.cpp
        lib4aio/lib4aio_cpp_sources/utils/string_utils/split.cpp
        lib4aio/lib4aio_cpp_sources/utils/string_utils/suffix_prefix.cpp
        lib4aio/lib4aio_cpp_sources/utils/string_utils/trim.cpp
        lib4aio/lib4aio_cpp_sources/utils/str_builder/str_builder.cpp
        lib4aio/lib4aio_cpp_sources/utils/error_utils/error_utils.cpp
        #---------------------------------------------------------------------------------------------------------------
        headers/aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.h sources/aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.cpp headers/aio_lang/aio_space/aio_initializable/aio_initializable.h sources/aio_lang/aio_space/aio_initializable/aio_initializable.cpp headers/aio_lang/aio_invokable/aio_constructor/aio_constructor.h headers/aio_lang/aio_invokable/aio_invokable.h sources/aio_lang/aio_field/aio_field.cpp headers/aio_lang/aio_annotatable/aio_annotatable.h sources/aio_lang/aio_annotatable/aio_annotatable.cpp headers/aio_parsing/aio_invokable_circuit/aio_invokable_circuit.h sources/aio_lang/aio_invokable/aio_invokable.cpp sources/aio_lang/aio_invokable/function/aio_function.cpp headers/aio_parsing/aio_invokable_instruction/aio_invokable_instruction.h headers/aio_runtime/aio_invokable_track/aio_invokable_track.h)