#include <mem.h>
#include <malloc.h>
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/tools/aio_common_tools/aio_spider_nest/aio_function_instruction_spider_nest.h"
#include "../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_switch_spider/aio_switch_spider.h"
#include "../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_procedure_spider/aio_procedure_spider.h"
#include "../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_break_spider/aio_break_spider.h"
#include "../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_return_spider/aio_return_spider.h"
#include "../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_loop_spider/aio_loop_spider.h"
#include "../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_if_spider/aio_if_spider.h"
#include "../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_assign_spider/aio_assign_spider.h"
#include "../../../../headers/tools/aio_common_tools/aio_spider_nest/aio_spider.h"
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"

#define AIO_NUMBER_OF_SPIDERS 7

#define AIO_SPIDER_NEST_DEBUG

#ifdef AIO_SPIDER_NEST_DEBUG

#define AIO_SPIDER_NEST_TAG "AIO_SPIDER_NEST"

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Create spiders
 * @param body_length - specifies end index of function code block.
 * @return array of spiders.
 */

aio_spider_nest *breed_aio_function_instruction_spider_nest(point_watcher *ripper_watcher)
{
#ifdef AIO_SPIDER_NEST_DEBUG
    log_info_int(AIO_SPIDER_NEST_TAG, "Breed aio function spiders... Number of spiders:", AIO_NUMBER_OF_SPIDERS);
#endif
    //Create spiders:
    aio_spider **spiders = calloc(AIO_NUMBER_OF_SPIDERS, sizeof(struct aio_spider *));
    spiders[0] = new_aio_assign_spider(ripper_watcher);
    spiders[1] = new_aio_if_spider(ripper_watcher);
    spiders[2] = new_aio_loop_spider(ripper_watcher);
    spiders[3] = new_aio_return_spider(ripper_watcher);
    spiders[4] = new_aio_break_spider(ripper_watcher);
    spiders[5] = new_aio_procedure_spider(ripper_watcher);
    spiders[6] = new_aio_switch_spider(ripper_watcher);
    //Create spider nest:
    aio_spider_nest *nest = new_object(sizeof(aio_spider_nest));
    nest->number_of_spiders = AIO_NUMBER_OF_SPIDERS;
    nest->spiders = spiders;
    nest->active_spider = NULL;
    nest->mode = AIO_ALL_SPIDERS_WORK;
#ifdef AIO_SPIDER_NEST_DEBUG
    log_info(AIO_SPIDER_NEST_TAG, "Breeding is complete!");
#endif
    return nest;
}