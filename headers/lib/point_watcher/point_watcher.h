#ifndef POINTER_H
#define POINTER_H

enum point_mode {
    POINT_UNDEFINED, POINT_WATCHING_MODE, POINT_READING_MODE
};

typedef struct point_watcher {
    int start_index;
    int end_index;
    enum point_mode mode;
} point_watcher;

point_watcher *new_point_watcher();

void free_point_watcher(point_watcher *watcher);

#endif //POINTER_H