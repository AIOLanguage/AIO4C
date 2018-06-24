#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../headers/lang/methods/bundle/aio_bundle.h"

//Passed JUnitTest!
aio_bundle* new_aio_bundle(string_list *input_values) {
    //Create the same bundle:
    aio_bundle* bundle = calloc(1, sizeof(aio_bundle));
    if (bundle == NULL){
        perror("cannot allocate memory for aio_bundle");
        exit(1);
    }
    //Set input values:
    bundle->input_values = input_values;
    //Create output values:
    bundle->output_values = new_string_list();
}