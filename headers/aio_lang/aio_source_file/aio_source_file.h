#ifndef AIO_SOURCE_FILE_H
#define AIO_SOURCE_FILE_H

typedef struct aio_source_file {
    struct str_hook path;
    struct str_hook_list *aio_type_set;
    struct str_hook_list *import_list;
    //Content:
    struct aio_function_definition_list *global_function_definition_list;
    struct aio_field_definition_list *global_field_definition_list;
    struct aio_class_list *class_list;
} aio_source_file;

#endif //AIO_SOURCE_FILE_H