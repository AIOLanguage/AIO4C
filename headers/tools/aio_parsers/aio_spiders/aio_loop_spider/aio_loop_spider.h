#ifndef AIO_LOOP_SPIDER_H
#define AIO_LOOP_SPIDER_H

#include "../../../../lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../lib/point_watcher/point_watcher.h"
#include "../aio_spider.h"
#include "aio_inner_spiders/aio_default_loop_header_spider.h"
#include "aio_inner_spiders/aio_in_loop_header_spider.h"
#include "aio_inner_spiders/aio_tiny_loop_header_spider.h"
#include "../aio_spider_nest.h"

typedef enum aio_loop_scope_type {
    AIO_LOOP_MODIFIER_SCOPE, AIO_LOOP_HEADER_SCOPE, AIO_LOOP_BODY_SCOPE, AIO_LOOP_WEAVING_SCOPE
} aio_loop_scope_type;

typedef enum aio_loop_body_type {
    AIO_LOOP_UNDEFINED_BODY, AIO_LOOP_HAS_BODY
} aio_loop_body_type;

typedef enum aio_loop_material_type {
    AIO_LOOP_MATERIALS_UNDEFINED,
    AIO_LOOP_MATERIALS_MAIN,
    AIO_LOOP_MATERIALS_DEFAULT_HEADER,
    AIO_LOOP_MATERIALS_IN_HEADER,
    AIO_LOOP_MATERIALS_TINY_HEADER
} aio_loop_material_type;

typedef struct aio_main_loop_materials {

    //States:
    aio_loop_scope_type scope_type;

    //Watchers:
    point_watcher *main_watcher;
    point_watcher *header_watcher;
    point_watcher *body_watcher;

    aio_loop_material_type applied_header_material_type;

    union {
        struct aio_default_loop_header_materials *default_loop_header;
        struct aio_in_loop_header_materials *in_loop_header;
        struct aio_tiny_loop_header_materials *tiny_loop_header;
    } get_applied_materials_from;

} aio_main_loop_materials;

typedef struct aio_loop_materials {

    aio_loop_material_type type;

    union {
        struct aio_main_loop_materials *main;
        struct aio_default_loop_header_materials *default_loop_header;
        struct aio_in_loop_header_materials *in_loop_header;
        struct aio_tiny_loop_header_materials *tiny_loop_header;
    } from;

} aio_loop_materials;

struct aio_spider *new_aio_loop_spider(point_watcher *ripper_watcher);


/**
 *  Declare functions.
 */

const_boolean is_end_of_block_body(const_string function_body_string, point_watcher *watcher);

const enum aio_spider_message is_found_loop_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                        struct aio_spider *spider);

void handle_loop_modifier_scope(const_string source_code, struct aio_spider *spider);

void handle_loop_header_scope(const_string source_code, struct aio_spider *spider);

struct aio_spider_nest *breed_aio_loop_header_spider_nest(point_watcher *header_watcher);

void handle_loop_body_scope(const_string source_code, struct aio_spider *spider);

void dig_header_materials(const_string source_code, struct aio_spider *parent_spider);

\


void weave_loop_instruction_for(aio_instruction_holder *holder, const_string source_code,
                                point_watcher *ripper_watcher, struct aio_spider *spider);


#endif //AIO_LOOP_SPIDER_H