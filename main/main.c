#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../headers/lang/aio_core/aio_core.h"
#include "../headers/lib/utils/string_utils/string_builder.h"

void make_test() {
    inflate_aio_core();
    const_string aio_file_path = "../aio_programs/test.aio";
    inflate_aio_context_and_put_in_core(aio_file_path);
    //찌꺼기 수집기 (Garbage collector):
    free((void *) aio_file_path);
}

int main() {
    make_test();
    return 0;
}