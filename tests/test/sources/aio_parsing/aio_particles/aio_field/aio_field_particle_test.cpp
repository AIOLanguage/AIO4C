//google test:
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_schemable/aio_schemable.h>
//parsing:
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
//runtime:
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.h>
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
#include <test/sources/aio_parsing/aio_particles/aio_field/trivial/aio_field_particle_trivial_test.h>
#include <test/sources/aio_parsing/aio_particles/aio_field/two_fields/aio_field_particle_two_fields_test.h>

#define TEST_PATH "../tests/test/sources/aio_parsing/aio_particles/aio_field/"

#define AIO_FIELD_PARTICLE_TEST_INFO_TAG "AIO_FIELD_PARTICLE_TEST_INFO"

using namespace lib4aio;

using testing::Eq;

class aio_field_particle_test : public testing::Test {
};


TEST_F(aio_field_particle_test, trivial)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "trivial/trivial.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(AIO_FIELD_PARTICLE_TEST_INFO_TAG, radius);

    //Create template:
    aio_schemable *schemable = new aio_schemable();

    //Test actual_field:
    aio_orbit<aio_schemable>::create()
            ->set_pivot(schemable)
            ->set_radius(radius)
            ->set_particle(new aio_field_particle())
            ->spin()
            ->finish();

    //Actual actual_field:
    const aio_field *actual_field = schemable->fields->last();
    //Expected actual_field:
    const aio_field *expected_field = create_field_for_aio_field_trivial_test();
    ASSERT_EQ(*actual_field, *expected_field);

    //Actual task:
    const aio_assign_task *actual_task = (aio_assign_task *) schemable->instructions->last();
    //Expected task:
    const aio_assign_task *expected_task = create_task_for_aio_field_trivial_test();
    ASSERT_TRUE(*actual_task == *expected_task);

    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete schemable;
    delete file_content;
    delete expected_task;
    delete expected_field;
}

TEST_F(aio_field_particle_test, two_fields)
{
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "two_fields/two_fields.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(AIO_FIELD_PARTICLE_TEST_INFO_TAG, radius);

    //Create template:
    aio_schemable *schemable = new aio_schemable();

    //Test fields:
    aio_orbit<aio_schemable>::create()
            ->set_pivot(schemable)
            ->set_radius(radius)
            ->set_particle(new aio_field_particle())
            ->spin()
            ->finish();

    const array_list<aio_field> *fields = schemable->fields;
    ASSERT_EQ(fields->get_size(), 2);

    //Actual field:
    const aio_field *actual_hello = fields->get(0);
    //Expected field:
    const aio_field *expected_hello = create_field_1_for_aio_two_fields_test();
    ASSERT_TRUE(*expected_hello == *actual_hello);

    //Actual bye:
    const aio_field *actual_bye = fields->get(1);
    //Expected bye:
    const aio_field *expected_bye = create_field_2_for_aio_two_fields_test();
    ASSERT_TRUE(*expected_bye == *actual_bye);

    const array_list<aio_task> *instructions = schemable->instructions;
    ASSERT_EQ(instructions->get_size(), 2);

    //Actual actual_task_1:
    const aio_assign_task *actual_task_1 = (aio_assign_task *) instructions->get(0);
    //Expected task 1:
    aio_assign_task *expected_task_1 = create_task_1_for_aio_two_fields_test();
    ASSERT_TRUE(*expected_task_1 == *actual_task_1);

    //Actual task 2:
    const aio_assign_task *actual_task_2 = (aio_assign_task *) instructions->get(1);
    //Expected task 2:
    const aio_assign_task *expected_task_2 = create_task_2_for_aio_two_fields_test();
    ASSERT_TRUE(*expected_task_2 == *actual_task_2);

    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete schemable;
    delete file_content;
    delete expected_hello;
    delete expected_bye;
    delete expected_task_1;
    delete expected_task_2;
}