#ifndef AIO_SPIDER_H
#define AIO_SPIDER_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_instructions/aio_instructions.h"

#define NUMBER_OF_AIO_SPIDERS 7

typedef struct aio_spider {
    //Function which finds instruction:
    const_boolean (*is_found_instruction)(const_string string_web);

    //Function which builds instruction for holder:
    void (*weave_instruction_for)(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);
} aio_spider;

aio_spider **breed_aio_spiders();

void reset_aio_spider(aio_spider *spider_entry);

void free_aio_spiders(aio_spider **spiders);

#endif //AIO_SPIDER_H