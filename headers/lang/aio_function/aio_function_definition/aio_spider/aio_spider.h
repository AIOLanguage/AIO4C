#ifndef AIO_AIO_SPIDER_H
#define AIO_AIO_SPIDER_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_instructions/aio_instructions.h"

#define NUMBER_OF_AIO_SPIDERS 7

typedef struct aio_spider {
    enum aio_instruction_type instruction_type;
    boolean (*weave_instruction)(const_string string_web);
} aio_spider;

aio_spider** breed_aio_spiders();

void free_aio_spiders(aio_spider** spiders);

#endif //AIO_AIO_SPIDER_H