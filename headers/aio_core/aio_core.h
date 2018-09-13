#ifndef AIO_CORE_H
#define AIO_CORE_H

#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>

#define NUMBER_OF_CORE_TYPES 5

using namespace lib4aio;

class aio_core {
    str_hook_list *root_types;

};




//
//typedef struct aio_core {
//    //Main:
//    struct str_hook_list *root_types;
//    struct aio_context_list *context_list;
//    struct aio_source_file_list *source_file_list;
//} aio_core;
//
//struct aio_value_list *inflate_aio_core(struct aio_bundle *input_bundle);
//
///**
// * Global core.
// */
//
//extern struct aio_core *core;

#endif //AIO_CORE_H