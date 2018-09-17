#ifndef AIO_FILE_H
#define AIO_FILE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>

using namespace lib4aio;

class aio_file : aio_space {

private:

    str_hook *path;

    const char *source_file;

    str_hook_chain *source_context;

    array_list<str_hook> *import_list;

public:

    explicit aio_file(
            str_hook *path,
            const char *source_file,
            str_hook_chain *source_context,
            array_list<str_hook> *import_list,
            array_list<aio_class> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function> *function_definition_list,
            array_list<aio_field> *field_definition_list
    );

    ~aio_file();

    const str_hook *get_path() const;

    const char *get_source_file() const;

    const str_hook_chain *get_source_context() const;

    const array_list<str_hook> *get_import_list() const;

    const array_list<aio_class> *get_annotation_definition_list() const = delete;

    const aio_space *get_parent_namespace() const = delete;

};

#endif //AIO_FILE_H