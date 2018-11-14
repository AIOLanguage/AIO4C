//native:
#include <iostream>
//core:
#include <aio_core/aio_core.h>
//parsing:
#include <aio_parsing/aio_core_builder/aio_core_builder.h>
//runtime:
#include <aio_runtime/aio_ray/aio_ray.h>
//#include <aio_runtime/aio_ray/aio_ray.cpp>
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_bundle/aio_bundle.h>
#include <aio_runtime/aio_invoker/aio_invoker.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/color_utils/color_utils.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

/**
 * 태그들.
 */

#define AIO_CORE_ERROR_TAG "AIO_CORE_ERROR"

#define AIO_CORE_INFO_TAG "AIO_CORE_INFO"

#define AIO_CORE_DEBUG

#ifdef AIO_CORE_DEBUG

/**
 * 비즈니스 로직.
 */

#define START_FUNCTION_ARG_INDEX 2

#define ROOT_FUNCTION_NAME "main"

//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>


#endif

#ifdef _WIN32

#include <windows.h>

#endif

using namespace lib4aio;

aio_core *aio_core::create() {
    return new aio_core();
}

aio_core::aio_core() {}

aio_core *aio_core::configure() {
#ifdef _WIN32
    const unsigned UTF_8 = 65001;
    SetConsoleOutputCP(UTF_8);
    SetConsoleCP(UTF_8);
#elif __linux__
#include <sys/utsname.h>
    std::cout << BLUE << "\nAIO 이 시작됩다...\n\n" << RESET;
    utsname *sys_data = (utsname *) new_object(sizeof(utsname));
    uname(sys_data);
    std::cout << CYAN << sys_data->sysname << " 운영 체제가 감지되었습니다!\n\n";
    std::cout << "정부:\n"
              << sys_data->machine << "\n"
              << sys_data->nodename << "\n"
              << sys_data->release << "\n"
              << sys_data->version << "\n\n"
              << RESET;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete sys_data;
#elif  __APPLE__

    /**
     * Make sth config.
     */

#endif

    //------------------------------------------------------------------------------------------------------------------
    return this;
}

static aio_bundle *new_main_bundle(const int argc, char **argv, str_hook *file_path, aio_core *core_ptr) {
    const bool has_args = argc > START_FUNCTION_ARG_INDEX;
    struct_list *aio_args = new_struct_list(sizeof(aio_value));
    if (has_args) {
        for (unsigned i = START_FUNCTION_ARG_INDEX; i < argc; ++i) {
            const char *arg = argv[i];
            aio_value *aio_arg = new_aio_value_by_string(arg);
            add_struct_in_list(aio_args, aio_arg);
        }
    }
    str_hook *main_function_name = new str_hook(ROOT_FUNCTION_NAME);
    return new aio_bundle(core_ptr, file_path, main_function_name, aio_args);
}

aio_core *aio_core::inflate(char *build_path) {
    aio_core_builder::create()
            ->set_core(this)
            ->set_build_path(build_path)
            ->construct()
            ->finish();
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

void aio_core::finish() {
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete this;
}

array_list<str_hook> *aio_core::get_types() const {
    return this->types;
}

array_list<aio_file> *aio_core::get_files() const {
    return this->files;
}

aio_core *aio_core::invoke(int argc, char *const *argv) {
    return this;
}

//
//static array_list<str_hook> *new_aio_root_type_list()
//{
//    array_list<str_hook> *root_type_list = new array_list<str_hook>();
//    root_type_list->add(new str_hook(INTEGER));
//    root_type_list->add(new str_hook(DOUBLE));
//    root_type_list->add(new str_hook(STRING));
//    root_type_list->add(new str_hook(BOOLEAN));
//    root_type_list->add(new str_hook(ANY));
//    return root_type_list;
//}
//
//aio_runtime::aio_runtime(const aio_runtime_type type)
//{
//    this->runtime_type = type;
//    this->file_list = new array_list<aio_file>();
//    this->types = new_aio_root_type_list();
//    if (type == AIO_RUNTIME_TYPE_BUILD) {
//        this->types->add(new str_hook(AIOMAIN_TYPE));
//        this->types->add(new str_hook(AIOPROCESSOR_TYPE));
//    }
//}