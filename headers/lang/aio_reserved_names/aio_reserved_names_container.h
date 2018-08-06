#ifndef AIO_RESERVED_NAMES_CONTAINER_H
#define AIO_RESERVED_NAMES_CONTAINER_H

#include "../../lib/utils/string_utils/string_utils.h"
#include "../../lib/utils/boolean_utils/boolean_utils.h"
#include "../../lib/collections/sets/string_set.h"

#define AIO_MUTABLE_MODIFIER "mu"

#define AIO_IN_MODIFIER "in"

#define AIO_LOOP_MODIFIER "loo"

#define AIO_RETURN_MODIFIER "out"

#define AIO_WHEN_MODIFIER "whe"

#define AIO_BREAK_MODIFIER "brk"

const_boolean is_aio_mutable_modifier(const_string string);

boolean can_use_name(const_string name);

#endif //AIO_RESERVED_NAMES_CONTAINER_H