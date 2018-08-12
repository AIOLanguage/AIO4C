#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"

void throw_error(const_string message) {
    perror(message);
    free((void *) message);
    exit(1);
}

void throw_error_with_tag(const_string tag, const_string message){
    printf("\nERROR: %s: %s\n", tag, message);
    free((void *) message);
    exit(1);
}

void throw_error_string_with_details(const_string tag, const_string message, const_string value){
    printf("\nERROR: %s: %s %s\n", tag, message, value);
    free((void *) message);
    exit(1);
}