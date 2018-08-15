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
    point_watcher *value_watcher;
    point_watcher *condition_watcher;
    //Data:
    string_list *pointer_data_list;
    string init_value;
    string loop_condition;
    string step_value;
} aio_default_loop_header_materials;

typedef struct aio_default_loop_header_spider {

} aio_default_loop_header_spider;

struct aio_spider *new_aio_default_loop_header_spider(point_watcher *parent_watcher);

const enum aio_spider_message is_found_default_loop_header_instruction(const_string source_code,
                                                                       point_watcher *parent_watcher,
                                                                       struct aio_spider *spider);

/**
 *  Declare functions.
 */

void refresh_default_loop_header_materials(aio_default_loop_header_materials *materials, point_watcher *parent_watcher);

void free_default_loop_header_materials(aio_default_loop_header_materials *materials);

void refresh_default_loop_header_declaration_scope(struct aio_spider *spider, string chunk,
                                                   aio_default_loop_header_pointer_declaration_type type,
                                                   enum aio_spider_message message);

void handle_default_loop_header_declaration_scope(const_string string_web, struct aio_spider *spider);

void handle_default_loop_header_equal_sign_scope(const_string source_code, struct aio_spider *spider);

void handle_default_loop_header_value_scope(const_string source_code, struct aio_spider *spider);

void handle_default_loop_header_condition_scope(const_string source_code, point_watcher *parent_watcher,
                                                struct aio_spider *spider);

void handle_default_loop_header_step_scope(const_string source_code, point_watcher *parent_watcher,
                                           struct aio_spider *spider);

string get_default_loop_pointer_name_by_materials(const aio_default_loop_header_materials *materials);

const_boolean is_same_default_loop_pointer(const_string input_name, aio_default_loop_header_materials *materials);

void weave_default_loop_materials_for(struct aio_spider *dst_spider, struct aio_spider *src_spider, const_string _,
                                      point_watcher *header_watcher);

aio_variable_definition *create_pointer_variable_definition_by_default_loop_header_spider(
        const aio_default_loop_header_pointer_declaration_type declaration_type, const_string_array pointer_data);

#endif //AIO_DEFAULT_LOOP_HEADER_SPIDER_H