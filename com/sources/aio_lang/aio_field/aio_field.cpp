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
    this->visibility_type = AIO_VISIBILITY_UNDEFINED;
}

aio_field::~aio_field()
{
    delete this->name;
    delete this->type;
}

void log_aio_field(const aio_field *field)
{
    log_info(AIO_FIELD_INFO, "------------------");
    log_info_str_hook(AIO_FIELD_INFO, "NAME:", field->name);
    log_info_str_hook(AIO_FIELD_INFO, "TYPE", field->type);
    log_info_boolean(AIO_FIELD_INFO, "IS ARRAY", field->is_array);
    log_info_boolean(AIO_FIELD_INFO, "IS CONST", field->is_const);
    log_info_boolean(AIO_FIELD_INFO, "IS_STATIC", field->is_static);
    switch (field->visibility_type) {
        case AIO_VISIBILITY_UNDEFINED:
            log_info(AIO_FIELD_INFO, "VISIBILITY: UNDEFINED");
            break;
        case AIO_VISIBILITY_LOCAL:
            log_info(AIO_FIELD_INFO, "VISIBILITY: LOCAL");
            break;
        case AIO_VISIBILITY_PRIVATE:
            log_info(AIO_FIELD_INFO, "VISIBILITY: PRIVATE");
            break;
        case AIO_VISIBILITY_PROTECTED:
            log_info(AIO_FIELD_INFO, "VISIBILITY: PROTECTED");
            break;
        case AIO_VISIBILITY_PUBLIC:
            log_info(AIO_FIELD_INFO, "VISIBILITY: PUBLIC");
    }
}