#ifndef AIO_SWITCH_SPIDER_H
#define AIO_SWITCH_SPIDER_H

#include "../../../aio_common_tools/aio_spider_nest/aio_spider.h"
#include "../../../../lib/utils/string_hook/str_hook.h"
#include "../../../../lib/utils/collections/lists/string_list.h"

typedef enum aio_switch_scope_type {
    AIO_SWITCH_MODIFIER_SCOPE, AIO_SWITCH_HEADER_SCOPE, AIO_SWITCH_BODY_SCOPE, AIO_SWITCH_WEAVING_SCOPE
} aio_switch_scope_type;

typedef struct aio_switch_materials {
    //States:
    aio_switch_scope_type scope_type;
    boolean has_else_branch;
    //Watchers:
    point_watcher *main_watcher;
    point_watcher *header_watcher;
    point_watcher *switch_body_watcher;
    point_watcher *else_watcher;
    //String hooks:
    str_hook_list *case_key_list;
    str_hook_list *case_body_list;
} aio_switch_materials;

struct aio_spider *new_aio_switch_spider(point_watcher *ripper_watcher);

const enum aio_spider_message is_found_switch_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                          struct aio_spider *spider);

void handle_switch_modifier_scope(const_string source_code, struct aio_spider *spider);

void handle_switch_header_scope(const_string source_code, struct aio_spider *spider);

void handle_switch_body_scope(const_string source_code, struct aio_spider *spider);

void build_switch_cases(const_string source_code, struct aio_spider *spider);

void handle_switch_case_value_scope(const_string source_code, struct aio_spider *spider);

void handle_switch_case_body_scope(const_string source_code, struct aio_spider *spider);

void weave_switch_instruction_for(void *parent, const_string source_code,
                                  point_watcher *ripper_watcher, struct aio_spider *spider);

string_list *extract_case_keys_from_hook(const_str_hook *case_keys_hook);

#endif //AIO_SWITCH_SPIDER_H