#ifndef AIO_DEFAULT_LOOP_HEADER_SPIDER_H
#define AIO_DEFAULT_LOOP_HEADER_SPIDER_H

#include "../../aio_spider.h"
#include "../aio_loop_spider.h"

typedef struct aio_main_loop_materials;

typedef enum aio_default_loop_header_scope_type {
    AIO_DEFAULT_LOOP_HEADER_DECLARATION_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_VALUE_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_CONDITION_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_STEP_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_WEAVING_SCOPE
} aio_default_loop_header_scope_type;

typedef enum aio_default_loop_header_pointer_declaration_type {
    AIO_DEFAULT_LOOP_HEADER_VARIABLE_UNDEFINED,
    AIO_DEFAULT_LOOP_HEADER_WAS_MUTABLE_MODIFIER,
    AIO_DEFAULT_LOOP_HEADER_MUTABLE,
    AIO_DEFAULT_LOOP_HEADER_IMMUTABLE,
    AIO_DEFAULT_LOOP_HEADER_REFERENCE,
    AIO_DEFAULT_LOOP_HEADER_ABSENT
} aio_default_loop_header_pointer_declaration_type;

typedef enum aio_default_loop_header_step_scope {
    AIO_DEFAULT_LOOP_HEADER_STEP_VARIABLE,
    AIO_DEFAULT_LOOP_HEADER_STEP_EQUAL_SIGN_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_STEP_VALUE_SCOPE
} aio_default_loop_header_step_type;

typedef struct aio_default_loop_header_materials {
    //States:
    aio_default_loop_header_scope_type scope_type;
    aio_default_loop_header_pointer_declaration_type declaration_type;
    aio_default_loop_header_step_type step_type;
    //Watchers:
    point_watcher *main_watcher;
    point_watcher *condition_watcher;
    //Data:
    string_list *pointer_data_list;
    string init_value;
    string loop_condition;
} aio_default_loop_header_materials;

typedef struct aio_default_loop_header_spider {

} aio_default_loop_header_spider;

struct aio_spider *new_aio_default_loop_header_spider(struct aio_main_loop_materials *parent_materials);

#endif //AIO_DEFAULT_LOOP_HEADER_SPIDER_H