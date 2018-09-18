#include <aio_core/aio_core.h>
#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <aio_parsing/aio_inflater/aio_inflater.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_bundle/aio_bundle.h>
#include <aio_runtime/aio_invoker/aio_invoker.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_CORE_TAG "AIO_CORE"

#define AIO_CORE_DEBUG

#ifdef AIO_CORE_DEBUG

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

#define FILE_PATH_INDEX 1

#define START_FUNCTION_ARG_INDEX 2

#define ROOT_FUNCTION_NAME "main"

using namespace lib4aio;

static aio_bundle *create_main_bundle(
        const int argc,
        char **argv,
        const aio_core *core,
        const str_hook *file_path
)
{
    const bool has_args = argc > START_FUNCTION_ARG_INDEX;
    struct_list *aio_args = new_struct_list(sizeof(aio_value));
    if (has_args) {
        for (unsigned i = START_FUNCTION_ARG_INDEX; i < argc; ++i) {
            const char *arg = argv[i];
            aio_value *aio_arg = new_aio_value_by_string(arg);
            add_struct_in_list(aio_args, aio_arg);
        }
    }
    const str_hook *main_function_name = new str_hook(ROOT_FUNCTION_NAME);
    aio_bundle *main_bundle = new aio_bundle(core, file_path, main_function_name, aio_args);
    return main_bundle;
}

void aio_core::inflate(const int argc, char **argv)
{
    const bool has_program_args = argc > 1;
    if (has_program_args) {
        aio_core *core = new aio_core();
#ifdef AIO_CORE_DEBUG
        log_info(AIO_CORE_TAG, "아이어 핵심을 만들었습니다");
#endif
        const str_hook *program_entry_path = inflate_aio_context(core, argv[FILE_PATH_INDEX]);
        aio_bundle *main_bundle = create_main_bundle(argc, argv, core, program_entry_path);
        invoke_main_function(main_bundle);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기:
        delete core;
        //--------------------------------------------------------------------------------------------------------------
    } else {
        throw_error_with_tag(AIO_CORE_TAG, "'build.aio_core'에 경로를 예상했습니다 (Expected path to build.aio_core).");
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
    delete this->build_script_data;
}

const array_list<str_hook> *aio_core::get_types() const
{
    return this->types;
}


const array_list<aio_file> *aio_core::get_file_list() const
{
    return this->file_list;
}

void aio_core::set_build_script_data(const char *build_script_data)
{
    if (!this->build_script_data) {
        this->build_script_data = build_script_data;
    } else {
        throw_error_with_tag(AIO_CORE_TAG, "'build script data' is already loaded");
    }
}
