#ifndef DOUBLE_UTILS_H
#define DOUBLE_UTILS_H

#include "../string_utils/string_utils.h"
#include "../boolean_utils/boolean_utils.h"

double string_to_double(const char *string);

_Bool matches_double(const char *src);

/**
 * Typedef utils.
 */

typedef double *double_array;

typedef const double *const_double_array;

#endif //DOUBLE_UTILS_H