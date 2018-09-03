
#include <malloc.h>
#include <lib/utils/boolean_utils/boolean_utils.h>
#include <lib/utils/type_utils/type.utils.h>
#include "../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"

#define INIT_CAPACITY 2

/**
 * String hook.
 */

str_hook *new_str_hook(string source_ref)
{
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_string = source_ref;
    hook->start = 0;
    hook->end = 0;
    return hook;
}

void free_str_hook(str_hook *hook)
{
    if (hook) {
        free(hook);
    }
}

/**
 * List.
 */

str_hook_list *new_str_hook_list()
{
    str_hook_list *list = new_object(sizeof(str_hook_list));
    list->capacity = INIT_CAPACITY;
    list->size = 0;
    list->hooks = new_object_array(INIT_CAPACITY, sizeof(str_hook));
    return list;
}

static void update_memory_in_string_hook_list(str_hook_list *list)
{
    if (list->size == list->capacity) {
        list->capacity *= INIT_CAPACITY;
        list->hooks = reallocate_object_array(list->hooks, list->capacity, sizeof(str_hook));
    }
}

void add_str_hook_in_list(str_hook_list *list, str_hook *hook)
{
    update_memory_in_string_hook_list(list);
    list->hooks[list->size] = hook;
    list->size++;
}

void free_str_hooks_in_list(str_hook_list *list)
{
    str_hook **hooks = list->hooks;
    for (int i = 0; i < list->size; ++i) {
        free_str_hook(hooks[i]);
    }
}

void reset_str_hook_positions(str_hook *hook)
{
    hook->start = 0;
    hook->end = 0;
}

void free_str_hook_list(str_hook_list *list)
{
    str_hook **hooks = list->hooks;
    free(hooks);
    free((void *) list);
}

/**
 * String hook iterator.
 */


str_hook_iterator *new_str_hook_iterator()
{
    str_hook_iterator *iterator = new_object(sizeof(str_hook_iterator));
    iterator->position = 0;
    return iterator;
}

str_hook_iterator *new_str_hook_iterator_by_list(
        str_hook_list *str_hook_list,
        const unsigned current_hook_index
)
{
    val start_position = str_hook_list->hooks[current_hook_index]->start;
    //Create iterator:
    str_hook_iterator *iterator = new_object(sizeof(str_hook_iterator));
    iterator->str_hook_list = str_hook_list;
    iterator->current_hook_index = current_hook_index;
    iterator->position = start_position;
    return iterator;
}

boolean next_in_str_hook_iterator(str_hook_iterator *iterator)
{
    //Extract list:
    str_hook_list *list = iterator->str_hook_list;
    str_hook **hooks = list->hooks;
    //Get current hook:
    const unsigned current_hook_index = iterator->current_hook_index;
    str_hook *current_hook = hooks[current_hook_index];
    //Check next position:
    if (iterator->position < current_hook->end - 1) {
        iterator->position++;
        return TRUE;
    } else {
        if (current_hook_index < list->size - 1) {
            iterator->position = hooks[++iterator->current_hook_index]->start;
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

void free_str_hook_iterator(str_hook_iterator *iterator)
{
    if (iterator) {
        free(iterator);
    }
}