#include <aio_core/aio_core.h>
#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_bundle/aio_bundle.h>
#include <aio_parsing/aio_inflater/aio_inflater.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>

#define AIO_CORE_TAG "AIO_CORE"

#define FILE_PATH_INDEX 1

#define START_FUNCTION_ARG_INDEX 2

#define ROOT_FUNCTION_NAME "main"

using namespace lib4aio;

static aio_bundle *create_bundle_of_main_function(
        const int argc,
        char **argv,
        aio_core *core,
        const str_hook *main_function_entry_point
)
{
    const bool has_args = argc > START_FUNCTION_ARG_INDEX;
    struct_list *aio_args = new_struct_list(sizeof(aio_value));
    if (has_args) {
        for (int i = START_FUNCTION_ARG_INDEX; i < argc; ++i) {
            const char *arg = argv[i];
            aio_value *aio_arg = new_aio_value_by_string(arg);
            add_struct_in_list(aio_args, aio_arg);
        }
    }
    aio_bundle * main_bundle = new aio_bundle()
    return aio_args;
}

void aio_core::inflate(const int argc, char **argv)
{
    const bool has_not_program_args = argc <= 1;
    if (has_not_program_args) {
        throw_error_with_tag(AIO_CORE_TAG, "'build.aio_core'에 경로를 예상했습니다 (Expected path to build.aio_core).");
    } else {
        aio_core *core = new aio_core();
        str_hook *program_entry_path = inflate_aio_context_for(core, argv[FILE_PATH_INDEX]);
        aio_bundle *main_bundle = create_bundle_of_main_function(argc, argv, aio_core);

    }
}

aio_core::aio_core()
{
    this->file_list = new array_list<aio_file>();
    this->types = new array_list<str_hook>();
}

aio_core::~aio_core()
{
    this->file_list->free_elements();
    this->types->free_elements();
    delete this->file_list;
    delete this->types;
}

const array_list<str_hook> *aio_core::get_types() const
{
    return this->types;
}

const array_list<aio_file> *aio_core::get_file_list() const
{
    return this->file_list;
}