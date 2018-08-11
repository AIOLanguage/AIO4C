#ifndef AIO_AIO_LOOP_SPIDER_H
#define AIO_AIO_LOOP_SPIDER_H

#include "../../aio_instructions/aio_instructions.h"
#include "../../../../../lib/point_watcher/point_watcher.h"
#include "../aio_spider.h"

typedef enum aio_loop_scope_type {
    AIO_LOOP_MODIFIER_SCOPE, AIO_LOOP_HEADER_SCOPE, AIO_LOOP_BODY_SCOPE, AIO_LOOP_WEAVING_SCOPE
} aio_loop_scope_type;

typedef enum aio_loop_header_scope_type {
    AIO_LOOP_HEADER_DEFINE, AIO_LOOP_HEADER_CONDITION, AIO_LOOP_HEADER_STEP
} aio_loop_header_scope_type;

typedef enum aio_loop_body_type {
    AIO_LOOP_UNDEFINED_BODY, AIO_LOOP_HAS_BODY
} aio_loop_body_type;

typedef struct aio_loop_materials {
    //States:
    aio_loop_scope_type scope_type;
    aio_loop_body_type body_type;
    aio_loop_header_scope_type header_scope_type;
    //Watchers:
    point_watcher *main_watcher;
    point_watcher *header_watcher;
    point_watcher *body_watcher;
    //Pointer variable:
    aio_variable_definition *pointer_definition;
    //Init pointer:
    aio_instruction *start_assign_instruction;
    //Condition:
    string condition;
    //Step:
    aio_instruction *step_assign_instruction;
} aio_loop_materials;

aio_spider *new_aio_loop_spider();

#endif //AIO_AIO_LOOP_SPIDER_H