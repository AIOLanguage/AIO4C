#include <aio_lang/aio_invokable/aio_constructor/aio_constructor.h>
#include <aio_lang/aio_inheritable/aio_inheritable.cpp>

const aio_inherited_type CONSTRUCTOR_INHERITED_TYPE = AIO_OPEN;

aio_constructor::aio_constructor()
{
    this->get_inherited_type() = CONSTRUCTOR_INHERITED_TYPE
}