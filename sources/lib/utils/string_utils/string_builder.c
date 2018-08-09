#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/string_utils/string_builder.h"

#define START_STRING_CAPACITY 2

string_builder *new_string_builder() {
    string_builder *builder = calloc(1, sizeof(string_builder));
    reset_string_builder(builder);
    return builder;
}

void reset_string_builder(string_builder *builder){
    builder->string_value = calloc(START_STRING_CAPACITY, sizeof(char));
    builder->capacity = START_STRING_CAPACITY;
    builder->length = 0;
}

void update_string_builder_memory(string_builder *builder, const size_t other_length) {
    const size_t new_length = builder->length + other_length + 1;
    if (new_length >= builder->capacity) {
        while (new_length >= builder->capacity) {
            builder->capacity *= 2;
        }
        //const_string new_str = calloc(builder->capacity, sizeof(char));
        builder->string_value = realloc(builder->string_value, builder->capacity);
    }
}

void append_char_to(string_builder *builder, const char c) {
    update_string_builder_memory(builder, 1);
    builder->string_value[builder->length++] = c;
}

void append_string(string_builder *builder, const_string string) {
    const size_t other_string_length = strlen(string);
    const int start_position = builder->length;
    const size_t new_length = start_position + other_string_length;
    int other_string_counter = 0;
    update_string_builder_memory(builder, other_string_length);
    for (int i = start_position; i < new_length; ++i) {
        builder->string_value[i] = string[other_string_counter++];
    }
    builder->string_value[new_length] = '\0';
    builder->length = new_length;
}

string pop_string_from_builder(string_builder *builder) {
    string new_str = new_string(builder->string_value);
    free(builder->string_value);
    reset_string_builder(builder);
    return new_str;
}

void free_string_builder(string_builder *builder) {
    free(builder->string_value);
    free(builder);
}