#include <ctype.h>
#include <mem.h>
#include "../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../../../headers/lang/aio_core/aio_core.h"

enum output_mode {
    OUTPUT_UNDEFINED, SINGLE_OUTPUT_MODE, MULTI_OUTPUT_MODE
};

string_list *delve_output_types(const_string source_code, int *pointer_reference) {
    string_list *output_type_list = new_string_list();
    const size_t source_code_length = strlen(source_code);
    enum output_mode mode = OUTPUT_UNDEFINED;
    point_watcher *watcher = new_point_watcher();
    for (int i = *pointer_reference; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        //Is space or line break:
        const_boolean is_space_or_break_line = is_space(symbol) || is_line_break(symbol);
        //Starts with symbol:
        if (isalpha(symbol) && mode == OUTPUT_UNDEFINED) {
            //Single return type:
            mode = SINGLE_OUTPUT_MODE;
            watcher->start_index = i;
            watcher->mode = POINT_READING_MODE;
        }
        //Starts with parenthesis:
        if (is_open_parenthesis(symbol) && mode == OUTPUT_UNDEFINED) {
            //Multi return type:
            mode = MULTI_OUTPUT_MODE;
            watcher->start_index = i + 1;
            watcher->mode = POINT_READING_MODE;
        }
        //Stop reading single or multi output mode:
        if ((is_space_or_break_line && mode == SINGLE_OUTPUT_MODE)
            || (is_close_parenthesis(symbol) && mode == MULTI_OUTPUT_MODE)) {
            watcher->end_index = i;
            *pointer_reference = i;
            break;
        }
    }
    //Get type content string:
    string type_content = substring(source_code, watcher->start_index, watcher->end_index);
    switch (mode) {
        case SINGLE_OUTPUT_MODE:
            if (contains_aio_type_in_set(type_content)) {
                add_string_in_list(output_type_list, type_content);
                return output_type_list;
            } else {
                throw_error("Aio set doesn't support type!");
            }
        case MULTI_OUTPUT_MODE: {
            const_string_array dirty_types = split_by_comma(type_content);
            const int type_number = strings_size(dirty_types);
            const_string_array clean_types = trim_all(dirty_types, type_number);
            for (int i = 0; i < type_number; ++i) {
                string type = clean_types[i];
                if (contains_aio_type_in_set(type)) {
                    add_string_in_list(output_type_list, type);
                } else {
                    throw_error("Aio set doesn't support type!");
                }
            }
            return output_type_list;
        }
        case OUTPUT_UNDEFINED:
            throw_error("출력 유형들을 칮을 수 없습니다! (Output types not found!)");
    }
}