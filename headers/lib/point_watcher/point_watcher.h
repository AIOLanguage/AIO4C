#ifndef POINTER_H
#define POINTER_H

#include "../utils/string_utils/string_utils.h"

enum point_mode {
    POINT_UNDEFINED_MODE, POINT_PASSIVE_MODE, POINT_ACTIVE_MODE
};

typedef struct point_watcher {
    int pointer;
    int start_index;
    int end_index;
    enum point_mode mode;
} point_watcher;

point_watcher *new_point_watcher();

point_watcher *new_point_watcher_with_pointer(const int pointer_value);

void reset_point_watcher(point_watcher *watcher);

void free_point_watcher(point_watcher *watcher);

string substring_by_point_watcher(const_string src, point_watcher *watcher);

#endif //POINTER_H