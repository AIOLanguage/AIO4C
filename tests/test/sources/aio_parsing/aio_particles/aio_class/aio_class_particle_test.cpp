//google test:
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_schemable/aio_schemable.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//parsing:
#include <aio_parsing/aio_particles/aio_class/aio_class_particle.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/color_utils/color_utils.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
//test:
#include <test/sources/aio_parsing/aio_particles/util/aio_particle_test_common.h>
#include <test/sources/aio_parsing/aio_particles/aio_class/trivial/aio_class_particle_trivial_test.h>
#include <test/sources/aio_parsing/aio_particles/aio_class/medium/aio_class_particle_medium_test.h>

#define TEST_PATH "../tests/test/sources/aio_parsing/aio_particles/aio_class/"

#define AIO_CLASS_PARTICLE_TEST_INFO_TAG "AIO_CLASS_PARTICLE_TEST_INFO"

using namespace lib4aio;

using testing::Eq;

class aio_class_particle_test : public testing::Test {
};

TEST_F(aio_class_particle_test, trivial)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "trivial/trivial.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(AIO_CLASS_PARTICLE_TEST_INFO_TAG,radius);

    //Create template:
    aio_space *space = new aio_space();

    //Test field:
    aio_orbit<aio_space>::create()
            ->set_pivot(space)
            ->set_radius(radius)
            ->set_particle(new aio_class_particle())
            ->spin()
            ->finish();

    //Expected class:
    const aio_class *actual_class = space->typenames->last();
    //Actual class:
    const aio_class *expected_class = create_class_for_aio_class_trivial_test();

    ASSERT_EQ(*expected_class, *actual_class);

    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete space;
    delete file_content;
    delete expected_class;
}

TEST_F(aio_class_particle_test, medium)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "medium/medium.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(AIO_CLASS_PARTICLE_TEST_INFO_TAG,radius);

    //Create template:
    aio_space *space = new aio_space();

    //Test field:
    aio_orbit<aio_space>::create()
            ->set_pivot(space)
            ->set_radius(radius)
            ->set_particle(new aio_class_particle())
            ->spin()
            ->finish();

    //Expected class:
    const aio_class *actual_class = space->typenames->last();
    //Actual class:
    const aio_class *expected_class = create_class_for_aio_class_medium_test();

    ASSERT_EQ(*expected_class, *actual_class);

    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete space;
    delete file_content;
    delete expected_class;
}

TEST_F(aio_class_particle_test, complex)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "complex/complex.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(AIO_CLASS_PARTICLE_TEST_INFO_TAG,radius);

    //Create template:
    aio_space *space = new aio_space();

    //Test field:
    aio_orbit<aio_space>::create()
            ->set_pivot(space)
            ->set_radius(radius)
            ->set_particle(new aio_class_particle())
            ->spin()
            ->finish();

    const array_list<aio_class> * classes = space->typenames;
    ASSERT_TRUE(classes->get_size() == 2);

    //Expected class 1:
    const aio_class *actual_class1 = space->typenames->get(0);
    //Actual class 1:
    const aio_class *expected_class1 = create_class_for_aio_class_medium_test();

    ASSERT_EQ(*expected_class1, *actual_class1);

    //Expected class 2:
    const aio_class *actual_class2 = space->typenames->get(1);
    //Actual class 2:
    const aio_class *expected_class2 = create_class_for_aio_class_trivial_test();

    ASSERT_EQ(*expected_class2, *actual_class2);

    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete space;
    delete file_content;
    delete expected_class1;
    delete expected_class2;
}