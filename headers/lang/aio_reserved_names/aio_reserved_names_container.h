#ifndef AIO_RESERVED_NAMES_CONTAINER_H
#define AIO_RESERVED_NAMES_CONTAINER_H

#include "../../lib/utils/string_utils/string_utils.h"
#include "../../lib/utils/boolean_utils/boolean_utils.h"
#include "../../lib/collections/sets/string_set.h"

#define AIO_MUTABLE "mu"

#define AIO_IN "in"

#define AIO_LOOP "loo"

#define AIO_RETURN "out"

#define AIO_WHEN "whe"

#define AIO_BREAK "brk"

boolean can_use_name(const_string name);

#endif //AIO_RESERVED_NAMES_CONTAINER_H