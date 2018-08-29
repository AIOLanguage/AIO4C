#ifndef POINT_WATCHER_H
#define POINT_WATCHER_H

typedef enum point_watcher_mode {
    POINT_WATCHER_UNDEFINED_MODE, POINT_WATCHER_PASSIVE_MODE, POINT_WATCHER_ACTIVE_MODE
} point_watcher_mode;

typedef struct point_watcher {
    int pointer;
    int start;
    int end;
    enum point_watcher_mode mode;
} point_watcher;

struct point_watcher *new_point_watcher();

struct point_watcher *new_point_watcher_with_pointer(const int pointer_value);

void reset_point_watcher(struct point_watcher *watcher);

void free_point_watcher(struct point_watcher *watcher);

char *substring_by_point_watcher(const char *src, const struct point_watcher *watcher);

/**
 * Typedef utils.
 */

typedef const struct point_watcher const_point_watcher;

#endif //POINT_WATCHER_H