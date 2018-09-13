#ifndef AIO_CONTEXT_H
#define AIO_CONTEXT_H

#include <aio_utils/aio_bundle/aio_bundle.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_iterator/str_hook_iterator.h>

class aio_context
{
    /**
    * 컨텍스트 조건
    */

    enum
    {
        AIO_CONTEXT_IS_ABSENT, AIO_CONTEXT_IS_LOADING, AIO_CONTEXT_IS_READY
    } aio_context_state;


    /**
      * 조건
      */

    /**
     * Breaks.
     */

    struct struct_list *break_points;

    /**
     * Pressed source code.
     */

    str_builder *source_code_builder;


    /**
     * Context iterator.
     */

    str_hook_iterator *iterator;

    /**
     * Lexer nest.
     */

    aio_spider_nest *spider_nest;

    /**
     * Imported types.
     */

    str_hook_list *types;

    /**
     * Interpret Graph.
     */

    aio_context_control_graph *context_graph;
};

struct aio_value_list *inflate_aio_context(aio_bundle *bundle);

#endif //AIO_CONTEXT_H