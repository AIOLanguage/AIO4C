//lang:
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//lib4aio;
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_class *create_class_for_aio_class_medium_test()
{
    aio_class *clazz = new aio_class();
    clazz->name = new str_hook("IRobot");
    clazz->parent_names->add(new str_hook("IEngineer"));
    clazz->parent_names->add(new str_hook("ITeacher"));
    clazz->inherited_type = aio_inheritable<aio_class>::AIO_INHERITED_TYPE_ABSTRACT;
    clazz->visibility = aio_visible::AIO_VISIBILITY_PROTECTED;
    return clazz;
}