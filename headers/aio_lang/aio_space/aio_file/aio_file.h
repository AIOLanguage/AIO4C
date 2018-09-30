#ifndef AIO_FILE_H
#define AIO_FILE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>

namespace lib4aio {

    class str_hook;

    class str_builder;
}

using namespace lib4aio;

class aio_file : public aio_space {

public:

    explicit aio_file(str_builder *content, const str_hook *relative_file_path);

    ~aio_file();

    const str_hook *relative_path;

    str_builder *content;

    array_list<str_hook> *additions;
};

#endif //AIO_FILE_H