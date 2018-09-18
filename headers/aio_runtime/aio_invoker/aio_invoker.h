#ifndef AIO_INVOKER_H
#define AIO_INVOKER_H

namespace lib4aio {

    struct struct_list;

    class str_hook;
}

class aio_core;

class aio_bundle;

using namespace lib4aio;

void invoke_main_function(aio_bundle *bundle);

struct_list *invoke_function(aio_bundle *bundle);

#endif //AIO_INVOKER_H