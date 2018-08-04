#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../headers/lang/aio_function/aio_bundle/aio_bundle.h"

//Passed JUnitTest!
aio_bundle *new_aio_bundle(string_list *input_values) {
    //Create the same aio_bundle:
    aio_bundle *bundle = calloc(1, sizeof(aio_bundle));
    //Set input values:
    bundle->input_values = input_values;
    //Create output values:
    bundle->output_values = new_string_list();
    return bundle;
}