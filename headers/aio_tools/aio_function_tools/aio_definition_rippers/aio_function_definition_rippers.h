#ifndef AIO_FUNCTION_DEFINITION_SPIDER_H
#define AIO_FUNCTION_DEFINITION_SPIDER_H

struct aio_annotation_list *dig_aio_annotations(const char *source_code, int *pointer_reference);

struct str_hook_list *dig_output_types(const char *source_code, int *pointer_reference);

struct str_hook *dig_function_name(const char *source_code, int *pointer_reference);

struct aio_field_definition_list *dig_arguments(const char *source_code, int *pointer_reference);

void search_context_for(
        struct aio_function_instruction_holder *root_holder,
        const char *source_code,
        const int start_index,
        const int end_index
);

#endif //AIO_FUNCTION_DEFINITION_SPIDER_H