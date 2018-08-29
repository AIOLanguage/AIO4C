
#include <mem.h>
#include "../../../../../headers/lib/utils/collections/sets/string_set.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"

string_set *new_string_set()
{
    string_set *set = new_object(sizeof(string_set));
    set->capacity = 2;
    set->size = 0;
    set->strings = new_object_array(2, sizeof(string));
    return set;
}

static void update_memory_in_string_set(string_set *set)
{
    if (set->size + 1 == set->capacity) {
        set->capacity = set->capacity * 2;
        set->strings = reallocate_object_array(
                set->strings,
                set->capacity, sizeof(string)
        );
    }
}

void add_string_in_set(string_set *set, string string)
{
    for (int i = 0; i < set->size; ++i) {
        if (strcmp(set->strings[i], string) == 0) {
            return;
        }
    }
    update_memory_in_string_set(set);
    set->strings[set->size] = string;
    set->size++;
}

boolean contains_string_in_set(string_set *set, const_string string)
{
    for (int i = 0; i < set->size; ++i) {
        if (strcmp(set->strings[i], string) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

void free_strings_in_set(struct string_set *set)
{

}

void free_string_set(string_set *set)
{

}