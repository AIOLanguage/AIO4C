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

#define TEST_PATH "../tests/aio_parsing/aio_particles/aio_field/"

#define AIO_FIELD_PARTICLE_TEST_INFO_TAG "AIO_FIELD_PARTICLE_TEST_INFO"

using namespace lib4aio;

using testing::Eq;

class aio_field_particle_test : public testing::Test {
};

static bool assert_field_equals_content(const aio_field *field, bool is_const, const char *name, const char *type)
{
    return field->is_const == is_const && field->name->equals_string(name) && field->type->equals_string(type);
}

static bool assert_assign_task_equals_content(const aio_assign_task *task, const char *name, const char *value)
{
    return task->get_name()->equals_string(name) && are_equal_strings(task->get_value(), value);
}

static void print_radius(const str_hook *radius)
{
    log_info(AIO_FIELD_PARTICLE_TEST_INFO_TAG, "\n---------------------------");
    log_info_str_hook(AIO_FIELD_PARTICLE_TEST_INFO_TAG, "SAMPLE: \n\n" GREEN, radius);
    log_info(RESET AIO_FIELD_PARTICLE_TEST_INFO_TAG, "\n-------------------------\n");
}

TEST_F(aio_field_particle_test, sample_1)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "trivial.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());
    //Print pretty file content:
    print_radius(radius);
    //Create template:
    aio_schemable *schemable = new aio_schemable();
    //Test field:
    aio_orbit<aio_schemable>::create()
            ->set_pivot(schemable)
            ->set_radius(radius)
            ->set_particle(new aio_field_particle())
            ->spin()
            ->finish();
    const aio_field *field = schemable->fields->last();
    ASSERT_TRUE(assert_field_equals_content(field, true, "x", AUTO));
    const aio_assign_task *task = (aio_assign_task *) schemable->instructions->last();
    ASSERT_TRUE(assert_assign_task_equals_content(task, "x", "3"));
    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete schemable;
    delete file_content;
}

TEST_F(aio_field_particle_test, sample_2)
{
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "two_fields.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());
    //Print pretty file content:
    print_radius(radius);
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
    const aio_field *hello = fields->get(0);
    ASSERT_TRUE(assert_field_equals_content(hello, false, "hello", "String"));
    const aio_field *bye = fields->get(1);
    ASSERT_TRUE(assert_field_equals_content(bye, true, "bye", "String"));
    const array_list<aio_task> *instructions = schemable->instructions;
    ASSERT_EQ(instructions->get_size(), 2);
    const aio_assign_task *task_1 = (aio_assign_task *) instructions->get(0);
    ASSERT_TRUE(assert_assign_task_equals_content(task_1, "hello", "'Hello, AIO!'"));
    const aio_assign_task *task_2 = (aio_assign_task *) instructions->get(1);
    ASSERT_TRUE(assert_assign_task_equals_content(task_2, "bye", "'Bye, AIO'"));
    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete schemable;
    delete file_content;
}