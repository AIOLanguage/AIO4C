#ifndef POINT_WATCHER_H
#define POINT_WATCHER_H

#include "../string_utils/string_utils.h"

typedef enum point_watcher_mode {
    POINT_UNDEFINED_MODE, POINT_PASSIVE_MODE, POINT_ACTIVE_MODE
} point_watcher_mode;

typedef struct point_watcher {
    int pointer;
    int start;
    int end;
    point_watcher_mode mode;
} point_watcher;

typedef const point_watcher const_point_watcher;

point_watcher *new_point_watcher();

point_watcher *new_point_watcher_with_pointer(const int pointer_value);

void reset_point_watcher(point_watcher *watcher);

void free_point_watcher(point_watcher *watcher);

string substring_by_point_watcher(const_string src, const_point_watcher *watcher);

#endif //POINT_WATCHER_H