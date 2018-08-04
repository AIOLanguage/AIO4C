#include <malloc.h>
#include "../../../headers/lib/point_watcher/point_watcher.h"

point_watcher *new_point_watcher() {
    point_watcher *watcher = calloc(1, sizeof(point_watcher));
    watcher->start_index = 0;
    watcher->end_index = 0;
    watcher->mode = POINT_UNDEFINED;
    return watcher;
}

void free_point_watcher(point_watcher *watcher) {
    free(watcher);
}