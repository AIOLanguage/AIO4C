#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../headers/lib/utils/stringUtils/string_utils.h"

AIOObjectManager *aio_object_manager;

void init() {
    initAIOObjectManager(&aio_object_manager);
}

void make() {
    init();
    char *path = "../aioPrograms/test.aio";
    build_aio_object_and_put_in_object_manager(aio_object_manager, path);
}

int main() {
    string_list *strings;
    new_string_list(&strings);
    add_in_string_list(strings, "    fwbm   ");
    add_in_string_list(strings, "ddv  ");
    add_in_string_list(strings, "");
    add_in_string_list(strings, "s");
    add_in_string_list(strings, "");
    printf("\nSIZE:-%d-\n", *strings->size);
    char **clean_strings = filter(strings->strings, *strings->size, is_not_empty_string);

    for (int i = 0; i < _msize(clean_strings) / 4; ++i) {
        strings->strings[i] = trim(clean_strings[i]);
        printf("\n-%s-\n", strings->strings[i]);
    }
    printf("\n-%s-\n", join_to_string(strings->strings, "|", *strings->size));

    char* a = "sffsfs";
    char* b = substring("ssw||||", 2, 4);
    printf("\nB   -%s-\n", b);
    printf("\nA   -%s-\n", a);


    concat_char_to_string(b, '!');;
    printf("\nCONCAT:-%s-\n", b);
    return 0;
}

//printf("\n-%s-\n", test)