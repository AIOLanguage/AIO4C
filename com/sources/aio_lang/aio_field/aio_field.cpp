//lang:
#include <aio_lang/aio_field/aio_field.h>
//lib4aio:
#include <aio_lang/aio_types/aio_types.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_FIELD_INFO "AIO_FIELD"

aio_field::aio_field()
{
    this->name = nullptr;
    this->type = nullptr;
}

aio_field::~aio_field()
{
    delete this->name;
    delete this->type;
}

bool aio_field::operator==(const aio_field &rhs) const
{
    if (static_cast<const aio_visible &>(*this) == static_cast<const aio_visible &>(rhs)) {
        const aio_field *other = &rhs;
        if ((!this->name && other->name) || (this->name && !other->name)) {
            return false;
        }
        if (!this->name->equals_string(other->name)) {
            return false;
        }
        if ((!this->type && other->type) || (this->type && !other->type)) {
            return false;
        }
        if (!this->type->equals_string(other->type)) {
            return false;
        }
        return this->is_array == other->is_array
               && this->is_const == other->is_const
               && this->is_static == other->is_static;
    } else {
        return false;
    }
}

bool aio_field::operator!=(const aio_field &rhs) const
{
    return !(rhs == *this);
}

void aio_field::log() const
{
    log_info(AIO_FIELD_INFO, "------------------");
    log_info_str_hook(AIO_FIELD_INFO, "NAME:", this->name);
    log_info_str_hook(AIO_FIELD_INFO, "TYPE", this->type);
    log_info_boolean(AIO_FIELD_INFO, "IS ARRAY", this->is_array);
    log_info_boolean(AIO_FIELD_INFO, "IS CONST", this->is_const);
    log_info_boolean(AIO_FIELD_INFO, "IS_STATIC", this->is_static);
}

bool aio_field::compare_fields(const aio_field *o1, const aio_field *o2)
{
    return *o1 == *o2;
}

std::ostream &operator<<(std::ostream &os, const aio_field &field)
{
    os << static_cast<const aio_visible &>(field) << " name: " << field.name << " type: " << field.type << " is_array: "
       << field.is_array << " is_const: " << field.is_const << " is_static: " << field.is_static;
    return os;
}