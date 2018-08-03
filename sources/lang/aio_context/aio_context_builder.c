#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_types/aio_type.h"
#include "../../../headers/lib/collections/maps/aio_variable_map.h"

const_string extract_name_from_path(const_string path) {
    if (ends_with_suffix(path, AIO_SUFFIX)) {
        const int last_path_index = strlen(path) - 1;
        for (int i = last_path_index; i >= 0; --i) {
            const char symbol = path[i];
            //패스 파일 이름 (Pass file name):
            if (symbol == '/') {
                const_string file_name = substring(path, i + 1, last_path_index - i - AIO_SUFFIX_LENGTH);
                if (is_word(file_name)) {
                    return file_name;
                } else {
                    throw_error("잘못된 .aio 파일 이름 (Invalid .aio file name!");
                }
            }
        }
    } else {
        throw_error("파일이 .aio 타입을 없는 (The file doesn't have .aio type!");
    }
}

aio_function_definition *delve_method_definition(const_string source_code, int *pointer_reference);

void collect_method_definitions_in_manager(aio_context *context) {
    const_string source_code = context->source_code;
    aio_function_definition_map *method_definition_map = context->function_manager->function_definition_map;
    const int code_line_length = strlen(source_code);
    if (code_line_length == 0) {
        throw_error("aio context is empty!");
    }
    int pointer = 0;
    while (pointer < code_line_length) {
        aio_function_definition *method_definition = delve_method_definition(source_code, &pointer);
        put_aio_method_definition_in_map(method_definition_map, method_definition);
    }
}