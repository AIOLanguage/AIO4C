#ifndef AIO_SOURCE_FILE_H
#define AIO_SOURCE_FILE_H

#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>
#include <aio_lang/aio_space/aio_space.h>

using namespace lib4aio;

class aio_file : aio_space {

private:

    str_hook *path;

    const char *source_file;

    str_hook_chain *source_context;

    array_list<str_hook> *import_list;

public:

};

#endif //AIO_SOURCE_FILE_H