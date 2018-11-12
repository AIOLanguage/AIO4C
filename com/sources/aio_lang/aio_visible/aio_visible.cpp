//lang:
#include <aio_lang/aio_visible/aio_visible.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

using namespace lib4aio;

bool aio_visible::is_local_field()
{
    return this->visibility == AIO_VISIBILITY_LOCAL;
}

bool aio_visible::is_private_field()
{
    return this->visibility == AIO_VISIBILITY_PRIVATE;
}

bool aio_visible::is_protected_field()
{
    return this->visibility == AIO_VISIBILITY_PROTECTED;

}

bool aio_visible::is_public_field()
{
    return this->visibility == AIO_VISIBILITY_PUBLIC;
}

aio_visible::aio_visible()
{
    this->visibility = AIO_VISIBILITY_UNDEFINED;
}

aio_visible::~aio_visible()
{}

bool aio_visible::operator==(const aio_visible &rhs) const
{
    return this->visibility == rhs.visibility;
}

std::ostream &operator<<(std::ostream &os, const aio_visible &visible)
{
    switch (visible.visibility) {
        case aio_visible::AIO_VISIBILITY_UNDEFINED:
            printf("VISIBILITY: UNDEFINED\n");
            break;
        case aio_visible::AIO_VISIBILITY_LOCAL:
            printf("VISIBILITY: LOCAL\n");
            break;
        case aio_visible::AIO_VISIBILITY_PRIVATE:
            printf("VISIBILITY: PRIVATE\n");
            break;
        case aio_visible::AIO_VISIBILITY_PROTECTED:
            printf("VISIBILITY: PROTECTED\n");
            break;
        case aio_visible::AIO_VISIBILITY_PUBLIC:
            printf("VISIBILITY: PUBLIC\n");
    }
    return os;
}