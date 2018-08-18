/**
 * Refresh each spider.
 * @param spider nest.
 */

void refresh_aio_spider_nest(aio_spider_nest *nest, point_watcher *parent_watcher) {
    for (int i = 0; i < nest->number_of_spiders; ++i) {
        aio_spider *spider = nest->spiders[i];
        spider->refresh(spider, parent_watcher);
    }
}

/**
 * Destroy nest & free all spiders.
 * @param spider nest.
 */

void free_aio_spider_nest(aio_spider_nest *nest) {
    aio_spider **spiders = nest->spiders;
    for (int i = 0; i < nest->number_of_spiders; ++i) {
        aio_spider *spider = spiders[i];
        //Spider frees himself:
        spider->free(spider);
    }
    free(spiders);
    free(nest);
#ifdef AIO_SPIDER_NEST_DEBUG
    log_info(AIO_SPIDER_NEST_TAG, "Spider nest is destroyed!");
#endif
}