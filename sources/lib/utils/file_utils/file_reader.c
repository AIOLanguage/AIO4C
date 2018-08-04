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

string get_code_without_comments(const_string file_content) {
    string_list *clean_line_list = new_string_list();
    string_array lines = split_by_string(file_content, "\n");
    for (int i = 0; i < strings_size(lines); ++i) {
        const_string line = lines[i];
        if (!starts_with_prefix(line, AIO_COMMENTS) && !is_empty_string(line)) {
            string_array dirty_line_with_comments = split_by_string(line, AIO_COMMENTS);
            string clean_line = dirty_line_with_comments[0];
            printf("\nCLEAN!\n-%s-\n", clean_line);
            if (is_not_empty_string(clean_line)) {
                add_in_string_list(clean_line_list, clean_line);
            }
        }
    }
    printf("\nBUILD LIST\n");
    for (int j = 0; j < clean_line_list->size; ++j) {
        printf("-%s-\n", clean_line_list->strings[j]);
    }
    string clean_code = join_to_string(clean_line_list->strings, "\n", clean_line_list->size);
    //찌꺼기 수집기 (Garbage collector):
    printf("\nREADY!\n\n%s\n", clean_code);

    return clean_code;
}

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
    string clean_code = get_code_without_comments(file_content);
    //Garbage collector:


    return clean_code;
}