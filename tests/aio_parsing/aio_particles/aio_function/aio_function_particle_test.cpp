//google test:
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_schemable/aio_schemable.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
//parsing:
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
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

TEST_F(aio_function_particle_test, sample_1)
{
    //Read sample:
    const str_builder *file_content = read_file_by_str_builder(TEST_PATH "trivial.txt");
    const str_hook *radius = new str_hook(file_content->get_string(), 0, file_content->size());

    //Print pretty file content:
    print_radius(radius);

    //Create template:
    aio_space *schemable = new aio_space();
    aio_function_particle *function_particle = new aio_function_particle();

    //Test field:
    aio_orbit<aio_space>::create()
            ->set_pivot(schemable)
            ->set_radius(radius)
            ->set_particle(function_particle)
            ->spin()
            ->finish();

    const aio_function *function = schemable->functions->last();


    //------------------------------------------------------------------------------------------------------------------
    //Free:
    delete schemable;
    delete file_content;
}