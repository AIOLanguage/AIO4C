#include <mem.h>
#include <aio_lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/file_utils/file_reader.h>
#include <lib/utils/collections/lists/string_list.h>
#include <aio_core/aio_core.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_bundle/aio_bundle.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_value/aio_value.h>

#define AIO_CONTEXT_TAG "AIO_CONTEXT"

#define AIO_CONTEXT_DEBUG

#ifdef AIO_CONTEXT_DEBUG

#endif

aio_core *core;

aio_value_list *inflate_aio_context(aio_bundle *bundle)
{
    return NULL;
}