#include <malloc.h>
#include "../../../headers/lib/point_watcher/point_watcher.h"

point_watcher *new_point_watcher() {
    point_watcher *watcher = calloc(1, sizeof(point_watcher));
    reset_point_watcher(watcher);
    return watcher;
}

void reset_point_watcher(point_watcher *watcher){
    watcher->pointer = 0;
    watcher->start_index = 0;
    watcher->end_index = 0;
    watcher->mode = POINT_PASSIVE_MODE;
}

void free_point_watcher(point_watcher *watcher) {
    free(watcher);
}

string substring_by_point_watcher(const_string src, point_watcher *watcher){
    return substring(src, watcher->start_index, watcher->end_index);
}