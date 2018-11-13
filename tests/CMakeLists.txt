set(
        aioparsing

        #PARTICLE:
        #---------------------------------------------------------------------------------------------------------------

        #COMMON:
        tests/test/sources/aio_parsing/aio_particles/util/aio_particle_test_common.h
        tests/test/sources/aio_parsing/aio_particles/util/aio_particle_test_common.cpp

        #FIELD:
        tests/test/sources/aio_parsing/aio_particles/aio_field/aio_field_particle_test.cpp
        #TRIVIAL:
        tests/test/sources/aio_parsing/aio_particles/aio_field/trivial/aio_field_particle_trivial_test.h
        tests/test/sources/aio_parsing/aio_particles/aio_field/trivial/aio_field_particle_trivial_test.cpp
        #TWO FIELDS:
        tests/test/sources/aio_parsing/aio_particles/aio_field/two_fields/aio_field_particle_two_fields_test.h
        tests/test/sources/aio_parsing/aio_particles/aio_field/two_fields/aio_field_particle_two_fields_test.cpp

        #FUNCTION:
        tests/test/sources/aio_parsing/aio_particles/aio_function/aio_function_particle_test.cpp
        #TRIVIAL:
        tests/test/sources/aio_parsing/aio_particles/aio_function/trivial/aio_function_particle_trivial_test.h
        tests/test/sources/aio_parsing/aio_particles/aio_function/trivial/aio_function_particle_trivial_test.cpp
        #MEDIUM:
        tests/test/sources/aio_parsing/aio_particles/aio_function/medium/aio_function_particle_medium_test.h
        tests/test/sources/aio_parsing/aio_particles/aio_function/medium/aio_function_particle_medium_test.cpp

        #CLASS:
        tests/test/sources/aio_parsing/aio_particles/aio_class/aio_class_particle_test.cpp
        #TRIVIAL:
        tests/test/sources/aio_parsing/aio_particles/aio_class/trivial/aio_class_particle_trivial_test.h
        tests/test/sources/aio_parsing/aio_particles/aio_class/trivial/aio_class_particle_trivial_test.cpp
        #MEDIUM:
        tests/test/sources/aio_parsing/aio_particles/aio_class/medium/aio_class_particle_medium_test.h
        tests/test/sources/aio_parsing/aio_particles/aio_class/medium/aio_class_particle_medium_test.cpp
        #---------------------------------------------------------------------------------------------------------------

        #EXPRESSION:
        #---------------------------------------------------------------------------------------------------------------

        #ANALYSER:
        tests/test/sources/aio_parsing/aio_expression/aio_analyser/aio_analyser_test.cpp

        #PARSING:
        #---------------------------------------------------------------------------------------------------------------
)

set(
        aiotest
        #---------------------------------------------------------------------------------------------------------------
        ${aioparsing}
        #---------------------------------------------------------------------------------------------------------------
        PARENT_SCOPE
)