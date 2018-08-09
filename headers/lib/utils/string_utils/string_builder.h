#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include "string_utils.h"

typedef struct string_builder {
    string string_value;
    size_t capacity;
    size_t length;
} string_builder;

string_builder *new_string_builder();

void append_char_to(string_builder *builder, const char c);

void append_string(string_builder *builder, const_string string);

string pop_string_from_builder(string_builder *builder);

void reset_string_builder(string_builder *builder);

void free_string_builder(string_builder *builder);

#endif //STRING_BUILDER_H