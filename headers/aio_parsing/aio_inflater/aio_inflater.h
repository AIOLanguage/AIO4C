#ifndef AIO_INFLATER_H
#define AIO_INFLATER_H

namespace lib4aio {

    class str_hook;

}

using namespace lib4aio;

class aio_core;

str_hook *inflate_aio_context(aio_core *core, const char *build_script_path);

#endif //AIO_INFLATER_H