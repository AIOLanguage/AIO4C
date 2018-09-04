#ifndef AIO_BUNDLE_H
#define AIO_BUNDLE_H

#include <list>

class aio_bundle
{

private:

public:
    class str_hook *path;
    class str_hook *function_name;
    std::list<class aio_value> *input_values;
    class aio_value_list *output_values;

    aio_bundle();
};

//typedef struct aio_bundle {
//
//} aio_bundle;
//
//struct aio_bundle *new_aio_bundle(
//        struct str_hook *path,
//        struct str_hook *function_name,
//        struct aio_value_list *input_values
//);
//
//void free_aio_bundle(struct aio_bundle *bundle);

#endif //AIO_BUNDLE_H