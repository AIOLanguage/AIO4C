#include <mem.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/file_utils/file_reader.h>
#include <lib/utils/collections/lists/string_list.h>
#include <aio_core/aio_core.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_bundle/aio_bundle.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_value/aio_value.h>
#include <lib/utils/type_utils/type.utils.h>
#include <aio_tools/aio_common_tools/aio_spider_nest/aio_spider_nest.h>
#include <aio_tools/aio_context_tools/aio_spider_nest/aio_context_spider_nest.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/string_utils/string_builder.h>
#include <stdio.h>
#include <lib/utils/error_utils/error_utils.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <aio_tools/aio_common_tools/aio_spider_nest/aio_abstract_spider/aio_spider.h>
#include <aio_core/aio_context/aio_context.h>
#include <lib/utils/int_utils/int_utils.h>
#include <lib/utils/boolean_utils/boolean_utils.h>

#define AIO_CONTEXT_TAG "AIO_CONTEXT"

#define AIO_CONTEXT_DEBUG

#ifdef AIO_CONTEXT_DEBUG

#endif

#define READ "r"

#define CHUNK 1024

aio_core *core;

static aio_context *new_aio_context()
{
    str_hook_list *list = new_str_hook_list();
    str_hook_iterator *iterator = new_str_hook_iterator();
    iterator->str_hook_list = list;
    //Create context:
    aio_context *context = new_object(sizeof(aio_context));
    context->context_state = AIO_CONTEXT_IS_ABSENT;
    context->break_points = new_int_list();
    context->source_code = new_str_hook_list();
    context->source_code_builder = new_string_builder();
    context->iterator = iterator;
    return context;
}

static void free_aio_context(aio_context *context)
{

}

aio_value_list *inflate_aio_context(aio_bundle *bundle)
{
    //Init result:
    aio_value_list *result = NULL;
    //Extract path:
    val context_path = bundle->path->source_string;
    val context = new_aio_context();
    val context_iterator = context->iterator;
    //Create file:
    val file_reference = fopen(context_path, READ);
    var reading_pointer = 0;
    if (file_reference) {
        while (TRUE) {
            const char symbol = (char) fgetc(file_reference);
            if (symbol != EOF) {
                while (context_iterator->position < reading_pointer) {
                    next_in_str_hook_iterator(context_iterator);
                }
                result = handle_symbol_for(core, context, symbol, bundle);
                if (result) {
                    break;
                } else {
                    reading_pointer++;
                }
            } else {
                break;
            }
        }
        fclose(file_reference);
    } else {
        throw_error_with_details(AIO_CONTEXT_TAG, "Can not open source file", context_path);
    }
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    free_aio_context(context);
    //------------------------------------------------------------------------------------------------------------------
    return result;
}