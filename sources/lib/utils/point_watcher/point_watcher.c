#include <malloc.h>
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"

point_watcher *new_point_watcher() {
    point_watcher *watcher = calloc(1, sizeof(point_watcher));
    reset_point_watcher(watcher);
    return watcher;
}

point_watcher *new_point_watcher_with_pointer(const int pointer_value){
    point_watcher *watcher = new_point_watcher();
    watcher->pointer = pointer_value;
    return watcher;
}

void reset_point_watcher(point_watcher *watcher){
    watcher->pointer = 0;
    watcher->start = 0;
    watcher->end = 0;
    watcher->mode = POINT_PASSIVE_MODE;
}

void free_point_watcher(point_watcher *watcher) {
    free(watcher);
}

string substring_by_point_watcher(const_string src, const_point_watcher *watcher){
    return substring(src, watcher->start, watcher->end);
}