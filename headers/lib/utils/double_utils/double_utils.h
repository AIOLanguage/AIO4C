#ifndef DOUBLE_UTILS_H
#define DOUBLE_UTILS_H

#include "../string_utils/string_utils.h"
#include "../boolean_utils/boolean_utils.h"

typedef double *double_array;

typedef const double *const_double_array;

double string_to_double(const_string src);

boolean matches_double(const_string word);

#endif //DOUBLE_UTILS_H