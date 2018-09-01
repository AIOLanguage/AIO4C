#include <mem.h>
#include <aio_lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/file_utils/file_reader.h>
#include <lang/aio_core/aio_core.h>
#include <lib/utils/collections/lists/string_list.h>
#include <lang/aio_function/aio_bundle/aio_bundle.h>
#include <tools/aio_common_tools/utils/aio_value.h>

#define AIO_CONTEXT_TAG "AIO_CONTEXT"

#define AIO_CONTEXT_DEBUG

#ifdef AIO_CONTEXT_DEBUG

#endif

aio_core *core;

aio_value_list* inflate_aio_context(aio_bundle *bundle)
{










    //Read source code:
    string source_code = read_file_and_join_to_string_without_comments(context_path);
    const size_t source_code_length = strlen(source_code);
    const_boolean is_empty_context = source_code_length > 0;
    if (!is_empty_context) {
        add_source_code_in_aio_core(source_code);
        find_context_materials(source_code, source_code_length);
    }
}

//static void add_source_code_in_aio_core(string source_code)
//{
//    string_list *source_code_list = core->source_code_list;
//    add_string_in_list(source_code_list, source_code);
//}
//
//static void find_context_materials(const_string source_code, const size_t source_code_length)
//{
//    //함수들 찾기 준비하기 (Prepare to find functions):
//    int context_pointer = 0;
//    aio_function_definition_list *global_function_definition_list = core->global_function_definition_list;
//    while (context_pointer < source_code_length) {
//        const_aio_function_definition *global_function_definition = conjure_aio_function_definition(
//                source_code,
//                &context_pointer
//        );
//        add_aio_function_definition_in_list(global_function_definition_list, global_function_definition);
//    }
//}