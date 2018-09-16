#ifndef AIO_FIELD_H
#define AIO_FIELD_H

#include <aio_lang/aio_visibility/aio_visibility.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

class aio_field {

private:

    str_hook *name;

    str_hook *type;

    bool is_array;

    bool is_mutable;

    aio_visibility visibility_type;

public:

    aio_field(
            str_hook *name,
            str_hook *type,
            const bool is_array,
            const bool is_mutable,
            const aio_visibility visibility_type
    );

    ~aio_field();

    const str_hook *get_name() const;

    const str_hook *get_type() const;

    const bool is_array_type() const;

    const bool is_mutable_type() const;

    const aio_visibility get_visibility_type() const;
};

#endif //AIO_FIELD_H