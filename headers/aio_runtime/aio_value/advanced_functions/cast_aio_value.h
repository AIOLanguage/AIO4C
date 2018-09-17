#ifndef CAST_AIO_VALUE_H
#define CAST_AIO_VALUE_H

struct aio_value *cast_to_int(const struct aio_value *value);

struct aio_value *cast_to_double(const struct aio_value *value);

struct aio_value *cast_to_string(const struct aio_value *value);

struct aio_value *cast_to_boolean(const struct aio_value *value);

struct aio_value *cast_to_void(const struct aio_value *value);

struct aio_value *cast_to_type(const struct aio_value *value, const struct str_hook *type);

#endif //CAST_AIO_VALUE_H
