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

#define TEST_PATH "../tests/aio_parsing/aio_particles/aio_function/"

#define AIO_FUNCTION_PARTICLE_TEST_INFO_TAG "AIO_FUNCTION_PARTICLE_TEST_INFO"

using namespace lib4aio;

using testing::Eq;

class aio_function_particle_test : public testing::Test {
};

static void print_radius(const str_hook *radius)
{
    log_info(AIO_FUNCTION_PARTICLE_TEST_INFO_TAG, "\n---------------------------");
    log_info_str_hook(AIO_FUNCTION_PARTICLE_TEST_INFO_TAG, "SAMPLE: \n\n" GREEN, radius);
    log_info(RESET AIO_FUNCTION_PARTICLE_TEST_INFO_TAG, "\n-------------------------\n");
}

static bool assert_function_equals_content(
        const aio_function *actual_function,
        const char *expected_name,
        const array_list<aio_field> *expected_args,
        const char *expected_output_type,
        const aio_visibility expected_visibility,
        const bool is_array_output,
        const array_list<aio_task> expected_instructions
)
{
    if (!actual_function->name->equals_string(expected_name)) {
        return false;
    }
    const unsigned actual_arg_count = actual_function->arg_count;
    if (actual_arg_count != expected_args->get_size()) {
        return false;
    }
    const array_list<aio_field> *actual_args = actual_function->fields;
    for (unsigned i = 0; i < actual_arg_count; ++i) {
        if (!actual_args->get(i)->equals(expected_args->get(i))) {
            return false;
        }
    }
    if (!actual_function->output_type->equals_string(expected_output_type)) {
        return false;
    }
    if (actual_function->visibility_type != expected_visibility) {
        return false;
    }
    if (actual_function->is_array_output != is_array_output) {
        return false;
    }
    const array_list<aio_task> actual_tasks = actual_function->instructions;
    const unsigned size = expected_instructions.get_size();
    for (unsigned j = 0; j < size; ++j) {
        if (!actual_tasks.get(j)->equals(expected_instructions.get(j))) {
            return false;
        }
    }
    return true;
}

TEST_F(aio_function_particle_test, sample_1)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "trivial.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(radius);

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

    for (unsigned i = 0; i < 2; ++i) {
        log_aio_field(function->fields->get(i));
    }

    //Create expected args:
    aio_field *arg1 = new aio_field();
    arg1->name = new str_hook("a");
    arg1->type = new str_hook(INTEGER);
    arg1->visibility_type = AIO_VISIBILITY_LOCAL;
    arg1->is_static = false;
    arg1->is_const = true;
    arg1->is_array = false;

    aio_field *arg2 = new aio_field();
    arg2->name = new str_hook("b");
    arg2->type = new str_hook(INTEGER);
    arg2->visibility_type = AIO_VISIBILITY_LOCAL;
    arg2->is_static = false;
    arg2->is_const = true;
    arg2->is_array = false;

    array_list<aio_field> *args = new array_list<aio_field>(true);
    args->add(arg1);
    args->add(arg2);

    //Create expected tasks:
    aio_return_task *return_task = new aio_return_task();
    return_task->set_value(const_cast<char *>("a + b"));

    array_list<aio_task> *tasks = new array_list<aio_task>(true);
    tasks->add(return_task);

    ASSERT_TRUE(assert_function_equals_content(function, "sum", args, AUTO, AIO_VISIBILITY_UNDEFINED, false, tasks));
    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete space;
    delete file_content;
}