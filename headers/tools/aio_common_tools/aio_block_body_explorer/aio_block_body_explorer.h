#ifndef AIO_FUNCTION_BODY_EXPLORER_H
#define AIO_FUNCTION_BODY_EXPLORER_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../../lib/utils/point_watcher/point_watcher.h"

void explore_aio_context_bounds(const_string source_code, int *start_index, int *end_index,
                                boolean (*opening_bound_condition)(const char),
                                boolean (*closing_bound_condition)(const char));

void explore_aio_header_bounds(const_string source_code, int *start_index, int *end_index);

void explore_aio_block_bounds(const_string source_code, int *start_index, int *end_index);

const_boolean has_context_rest(const_string body_string, point_watcher *watcher);

#endif //AIO_FUNCTION_BODY_EXPLORER_H