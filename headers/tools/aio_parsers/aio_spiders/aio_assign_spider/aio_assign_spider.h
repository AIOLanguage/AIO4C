#ifndef AIO_ASSIGN_SPIDER_H
#define AIO_ASSIGN_SPIDER_H

#include "../../../../lib/point_watcher/point_watcher.h"
#include "../../../../lib/collections/lists/string_list.h"
#include "../aio_spider.h"

/**
 * Assign spider materials.
 */

typedef enum aio_assign_scope_type {
    AIO_ASSIGN_DECLARATION_SCOPE, AIO_ASSIGN_EQUAL_SIGN_SCOPE, AIO_ASSIGN_VALUE_SCOPE, AIO_ASSIGN_WEAVING_SCOPE
} aio_assign_scope_type;

typedef enum aio_assign_variable_declaration_type {
    AIO_ASSIGN_UNDEFINED_DECLARATION, AIO_ASSIGN_WAS_MUTABLE_MODIFIER, AIO_ASSIGN_WILL_DEFINED, AIO_ASSIGN_REFERENCE,
    AIO_ASSIGN_IMMUTABLE, AIO_ASSIGN_MUTABLE
} aio_assign_variable_declaration_type;

typedef struct aio_assign_materials {
    //States:
    aio_assign_scope_type scope_type;
    aio_assign_variable_declaration_type declaration_type;
    //Watchers:
    point_watcher *main_watcher;
    point_watcher *value_watcher;
    //Variable:
    string_list *variable_data_list;
    //Value:
    string value;
} aio_assign_materials;

struct aio_spider *new_aio_assign_spider(point_watcher *ripper_watcher);

/**
 * Declare functions.
 */

const enum aio_spider_message is_found_assign_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                     struct aio_spider *spider);

void handle_assign_declaration_scope(const_string source_code, struct aio_spider *spider);

void refresh_assign_declaration_scope(struct aio_spider *spider, string chunk, aio_assign_variable_declaration_type type,
                                      enum aio_spider_message message);

void handle_assign_equal_sign_scope(const_string source_code, struct aio_spider *spider);

void handle_assign_value_scope(const_string source_code, struct aio_spider *spider);

void weave_assign_instruction_for(aio_instruction_holder *holder, const_string _,
                                  point_watcher *ripper_watcher, struct aio_spider *spider);

aio_variable_definition *create_local_variable_definition_by_assign_spider(
        const aio_assign_variable_declaration_type declaration_type,
        const_string_array variable_materials);


#endif //AIO_ASSIGN_SPIDER_H