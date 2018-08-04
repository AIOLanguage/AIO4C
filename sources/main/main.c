#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/aio_core/aio_core.h"

void make_test() {
    inflate_aio_core();
    const_string aio_file_path = "../aio_programs/test.aio";
    inflate_aio_context_and_put_in_core(aio_file_path);
    //찌꺼기 수집기 (Garbage collector):
    free((void *) aio_file_path);
}

int main() {
    make_test();


//    string_list *list = new_string_list();
//    add_in_string_list(list, "fffff");
//    add_in_string_list(list, "\n");
//    for (int i = 0; i < list->size; ++i) {
//        printf("\n-%s-\n", list->strings[i]);
//    }



    return 0;
}

void throw_error(const_string message) {
    perror(message);
    exit(1);
}

//printf("\n-%s-\n", test)