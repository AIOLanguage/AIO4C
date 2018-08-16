#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../headers/lang/aio_core/aio_core.h"
#include "../headers/lib/utils/string_utils/string_builder.h"

//TODO: 'claw_string'과 utils 만들다:
//TODO: Create struct claw_string && utils: typedef claw_string{ string source_code; int start_index; int end_index }

void make_test() {
    inflate_aio_core();
    const_string aio_file_path = "../aio_programs/loop.aio";
    inflate_aio_context_and_put_in_core(aio_file_path);
    //찌꺼기 수집기 (Garbage collector):
    free((void *) aio_file_path);
}

int main() {
    make_test();
    return 0;
}