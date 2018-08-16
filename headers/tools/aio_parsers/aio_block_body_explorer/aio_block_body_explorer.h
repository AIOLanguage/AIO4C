#ifndef AIO_FUNCTION_BODY_EXPLORER_H
#define AIO_FUNCTION_BODY_EXPLORER_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../../lib/point_watcher/point_watcher.h"

void explore_bounds(const_string source_code, int *start_index, int *end_index,
                    boolean (*opening_bound_condition)(const char),
                    boolean (*closing_bound_condition)(const char));

void explore_header_body(const_string source_code, int *start_index, int *end_index);

void explore_block_body(const_string source_code, int *start_index, int *end_index);

const_boolean is_end_of_block_body(const_string function_body_string, point_watcher *watcher);

#endif //AIO_FUNCTION_BODY_EXPLORER_H