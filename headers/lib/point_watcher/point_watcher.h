#ifndef POINTER_H
#define POINTER_H

enum point_mode {
    POINT_UNDEFINED_MODE, POINT_PASSIVE_MODE, POINT_ACTIVE_MODE
};

typedef struct point_watcher {
    int counter;
    int start_index;
    int end_index;
    enum point_mode mode;
} point_watcher;

point_watcher *new_point_watcher();

void reset_point_watcher(point_watcher *watcher);

void free_point_watcher(point_watcher *watcher);

#endif //POINTER_H