#include <malloc.h>
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spider/aio_spiders.h"

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
 * Spider materials constructor.
 */

aio_spider_materials new_aio_spider_materials(const size_t number_of_materials) {
    aio_spider_materials materials = calloc(number_of_materials, sizeof(string_list *));
    for (int i = 0; i < number_of_materials; ++i) {
        materials[i] = new_string_list();
    }
    return materials;
}

/**
 * Reset strings in spider materials.
 * @param materials array of string list
 * @param number_of_materials array size.
 */

void reset_aio_spider_materials(aio_spider_materials materials, const size_t number_of_materials) {
    for (int i = 0; i < number_of_materials; ++i) {
        string_list *material_list = materials[i];
        //Deep clear list and all string references:
        for (int j = 0; j < material_list->size; ++j) {
            free(material_list->strings[j]);
        }
        clear_string_list(material_list);
    }
}

/**
 * Reset each spider fields.
 * @param swarm array of spiders.
 */

void reset_aio_spiders(aio_spider_swarm *swarm) {
    for (int i = 0; i < AIO_NUMBER_OF_SPIDERS; ++i) {
        aio_spider *spider = swarm->spiders[i];
        //Reset himself:
        spider->reset(spider);
    }
}

/**
 * Create spiders.
 * @return array of spiders.
 */

aio_spider_swarm *breed_aio_spider_swarm() {
    //Create spiders:
    aio_spider **spiders = calloc(AIO_NUMBER_OF_SPIDERS, sizeof(aio_spider *));
    spiders[0] = new_aio_assign_spider();
    spiders[1] = new_aio_break_spider();
    spiders[2] = new_aio_if_spider();
    spiders[3] = new_aio_loop_spider();
    spiders[4] = new_aio_out_spider();
    spiders[5] = new_aio_procedure_spider();
    spiders[6] = new_aio_switch_spider();
    aio_spider_swarm *swarm = calloc(1, sizeof(aio_spider_swarm));
    swarm->spiders = spiders;
    swarm->active_spider = NULL;
    swarm->mode = AIO_ALL_SPIDERS_WORK;
    return swarm;
}

/**
 * Free all spiders.
 * @param spider_swarm - reference of spider array.
 */

void free_aio_spider_swarm(aio_spider_swarm *spider_swarm) {
    aio_spider **spiders = spider_swarm->spiders;
    for (int i = 0; i < AIO_NUMBER_OF_SPIDERS; ++i) {
        aio_spider *spider = spiders[i];
        //Spider frees himself:
        spider->free(spider);
    }
    free(spiders);
    free(spider_swarm);
}