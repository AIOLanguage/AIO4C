#ifndef AIO_BUNDLE_H
#define AIO_BUNDLE_H

#include <list>
#include <lib4aio_cpp_headers/utils/str_hook/str_hook/str_hook.h>

using namespace lib4aio;
using namespace std;

class aio_bundle
{

private:

public:
    str_hook *path;
    str_hook *function_name;
    list<class aio_value> *input_values;
    class aio_value_list *output_values;

    aio_bundle();

    ~aio_bundle();
};

#endif //AIO_BUNDLE_H