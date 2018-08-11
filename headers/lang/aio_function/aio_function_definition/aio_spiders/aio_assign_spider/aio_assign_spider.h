#ifndef AIO_ASSIGN_SPIDER_H
#define AIO_ASSIGN_SPIDER_H

#include "../../../../../lib/point_watcher/point_watcher.h"
#include "../../../../../lib/collections/lists/string_list.h"
#include "../aio_spider.h"

/**
 * Assign spider materials.
 */

typedef enum aio_assign_scope_type {
    AIO_ASSIGN_DECLARATION_SCOPE, AIO_ASSIGN_EQUAL_SIGN_IN_SCOPE, AIO_ASSIGN_VALUE_SCOPE, AIO_ASSIGN_WEAVING_SCOPE
} aio_assign_scope_type;

typedef enum aio_assign_variable_declaration_type {
    AIO_ASSIGN_UNDEFINED_DECLARATION, AIO_ASSIGN_WAS_MUTABLE_MODIFIER, AIO_ASSIGN_WILL_DEFINED, AIO_ASSIGN_REFERENCE,
    AIO_ASSIGN_IMMUTABLE, AIO_ASSIGN_MUTABLE
} aio_assign_variable_declaration_type;

typedef struct aio_assign_materials {
    //States:
    aio_assign_scope_type scope_type;
    aio_assign_variable_declaration_type declaration_type;
    //Watcher:
    point_watcher *watcher;
    //Variable:
    string_list *variable_data_list;
    //Value:
    string value;
} aio_assign_materials;

aio_spider *new_aio_assign_spider();

#endif //AIO_ASSIGN_SPIDER_H