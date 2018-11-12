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

#define LOG_INFO "AIO_VISIBLE"

void aio_visible::log_aio_visibility() const
{
    switch (this->visibility) {
        case AIO_VISIBILITY_UNDEFINED:
            log_info(LOG_INFO, "VISIBILITY: UNDEFINED");
            break;
        case AIO_VISIBILITY_LOCAL:
            log_info(LOG_INFO, "VISIBILITY: LOCAL");
            break;
        case AIO_VISIBILITY_PRIVATE:
            log_info(LOG_INFO, "VISIBILITY: PRIVATE");
            break;
        case AIO_VISIBILITY_PROTECTED:
            log_info(LOG_INFO, "VISIBILITY: PROTECTED");
            break;
        case AIO_VISIBILITY_PUBLIC:
            log_info(LOG_INFO, "VISIBILITY: PUBLIC");
    }
}