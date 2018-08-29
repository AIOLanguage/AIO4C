#include <malloc.h>
#include "../../../../headers/lang/aio_function/aio_bundle/aio_bundle.h"
#include "../../../../headers/lang/aio_function/aio_value/aio_value.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_bundle *new_aio_bundle(aio_value_list *input_values)
{
    aio_bundle *bundle = new_object(sizeof(aio_bundle));
    bundle->input_values = input_values;
    bundle->output_values = new_aio_value_list();
    return bundle;
}

void free_aio_bundle(aio_bundle *bundle)
{
    aio_value_list *input_list = bundle->input_values;
    aio_value_list *output_list = bundle->output_values;
    free_aio_value_list(input_list);
    free_aio_value_list(output_list);
    free(bundle);
}