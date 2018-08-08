#include <malloc.h>
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spider/aio_spiders.h"

#define AIO_START_SPIDER_STATE 0;

aio_spider *new_aio_spider(

        /**
         * Function which creates spider states:
         */

        int *(*create_spider_states)(),

        /**
         * Function which finds instruction:
         */

        const_boolean (*is_found_instruction)(const_string string_web,
                                              int *spider_pointer_reference,
                                              int *spider_state_reference),

        /**
         * Function which builds instruction for holder:
         */

        void (*weave_instruction_for)(
                aio_instruction_holder *instruction_holder,
                const_string string_web,
                int *pointer),

        /**
         * Function which frees spider:
         */

        void *(free_spider)(aio_spider *spider)
) {
    aio_spider *spider = calloc(1, sizeof(aio_spider));
    spider->start_pointer = 0;
    spider->spider_protocol = AIO_START_SPIDER_STATE;
    spider->is_found_instruction = is_found_instruction;
    spider->weave_instruction_for = weave_instruction_for;
    return spider;
}

/**
 * Assign spider functions.
 */

const_boolean is_found_assign_instruction(const_string string_web,
                                          int *spider_pointer_reference,
                                          int *spider_states);

void weave_assign_instruction_for(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);


/**
 * Break spider functions.
 */

const_boolean is_found_break_instruction(const_string string_web,
                                         int *spider_pointer_reference,
                                         int *spider_state_reference);

void weave_break_instruction_for(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);

/**
 * If spider functions.
 */

const_boolean is_found_if_instruction(const_string string_web,
                                      int *spider_pointer_reference,
                                      int *spider_state_reference);

void weave_if_instruction_for(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);

/**
 * Loop spider functions.
 */

const_boolean is_found_loop_instruction(const_string string_web,
                                        int *spider_pointer_reference,
                                        int *spider_state_reference);

void weave_loop_instruction_for(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);

/**
 * Out spider functions.
 */

const_boolean is_found_out_instruction(const_string string_web,
                                       int *spider_pointer_reference,
                                       int *spider_state_reference);

void weave_out_instruction_for(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);

/**
 * Procedure spider functions.
 */

const_boolean is_found_procedure_instruction(const_string string_web,
                                             int *spider_pointer_reference,
                                             int *spider_state_reference);

void weave_procedure_instruction_for(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);

/**
 * Switch spider functions.
 */

const_boolean is_found_switch_instruction(const_string string_web,
                                          int *spider_pointer_reference,
                                          int *spider_state_reference);

void weave_switch_instruction_for(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);

aio_spider **breed_aio_spiders() {
    aio_spider **spiders = calloc(NUMBER_OF_AIO_SPIDERS, sizeof(aio_spider *));
    //Create spiders:
    aio_spider *assign_spider = new_aio_spider(is_found_assign_instruction, weave_assign_instruction_for);
    aio_spider *break_spider = new_aio_spider(is_found_break_instruction, weave_break_instruction_for);
    aio_spider *if_spider = new_aio_spider(is_found_if_instruction, weave_if_instruction_for);
    aio_spider *loop_spider = new_aio_spider(is_found_loop_instruction, weave_loop_instruction_for);
    aio_spider *out_spider = new_aio_spider(is_found_out_instruction, weave_out_instruction_for);
    aio_spider *procedure_spider = new_aio_spider(is_found_procedure_instruction, weave_procedure_instruction_for);
    aio_spider *switch_spider = new_aio_spider(is_found_switch_instruction, weave_switch_instruction_for);
    //Assign spiders:
    spiders[0] = assign_spider;
    spiders[1] = break_spider;
    spiders[2] = if_spider;
    spiders[3] = loop_spider;
    spiders[4] = out_spider;
    spiders[5] = procedure_spider;
    spiders[6] = switch_spider;
    return spiders;
}

void free_aio_spiders(aio_spider ***spiders_reference) {
    aio_spider **spiders = *spiders_reference;
    for (int i = 0; i < NUMBER_OF_AIO_SPIDERS; ++i) {
        free(spiders[i]);
    }
    free(spiders);
}