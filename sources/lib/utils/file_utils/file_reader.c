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
    string source_code = "";
    //Create file:
    FILE *file;
    //Create line buffer:
    char buffer[CHUNK];
    if ((file = fopen(path, "r")) == NULL) {
        throw_error("cannot open source-file");
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        if (starts_with_prefix(buffer, AIO_COMMENTS)){
            continue;
        }
        //Try to separate code from comments:
        string_array dirty_code_line_with_comments = split_by_string(buffer, AIO_COMMENTS);
        const_string dirty_code_line = dirty_code_line_with_comments[0];
        const_string clean_code_line = trim(dirty_code_line);
        concat_char_to_string(&source_code, '\n');
        concat_string_to_string(source_code, clean_code_line);
    }
    fclose(file);
    return source_code;
}