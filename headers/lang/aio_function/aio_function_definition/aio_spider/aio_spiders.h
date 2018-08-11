#ifndef AIO_SPIDER_H
#define AIO_SPIDER_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_instructions/aio_instructions.h"
#include "../../../../lib/point_watcher/point_watcher.h"

typedef enum aio_spider_message {
    AIO_SPIDER_NOT_FOUND_MATERIALS, AIO_SPIDER_FOUND_MATERIALS, AIO_SPIDER_IS_READY_FOR_WEAVING
} aio_spider_message;

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
    AIO_IF_MODIFIER_SCOPE, AIO_IF_CONDITION_SCOPE, AIO_IF_TRUE_BODY_SCOPE, AIO_IF_FALSE_BODY_SCOPE, AIO_IF_WEAVING_SCOPE
} aio_if_scope_type;

typedef enum aio_if_branch_type {
    AIO_UNDEFINED_BRANCHES, AIO_HAS_TRUE_BRANCH, AIO_HAS_TRUE_AND_FALSE_BRANCHES
} aio_if_branch_type;

typedef struct aio_if_materials {
    //States:
    aio_if_scope_type scope_type;
    aio_if_branch_type branch_type;
    //Watchers:
    point_watcher *main_watcher;
    point_watcher *header_watcher;
    point_watcher *true_watcher;
    point_watcher *false_watcher;
    //Condition:
    string condition;
} aio_if_materials;

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

    string name;

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
     * @param source_code - string.
     * @param next_ripper_point_reference - pointer reference in instruction ripper's loop.
     * @param spider - this.
     * After building ripper will know new start position that it again
     * will begin build string in function body and give "string web" for spiders.
     */

    void (*weave_instruction_for)(aio_instruction_holder *instruction_holder, const_string source_code,
                                  int *next_ripper_point_reference, struct aio_spider *spider);

    /**
     * Take other spider & build materials for it.
     * Spider can be and instruction builder for holder and material builder for other spider.
     * @param dst_spider destination spider.
     * @param src_spider source spider.
     * @param source_code - string.
     * @param next_spider_point_reference - pointer reference in spider's loop.
     * @param task_type - what is materials need to weave.
     */

    void (*weave_materials_for)(struct aio_spider *dst_spider, struct aio_spider *src_spider, const_string source_code,
                                int *next_spider_point_reference, aio_task_type task_type);

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

/**
 * Declare spider constructors.
 */

aio_spider *new_aio_assign_spider();

aio_spider *new_aio_break_spider();

aio_spider *new_aio_if_spider();

aio_spider *new_aio_loop_spider();

aio_spider *new_aio_out_spider();

aio_spider *new_aio_procedure_spider();

aio_spider *new_aio_switch_spider();

/**
 * Swarm.
 */

typedef enum aio_spider_swarm_mode {
    AIO_ONE_SPIDER_WORKS, AIO_ALL_SPIDERS_WORK
} aio_spider_swarm_mode;

typedef struct aio_spider_swarm {
    int number_of_spiders;
    aio_spider **spiders;
    aio_spider *active_spider;
    aio_spider_swarm_mode mode;
} aio_spider_swarm;

void reset_aio_spiders(aio_spider_swarm *swarm);

aio_spider_swarm *breed_aio_function_spider_swarm();

void free_aio_spider_swarm(aio_spider_swarm *spider_swarm);

#endif //AIO_SPIDER_H