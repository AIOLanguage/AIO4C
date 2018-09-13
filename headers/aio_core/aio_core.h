#ifndef AIO_CORE_H
#define AIO_CORE_H

#include <aio_lang/aio_file/aio_file.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>

#define NUMBER_OF_CORE_TYPES 5

using namespace lib4aio;

class aio_core
{
    array_list<str_hook> *types;

    array_list<aio_file> *file_list;
};

void inflate_aio_core(const int argc, char *argv[]);

/**
 * Global core.
 */

extern aio_core *core;

#endif //AIO_CORE_H