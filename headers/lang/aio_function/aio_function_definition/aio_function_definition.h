#include <malloc.h>
#include "../../aio_annotation/aio_annotation.h"
#include "../../../tools/aio_function_tools/aio_function_instructions/aio_function_instruction_holder.h"

#ifndef AIO_FUNCTION_DEFINITION_H
#define AIO_FUNCTION_DEFINITION_H

/**
 * Function definition.
 */

typedef struct aio_function_definition {
    const_aio_annotation_list *annotation_list;
    const_str_hook_list *output_type_list;
    const_str_hook *name;
    const int number_of_args;
    const_aio_function_instruction_holder *root_holder;
} aio_function_definition;

typedef const aio_function_definition const_aio_function_definition;

const_aio_function_definition *new_aio_function_definition(const_aio_annotation_list *annotations,
                                                           const_str_hook_list *output_type_list,
                                                           const_str_hook *name,
                                                           const int number_of_args,
                                                           const_aio_function_instruction_holder *instruction_holder);

void free_aio_function_definition(const_aio_function_definition *method_definition);

/**
 * List.
 */

typedef struct aio_function_definition_list {
    size_t capacity;
    size_t size;
    const aio_function_definition **definitions;
} aio_function_definition_list;

typedef const aio_function_definition_list const_aio_function_definition_list;

aio_function_definition_list *new_aio_function_definition_list();

void add_aio_function_definition_in_list(aio_function_definition_list *list, const_aio_function_definition *definition);

const_aio_function_definition * get_aio_method_definition_in_list_by_name(const_aio_function_definition_list *list,
                                                                          const_str_hook *name);

void delete_aio_method_definition_map(aio_function_definition_list *method_definition_map);

#endif //AIO_FUNCTION_DEFINITION_H