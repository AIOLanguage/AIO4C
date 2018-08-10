#ifndef AIO_SPIDER_H
#define AIO_SPIDER_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_instructions/aio_instructions.h"
#include "../../../../lib/point_watcher/point_watcher.h"

#define AIO_NUMBER_OF_SPIDERS 7

typedef enum aio_spider_message {
    AIO_SPIDER_NOT_FOUND_MATERIALS, AIO_SPIDER_FOUND_MATERIALS, AIO_SPIDER_SEARCH_OTHER_MATERIALS,
    AIO_SPIDER_IS_READY_FOR_WEAVING, AIO_SPIDER_WAS_CRUSH
} aio_spider_message;

/**
 * Assign spider materials.
 */

typedef enum aio_assign_scope_type {
    AIO_DECLARATION_SCOPE, AIO_EQUAL_SIGN_IN_SCOPE, AIO_VALUE_SCOPE, AIO_IS_WEAVING_SCOPE
} aio_assign_scope_type;

typedef enum aio_assign_variable_declaration_type {
    AIO_UNDEFINED_DECLARATION, AIO_WAS_MUTABLE_MODIFIER, AIO_CONST_MODE, AIO_REFERENCE_MODE, AIO_IMMUTABLE_MODE,
    AIO_MUTABLE_BY_VALUE_MODE
} aio_assign_variable_declaration_type;

typedef struct aio_assign_materials {
    point_watcher *watcher;
    aio_assign_scope_type scope_type;
    aio_assign_variable_declaration_type declaration_type;
    string_list *variable_data_list;
    string value;
} aio_assign_materials;

/**
 * Break spider materials.
 */

typedef struct aio_break_materials {
    point_watcher *watcher;
} aio_break_materials;

/**
 * If spider materials:
 */

typedef enum aio_if_scope_type {
    AIO_IF_SCOPE, AIO_CONDITION_SCOPE, AIO_TRUE_BODY_SCOPE, AIO_FALSE_BODY_SCOPE, AIO_IS_READY_FOR_WEAVING
} aio_if_scope_type;

typedef enum aio_if_branches_type {
    AIO_UNDEFINED_BRANCHES, AIO_HAS_TRUE_BRANCH, AIO_HAS_TRUE_AND_FALSE_BRANCHES
} aio_if_branches_type;

typedef struct aio_if_materials {
    aio_if_scope_type scope_type;
    aio_if_branches_type branches_type;
    point_watcher *true_watcher;
    point_watcher *false_watcher;
    string condition;
} aio_if_materials;

typedef struct aio_loop_materials {

} aio_loop_materials;

typedef struct aio_out_materials {

} aio_out_materials;

typedef struct aio_procedure_materials {

} aio_procedure_materials;

typedef struct aio_switch_materials {

} aio_switch_materials;


/**
 * Spider.
 */

typedef struct aio_spider {

    /**
     * Reset spider's fields.
     * @param spider - this
     */

    void (*reset)(struct aio_spider *spider);

    /**
     * Find instruction.
     * @param string_web - instruction string in function body;
     * @param spider - this.
     * @return can recognize instruction or not.
     */

    const aio_spider_message (*is_found_instruction)(const_string string_web, struct aio_spider *spider);

    /**
     * Take instruction holder & build instruction for it.
     * @param instruction_holder - make instruction for.
     * @param source_code - string from .aio file.
     * @param next_ripper_point_reference - pointer reference in instruction ripper's loop.
     * @param spider - this.
     * After building ripper will know new start position that it again
     * will begin build string in function body and give "string web" for spiders.
     */

    void (*weave_instruction_for)(aio_instruction_holder *instruction_holder, const_string source_code,
                                  int *next_ripper_point_reference, struct aio_spider *spider);

    /**
     * Free spider.
     * @param spider - this.
     */

    void (*free)(struct aio_spider *spider);

    union get {
        aio_assign_materials *assign_materials;
        aio_break_materials *break_materials;
        aio_if_materials *if_materials;
        aio_loop_materials *loop_materials;
        aio_out_materials *out_materials;
        aio_procedure_materials *procedure_materials;
        aio_switch_materials *switch_materials;
    } get;

    aio_spider_message message;

} aio_spider;

enum aio_spider_swarm_mode {
    AIO_ONE_SPIDER_WORKS, AIO_ALL_SPIDERS_WORK
};

typedef struct aio_spider_swarm {
    aio_spider **spiders;
    aio_spider *active_spider;
    enum aio_spider_swarm_mode mode;
} aio_spider_swarm;

/**
 * Spiders.
 */

void reset_aio_spiders(aio_spider_swarm *swarm);

aio_spider_swarm *breed_aio_function_spider_swarm();

aio_spider_swarm *breed_aio_loop_spider_swarm();

void free_aio_spider_swarm(aio_spider_swarm *spider_swarm);

#endif //AIO_SPIDER_H