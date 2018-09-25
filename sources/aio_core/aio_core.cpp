#include <cstring>
#include <iostream>
#include <sys/utsname.h>
#include <aio_core/aio_core.h>
#include <aio_lang/aio_types/aio_types.h>
#include <aio_parsing/aio_context_inflater/aio_context_inflater.h>
#include <aio_runtime/aio_runtime.h>
#include <aio_runtime/aio_build_runtime.h>
#include <aio_runtime/aio_program_runtime.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_bundle/aio_bundle.h>
#include <lib4aio_cpp_headers/utils/color_utils/color_utils.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_CORE_TAG "AIO_CORE"

#define AIO_CORE_DEBUG

#ifdef AIO_CORE_DEBUG

#define START_FUNCTION_ARG_INDEX 2

#define ROOT_FUNCTION_NAME "main"

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <aio_runtime/aio_invoker/aio_invoker.h>

#endif

using namespace lib4aio;

aio_core *aio_core::create()
{
    return new aio_core();
}

aio_core::aio_core()
{
    aio_build_runtime *build_runtime = new aio_build_runtime();
    this->build_runtime = build_runtime;
    this->program_runtime = new aio_program_runtime(build_runtime);
}

aio_core *aio_core::inflate_aio_config()
{
#ifdef _WIN32_
#include <windows.h>
    const unsigned UTF_8 = 65001;
    SetConsoleOutputCP(UTF_8);
    SetConsoleCP(UTF_8);
#elif __linux__

#elif  __APPLE__
#endif
    std::cout << BLUE << "\nAIO 이 시작됩다...\n\n" << RESET;
    utsname *os_data = (utsname *) new_object(sizeof(utsname));
    uname(os_data);
    std::cout << CYAN << os_data->sysname << " 운영 체제가 감지되었습니다!\n\n";
    std::cout << "정부:\n"
              << os_data->machine << "\n"
              << os_data->nodename << "\n"
              << os_data->release << "\n"
              << os_data->version << "\n\n"
              << RESET;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete os_data;
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

aio_bundle *aio_core::new_main_bundle(const int argc, char **argv, const str_hook *file_path)
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
    aio_bundle *main_bundle = new aio_bundle(this->program_runtime, file_path, main_function_name, aio_args);
    return main_bundle;
}

aio_core *aio_core::inflate_aio_context(const char *script_path)
{
    aio_context_inflater::create()
            ->set_core(this)
            ->set_script_path(script_path)
            ->inflate()
            ->destroy();
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

aio_core *aio_core::invoke_aio_context(int argc, char **argv)
{
    const str_hook *main_path = new str_hook(this->program_runtime->get_entry_path());
    aio_bundle *bundle = new_main_bundle(argc, argv, main_path);
    invoke_main_function(bundle);
    //------------------------------------------------------------------------------------------------------------------
    struct_list *input_list = bundle->get_input_values();
    struct_list *output_list = bundle->get_output_values();
    free_structs_in_list(
            input_list, [](void *it) {
                free_aio_value((aio_value *) it);
            });
    free_structs_in_list(
            output_list, [](void *it) {
                free_aio_value((aio_value *) it);
            });
    delete bundle;
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

void aio_core::destroy()
{
    delete this->build_runtime;
    delete this->program_runtime;
    delete this;
}