#ifndef AIO_SPIDER_H
#define AIO_SPIDER_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_instructions/aio_instructions.h"

#define NUMBER_OF_AIO_SPIDERS 7

typedef struct aio_spider {

    /**
     * Spider's pointer defines start scanning spider position.
     */

    int start_pointer;

    /**
     * Spider's states work instead enums as state fields.
     */

    int *spider_states;

    /**
     * Find instruction.
     * @param string_web - instruction string in function body.
     * @return can recognize instruction or not.
     */

    const_boolean (*is_found_instruction)(const_string string_web, int *spider_pointer_reference,
                                          int *spider_state_reference);

    /**
     * Take instruction holder & build instruction for it.
     * @param instruction_holder - make instruction for.
     * @param string_web - instruction string in function body.
     * @param pointer - pointer reference in instruction ripper's loop.
     * After building ripper will know new start position that it again
     * will begin build string in function body and give "string web" for spiders.
     */

    void (*weave_instruction_for)(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer);

} aio_spider;

aio_spider **breed_aio_spiders();

void free_aio_spiders(aio_spider ***spiders_reference);

#endif //AIO_SPIDER_H