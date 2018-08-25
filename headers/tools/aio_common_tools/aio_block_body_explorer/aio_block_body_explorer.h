#ifndef AIO_FUNCTION_BODY_EXPLORER_H
#define AIO_FUNCTION_BODY_EXPLORER_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../../lib/utils/point_watcher/point_watcher.h"

void explore_aio_context_bounds(const char *source_code, int *start_index, int *end_index,
                                _Bool (*opening_bound_condition)(const char),
                                _Bool (*closing_bound_condition)(const char));

void explore_aio_header_bounds(const char *source_code, int *start_index, int *end_index);

void explore_aio_block_bounds(const char *source_code, int *start_index, int *end_index);

//TODO: Question about unicode ¯\_(ツ)_/¯:
void explore_aio_block_quote_bounds(const char *source_code, int *start_index, int *end_index);

_Bool has_context_rest(const char *body_string, struct point_watcher *watcher);

#endif //AIO_FUNCTION_BODY_EXPLORER_H