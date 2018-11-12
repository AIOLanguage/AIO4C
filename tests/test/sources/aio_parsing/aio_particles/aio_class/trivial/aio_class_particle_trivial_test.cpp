//lang:
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_class *create_class_for_aio_class_trivial_test()
{
    aio_class *clazz = new aio_class();
    clazz->name = new str_hook("Cat");
    clazz->visibility = aio_visible::AIO_VISIBILITY_UNDEFINED;
    clazz->inherited_type = aio_inheritable<aio_class>::AIO_INHERITED_TYPE_CLOSE;
    return clazz;
}