#ifndef AIO_SPIDER_H
#define AIO_SPIDER_H

#include "../../../../../lib/utils/string_utils/string_utils.h"
#include "../../../../../lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../lib/point_watcher/point_watcher.h"
#include "aio_assign_spider/aio_assign_spider.h"
#include "aio_switch_spider/aio_switch_spider.h"
#include "aio_procedure_spider/aio_procedure_spider.h"
#include "aio_loop_spider/aio_loop_spider.h"
#include "aio_out_spider/aio_out_spider.h"
#include "aio_break_spider/aio_break_spider.h"
#include "aio_if_spider/aio_if_spider.h"

typedef enum aio_spider_message {
    AIO_SPIDER_NOT_FOUND_MATERIALS, AIO_SPIDER_FOUND_MATERIALS, AIO_SPIDER_IS_READY_FOR_WEAVING
} aio_spider_message;

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
     * @param source_code - instruction string in function body;
     * @param spider - this.
     * @return can recognize instruction or not.
     */

    const aio_spider_message (*is_found_instruction)(const_string source_code, const int current_position,
                                                     struct aio_spider *spider);

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

    union {
        struct aio_assign_materials *assign_materials;
        aio_break_materials *break_materials;
        aio_if_materials *if_materials;
        aio_loop_materials *loop_materials;
        aio_out_materials *out_materials;
        aio_procedure_materials *procedure_materials;
        aio_switch_materials *switch_materials;
    } get;

    aio_spider_message message;

} aio_spider;

#endif //AIO_SPIDER_H