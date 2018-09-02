#include <aio_tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.h>
#include <fcntl.h>
#include <aio_lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <lib/utils/str_hook/str_hook.h>
#include <aio_lang/aio_annotation/aio_annotation.h>
#include <lib/utils/type_utils/type.utils.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lib/utils/error_utils/error_utils.h>

#define AIO_FUNCTION_DEFINITION_DEBUG

#define AIO_FUNCTION_DEFINITION_TAG "AIO_FUNCTION_DEFINITION"

#define INIT_CAPACITY 2

/**
 * Definition.
 */

aio_function_definition *new_aio_function_definition(
        aio_annotation_list *annotations,
        str_hook_list *output_type_list,
        str_hook *name,
        size_t number_of_args,
        aio_function_instruction_holder *holder
)
{
    aio_function_definition *function_definition = new_object(sizeof(aio_function_definition));
    function_definition->annotation_list = annotations;
    function_definition->output_type_list = output_type_list;
    function_definition->name = name;
    function_definition->number_of_args = number_of_args;
    function_definition->root_holder = holder;
    return function_definition;
}

void free_aio_function_definition(aio_function_definition *function_definition)
{

}

/**
 * List.
 */

aio_function_definition_list *new_aio_function_definition_list()
{
    aio_function_definition_list *list = new_object(sizeof(aio_function_definition_list));
    list->capacity = INIT_CAPACITY;
    list->size = 0;
    list->definitions = new_object_array(INIT_CAPACITY, sizeof(aio_function_definition *));
    return list;
}

static void update_memory_in_function_definition_list(aio_function_definition_list *list)
{
    if (list->size + 1 == list->capacity) {
        list->capacity *= INIT_CAPACITY;
        list->definitions = reallocate_object_array(list->definitions, list->capacity, sizeof(aio_function_definition));
    }
}

void add_aio_function_definition_in_list(
        aio_function_definition_list *list,
        aio_function_definition *definition
)
{
    val definition_name = definition->name;
    for (int i = 0; i < list->size; ++i) {
        val current_name = list->definitions[i]->name;
        val are_equal_strings = are_equal_hooked_str(current_name, definition_name);
        if (are_equal_strings) {
            throw_error_with_tag(AIO_FUNCTION_DEFINITION_TAG, "definition with the same name already exists!");
        }
    }
    //Check capacity:
    update_memory_in_function_definition_list(list);
    list->definitions[list->size] = definition;
    list->size++;
}

aio_function_definition *get_aio_function_definition_in_list_by_name(
        aio_function_definition_list *list,
        str_hook *name
)
{
    for (int i = 0; i < list->size; ++i) {
        val current_name = list->definitions[i]->name;
        val are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            return list->definitions[i];
        }
    }
    return NULL;
}

void free_aio_function_definition_list(aio_function_definition_list *function_definition_list)
{

}

//
//const_aio_function_definition *conjure_aio_function_definition(const_string source_code, int *start_index_ref)
//{
//    const_aio_annotation_list *annotations = dig_aio_annotations(source_code, start_index_ref);
//    const_str_hook_list *output_types = dig_output_types(source_code, start_index_ref);
//    const_str_hook *function_name = dig_function_name(source_code, start_index_ref);
//    aio_field_definition_list *arg_definition_list = dig_arguments(source_code, start_index_ref);
//    //Save number of args:
//    const size_t number_of_args = arg_definition_list->size;
//    //Pass list to root holder. It will add definitions in arg_definition_list:
//    const_aio_function_instruction_holder *holder = inflate_root_aio_instruction_holder(
//            source_code,
//            start_index_ref,
//            arg_definition_list
//    );
//    return new_aio_function_definition(annotations, output_types, function_name, number_of_args, holder);
//}