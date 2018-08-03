#ifndef BOOLEAN_UTILS_H
#define BOOLEAN_UTILS_H

#include "../string_utils/string_utils.h"

#define TRUE 1
#define FALSE 0
#define TRUE_STRING "true"
#define FALSE_STRING "false"

typedef _Bool boolean;

typedef const _Bool const_boolean;

typedef const char *const_string;

const_boolean matches_boolean(const_string string);

const_boolean string_to_boolean(const_string string);

#endif //BOOLEAN_UTILS_H