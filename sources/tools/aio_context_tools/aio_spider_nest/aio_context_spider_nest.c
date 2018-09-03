#include <mem.h>
#include <malloc.h>
#include <aio_tools/aio_common_tools/aio_spider_nest/aio_spider_nest.h>
#include <lib/utils/str_hook/str_hook.h>
#include <aio_tools/aio_function_tools/aio_spider_nest/aio_assign_spider/aio_assign_spider.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <aio_tools/aio_context_tools/aio_spider_nest/aio_import_spider/aio_import_spider.h>
#include <aio_tools/aio_common_tools/aio_spider_nest/aio_common_spiders/aio_field_spider/aio_field_spider.h>
#include <aio_tools/aio_context_tools/aio_spider_nest/aio_class_spider/aio_class_spider.h>
#include <aio_tools/aio_common_tools/aio_spider_nest/aio_common_spiders/aio_function_spider/aio_function_spider.h>
#include <aio_tools/aio_common_tools/aio_spider_nest/aio_abstract_spider/aio_spider.h>

#define AIO_NUMBER_OF_SPIDERS 4

#define AIO_SPIDER_NEST_DEBUG

#ifdef AIO_SPIDER_NEST_DEBUG

#define AIO_SPIDER_NEST_TAG "AIO_SPIDER_NEST"

#endif

aio_spider_nest *breed_aio_context_spider_nest()
{
    //Create spiders:
    aio_spider **spiders = calloc(AIO_NUMBER_OF_SPIDERS, sizeof(aio_spider *));
    spiders[0] = new_aio_import_spider();
    spiders[1] = new_aio_field_spider();
    spiders[2] = new_aio_function_spider();
    spiders[3] = new_aio_class_spider();
    //Create spider nest:
    aio_spider_nest *nest = new_object(sizeof(aio_spider_nest));
    nest->number_of_spiders = AIO_NUMBER_OF_SPIDERS;
    nest->spiders = spiders;
    nest->active_spider = NULL;
    nest->mode = AIO_ALL_SPIDERS_WORK;
    return nest;
}