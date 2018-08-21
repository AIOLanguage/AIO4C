#ifndef BOOLEAN_UTILS_H
#define BOOLEAN_UTILS_H

#include "../string_utils/string_utils.h"

#define TRUE 1
#define FALSE 0
#define TRUE_STRING "true"
#define FALSE_STRING "false"

_Bool matches_boolean(const char *string);

_Bool string_to_boolean(const char *string);

/**
 * Typedef utils.
 */

typedef _Bool boolean;

typedef const _Bool const_boolean;

#endif //BOOLEAN_UTILS_H