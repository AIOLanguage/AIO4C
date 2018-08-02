#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/aio_core/aio_core.h"

void make_test() {
    inflate_aio_core();
    const_string aio_file_path = "../aio_programs/test.aio";
    inflate_aio_context_and_put_in_core(aio_file_path);
}

int main() {
    return 0;
}

//printf("\n-%s-\n", test)