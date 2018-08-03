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

string read_file_and_join_to_string_without_comments(const_string path) {
    int read_position = 0;
    size_t code_size = CHUNK;
    string file_content = calloc(code_size, sizeof(char));
    char read_pointer;
    //Create file:
    FILE *file_reference;
    if ((file_reference = fopen(path, "r")) == NULL) {
        throw_error("cannot open source file");
    }
    while ((read_pointer = (char) fgetc(file_reference)) != EOF) {
        if (read_position == code_size) {
            code_size *= 2;
            file_content = realloc(file_content, code_size);
        }
        file_content[read_position] = read_pointer;
        read_position++;
    }
    fclose(file_reference);
    printf("\nLOADED!\n\n%s\n", file_content);
    //Remove comments:
    string_list *clean_line_list = new_string_list();
    const_string_array lines = (const_string_array) split_by_string(file_content, "\n");
    for (int i = 0; i < strings_size(lines); ++i) {
        const_string line = lines[i];
        if (!starts_with_prefix(line, AIO_COMMENTS)) {
            string_array dirty_line_with_comments = split_by_string(line, AIO_COMMENTS);
            add_in_string_list(clean_line_list, dirty_line_with_comments[0]);
        }
    }
    string clean_code = join_to_string(clean_line_list->strings, "\n", clean_line_list->size);
    //Delete local variables:
    printf("\nREADY!\n\n%s\n", clean_code);
    return clean_code;
}