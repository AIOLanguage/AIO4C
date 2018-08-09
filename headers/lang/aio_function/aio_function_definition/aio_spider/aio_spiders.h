#ifndef AIO_SPIDER_H
#define AIO_SPIDER_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_instructions/aio_instructions.h"

#define AIO_NUMBER_OF_SPIDERS 7

typedef string_list **aio_spider_materials;


enum aio_spider_message {
    AIO_SPIDER_NOT_FOUND_MATERIALS, AIO_SPIDER_FOUND_MATERIALS, AIO_SPIDER_IS_READY_FOR_WEAVING, AIO_SPIDER_WAS_CRUSH
};

typedef struct aio_spider {

    /**
     * Spider's pointer defines start scanning spider position.
     */

    int start_pointer;

    /**
     * Spider's protocol has keys for work with "spider web" and weaving instruction.
     */

    int *spider_protocol;

    /**
     * Spider collects materials when it founds regex.
     * After successful searching spider weave instruction for holder by materials.
     */

    aio_spider_materials collected_materials;

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

    const enum aio_spider_message (*is_found_instruction)(const_string string_web, struct aio_spider *spider);

    /**
     * Take instruction holder & build instruction for it.
     * @param instruction_holder - make instruction for.
     * @param next_ripper_point_reference - pointer reference in instruction ripper's loop.
     * @param spider - this.
     * After building ripper will know new start position that it again
     * will begin build string in function body and give "string web" for spiders.
     */

    void (*weave_instruction_for)(aio_instruction_holder *instruction_holder, int *next_ripper_point_reference,
                                  struct aio_spider *spider);

    /**
     * Free spider.
     * @param spider - this.
     */

    void (*free)(struct aio_spider *spider);

} aio_spider;

enum aio_spider_swarm_mode {
    AIO_ONE_SPIDER_WORKS, AIO_ALL_SPIDERS_WORK
};

typedef struct aio_spider_swarm {
    aio_spider **spiders;
    aio_spider *active_spider;
    enum aio_spider_swarm_mode mode;
} aio_spider_swarm;

aio_spider_materials new_aio_spider_materials(const size_t number_of_materials);

void reset_aio_spider_materials(aio_spider_materials materials, const size_t number_of_materials);

void reset_assign_spider(aio_spider *spider);

void reset_aio_spiders(aio_spider_swarm *swarm);

aio_spider_swarm *breed_aio_spider_swarm();

void free_aio_spider_swarm(aio_spider_swarm *spider_swarm);

#endif //AIO_SPIDER_H