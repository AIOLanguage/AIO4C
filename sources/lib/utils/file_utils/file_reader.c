#include "../../../../headers/lib/pair/string_pair.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../headers/lib/utils/file_utils/file_reader.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_context/aio_context.h"
#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>

const_string read_file_and_join_to_string_without_comments(const_string path) {
    int read_position = 0;
    size_t code_size = CHUNK;
    string aio_code = calloc(code_size, sizeof(char));
    char pointer;
    //Create file:
    FILE *file;
    if ((file = fopen(path, "r")) == NULL) {
        throw_error("cannot open source-file");
    }
    while ((pointer = (char) fgetc(file)) != EOF) {
        if (read_position == code_size) {
            code_size *= 2;
            aio_code = realloc(aio_code, code_size);
        }
        aio_code[read_position] = pointer;
        read_position++;
    }
    fclose(file);
    printf("\nLOADED!\n\n%s\n", aio_code);
    return "";
}