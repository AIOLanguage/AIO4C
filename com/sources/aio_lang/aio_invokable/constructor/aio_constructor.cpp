//lang:
#include <aio_lang/aio_inheritable/aio_inheritable.cpp>
#include <aio_lang/aio_invokable/aio_constructor/aio_constructor.h>

aio_constructor::aio_constructor()
{
    this->inherited_type = AIO_INHERITED_TYPE_CLOSE;
}

aio_constructor::~aio_constructor()
{}
