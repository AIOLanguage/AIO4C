#include <malloc.h>
#include "../../../headers/lib/point_watcher/point_watcher.h"

point_watcher *new_point_watcher() {
    point_watcher *watcher = calloc(1, sizeof(point_watcher));
    reset_point_watcher(watcher);
    return watcher;
}

void reset_point_watcher(point_watcher *watcher){
    watcher->counter = 0;
    watcher->start_index = 0;
    watcher->end_index = 0;
    watcher->mode = POINT_UNDEFINED;
}

void free_point_watcher(point_watcher *watcher) {
    free(watcher);
}