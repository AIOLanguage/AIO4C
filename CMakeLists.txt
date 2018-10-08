cmake_minimum_required(VERSION 3.10.3)

project(aio)

set(CMAKE_CXX_STANDARD 17)

#project directories
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

#project files:
add_executable(
        #---------------------------------------------------------------------------------------------------------------
        #PROJECT NAME:
        aio
        #---------------------------------------------------------------------------------------------------------------
        #MAIN:
        com/main/main.cpp
        #---------------------------------------------------------------------------------------------------------------

        #---------------------------------------------------------------------------------------------------------------
        #HEADERS:
        com/headers
        #core:
        com/headers/aio_core/aio_core.h
        #lang:
        com/headers/aio_lang/aio_space/aio_space.h
        com/headers/aio_lang/aio_field/aio_field.h
        com/headers/aio_lang/aio_types/aio_types.h
        com/headers/aio_lang/aio_modifiers/aio_modifiers.h
        com/headers/aio_lang/aio_schemable/aio_schemable.h
        com/headers/aio_lang/aio_invokable/aio_invokable.h
        com/headers/aio_lang/aio_space/aio_file/aio_file.h
        com/headers/aio_lang/aio_space/aio_scope/aio_scope.h
        com/headers/aio_lang/aio_visibility/aio_visibility.h
        com/headers/aio_lang/aio_annotatable/aio_annotatable.h
        com/headers/aio_lang/aio_inheritable/aio_inheritable.h
        com/headers/aio_lang/aio_invokable/aio_function/aio_function.h
        com/headers/aio_lang/aio_space/aio_initializable/aio_initializable.h
        com/headers/aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.h
        com/headers/aio_lang/aio_invokable/aio_constructor/aio_constructor.h
        com/headers/aio_lang/aio_space/aio_initializable/aio_class/aio_class.h
        #parsing:
        com/headers/aio_parsing/aio_core_builder/aio_core_builder.h
        com/headers/aio_parsing/aio_particles/aio_scope/aio_scope_particle.h
        com/headers/aio_parsing/aio_particles/aio_class/aio_class_particle.h
        com/headers/aio_parsing/aio_particles/aio_field/aio_field_particle.h
        com/headers/aio_parsing/aio_particles/aio_import/aio_import_particle.h
        com/headers/aio_parsing/aio_particles/aio_function/aio_function_particle.h
        com/headers/aio_parsing/aio_particles/aio_constructor/aio_constructor_particle.h
        #runtime:
        com/headers/aio_runtime/aio_ray/aio_ray.h
        com/headers/aio_runtime/aio_task/aio_task.h
        com/headers/aio_runtime/aio_value/aio_value.h
        com/headers/aio_runtime/aio_bundle/aio_bundle.h
        com/headers/aio_runtime/aio_invoker/aio_invoker.h
        com/headers/aio_runtime/aio_variable/aio_variable.h
        com/headers/aio_runtime/aio_task/aio_assign/aio_assign_task.h
        com/headers/aio_runtime/aio_value/advanced_functions/log_aio_value.h
        com/headers/aio_runtime/aio_value/advanced_functions/cast_aio_value.h
        com/headers/aio_runtime/aio_value/advanced_functions/compare_aio_value.h

        #---------------------------------------------------------------------------------------------------------------
        #SOURCES:
        com/sources
        #core:
        com/sources/aio_core/aio_core.cpp
        #lang:
        com/sources/aio_lang/aio_space/aio_space.cpp
        com/sources/aio_lang/aio_field/aio_field.cpp
        com/sources/aio_lang/aio_invokable/aio_invokable.cpp
        com/sources/aio_lang/aio_modifiers/aio_modifiers.cpp
        com/sources/aio_lang/aio_space/aio_file/aio_file.cpp
        com/sources/aio_lang/aio_schemable/aio_schemable.cpp
        com/sources/aio_lang/aio_space/aio_scope/aio_scope.cpp
        com/sources/aio_lang/aio_inheritable/aio_inheritable.cpp
        com/sources/aio_lang/aio_annotatable/aio_annotatable.cpp
        com/sources/aio_lang/aio_invokable/function/aio_function.cpp
        com/sources/aio_lang/aio_invokable/constructor/aio_constructor.cpp
        com/sources/aio_lang/aio_space/aio_initializable/aio_initializable.cpp
        com/sources/aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.cpp
        com/sources/aio_lang/aio_space/aio_initializable/aio_class/aio_class.cpp
        #parsing:
        com/sources/aio_parsing/aio_context_inflater/aio_core_builder.cpp
        com/sources/aio_parsing/aio_particles/aio_field/aio_field_particle.cpp
        com/sources/aio_parsing/aio_particles/aio_class/aio_class_particle.cpp
        com/sources/aio_parsing/aio_particles/aio_scope/aio_scope_particle.cpp
        com/sources/aio_parsing/aio_particles/aio_import/aio_import_particle.cpp
        com/sources/aio_parsing/aio_particles/aio_function/aio_function_particle.cpp
        com/sources/aio_parsing/aio_particles/aio_constructor/aio_constructor_particle.cpp
        #runtime:
        com/sources/aio_runtime/aio_ray/aio_ray.cpp
        com/sources/aio_runtime/aio_task/aio_task.cpp
        com/sources/aio_runtime/aio_value/aio_value.cpp
        com/sources/aio_runtime/aio_bundle/aio_bundle.cpp
        com/sources/aio_runtime/aio_invoker/aio_invoker.cpp
        com/sources/aio_runtime/aio_variable/aio_variable.cpp
        com/sources/aio_runtime/aio_task/aio_assign/aio_assign_task.cpp
        com/sources/aio_runtime/aio_value/advanced_functions/log_aio_value.cpp
        com/sources/aio_runtime/aio_value/advanced_functions/cast_aio_value.cpp
        com/sources/aio_runtime/aio_value/advanced_functions/compare_aio_value.cpp

        #---------------------------------------------------------------------------------------------------------------
        #TESTS:
        tests/aio_parsing/aio_particles/aio_field_particle_test.cpp)

#link google test:
target_link_libraries(aio gtest gtest_main)

#link lib4aio:
target_link_libraries(aio lib4aio)