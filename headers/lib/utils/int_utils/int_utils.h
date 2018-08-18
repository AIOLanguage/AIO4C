#ifndef AIO_INT_UTILS_H
#define AIO_INT_UTILS_H

#include "../string_utils/string_utils.h"
#include "../boolean_utils/boolean_utils.h"

typedef int *int_array;

typedef const int *const_int_array;

boolean matches_int(const_string word);

int string_to_int(const_string word);

#endif //AIO_INT_UTILS_H