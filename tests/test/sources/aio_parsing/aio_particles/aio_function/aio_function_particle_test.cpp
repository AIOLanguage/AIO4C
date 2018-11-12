//google test:
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_schemable/aio_schemable.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
//parsing:
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
//runtime:
#include <aio_runtime/aio_task/aio_task.h>
#include <aio_runtime/aio_task/aio_return/aio_return_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/color_utils/color_utils.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.h>
//tests:
#include <test/sources/aio_parsing/aio_particles/util/aio_particle_test_common.h>
#include <test/sources/aio_parsing/aio_particles/aio_function/medium/aio_function_particle_medium_test.h>
#include <test/sources/aio_parsing/aio_particles/aio_function/trivial/aio_function_particle_trivial_test.h>

#define TEST_PATH "../tests/test/sources/aio_parsing/aio_particles/aio_function/"

#define AIO_FUNCTION_PARTICLE_TEST_INFO_TAG "AIO_FUNCTION_PARTICLE_TEST_INFO"

#define AIO_FUNCTION_PARTICLE_TEST_DEBUG

using namespace lib4aio;

using testing::Eq;

class aio_function_particle_test : public testing::Test {
};


TEST_F(aio_function_particle_test, trivial)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "trivial/trivial.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(AIO_FUNCTION_PARTICLE_TEST_INFO_TAG, radius);

    //Create template:
    aio_space *space = new aio_space();
    aio_function_particle *function_particle = new aio_function_particle();

    //Test field:
    aio_orbit<aio_space>::create()
            ->set_pivot(space)
            ->set_radius(radius)
            ->set_particle(function_particle)
            ->spin()
            ->finish();

    //Check space:
    ASSERT_EQ(1, space->functions->get_size());

    //Actual function:
    const aio_function *function = space->functions->last();
    //Expected function:
    const aio_function *expected_function = create_function_for_aio_function_trivial_test();
    ASSERT_TRUE(*expected_function == *function);

    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete space;
    delete file_content;
    delete expected_function;
}

TEST_F(aio_function_particle_test, medium)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "medium/medium.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(AIO_FUNCTION_PARTICLE_TEST_INFO_TAG, radius);

    //Create template:
    aio_space *space = new aio_space();
    aio_function_particle *function_particle = new aio_function_particle();

    //Test field:
    aio_orbit<aio_space>::create()
            ->set_pivot(space)
            ->set_radius(radius)
            ->set_particle(function_particle)
            ->spin()
            ->finish();

    //Check space:
    ASSERT_EQ(1, space->functions->get_size());

    //Get function:
    const aio_function *function = space->functions->last();

    //Create expected function:
    aio_function *expected_function = create_function_for_aio_function_medium_test();

    ASSERT_TRUE(*expected_function == *function);
    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete space;
    delete file_content;
    delete expected_function;
}

TEST_F(aio_function_particle_test, complex)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "complex/complex.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(AIO_FUNCTION_PARTICLE_TEST_INFO_TAG, radius);

    //Create template:
    aio_space *space = new aio_space();
    aio_function_particle *function_particle = new aio_function_particle();

    //Test field:
    aio_orbit<aio_space>::create()
            ->set_pivot(space)
            ->set_radius(radius)
            ->set_particle(function_particle)
            ->spin()
            ->finish();

    //Check space:
    const array_list<aio_function> *functions = space->functions;
    ASSERT_EQ(2, functions->get_size());

    //Create expected functions:
    aio_function *expected_function_1 = create_function_for_aio_function_trivial_test();
    aio_function *expected_function_2 = create_function_for_aio_function_medium_test();

    ASSERT_TRUE(*expected_function_1 == *functions->get(0));
    ASSERT_TRUE(*expected_function_2 == *functions->get(1));

    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete space;
    delete file_content;
    delete expected_function_1;
    delete expected_function_2;
}