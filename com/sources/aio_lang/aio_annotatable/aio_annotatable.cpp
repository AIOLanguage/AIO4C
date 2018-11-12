//lang:
#include <aio_lang/aio_annotatable/aio_annotatable.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_annotatable::aio_annotatable()
{
    this->annotations = new array_list<aio_class>(false);
    this->annotation_names = new array_list<str_hook>(true);
}

aio_annotatable::~aio_annotatable()
{
    delete this->annotations;
    delete this->annotation_names;
}

/**
 * Boilerplate.
 */

bool aio_annotatable::operator==(const aio_annotatable &rhs) const
{
    return this->annotations->equals(rhs.annotations, aio_class::compare_classes)
    && this->annotation_names->equals(rhs.annotation_names, str_hook::compare);
}

bool aio_annotatable::operator!=(const aio_annotatable &rhs) const
{
    return !(rhs == *this);
}