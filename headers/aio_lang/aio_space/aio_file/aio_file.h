#ifndef AIO_FILE_H
#define AIO_FILE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>

namespace lib4aio {

    class str_hook;

    class str_hook_list;

    template<typename K, typename V>
    struct aio_pair;
}

using namespace lib4aio;

class aio_file : aio_space {

private:

    aio_pair<str_hook, char> *path_entry;

    const char *source_file;

    array_list<str_hook> *import_list;

public:

    explicit aio_file(
            aio_pair<str_hook, char> *path_entry,
            const char *source_file,
            array_list<str_hook> *import_list,
            array_list<aio_class> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function> *function_definition_list,
            array_list<aio_field> *field_definition_list
    );

    ~aio_file();

    const aio_pair<str_hook, char> * get_path() const;

    const char *get_source_file() const;

    const array_list<str_hook> *get_import_list() const;

    const array_list<aio_class> *get_annotation_definition_list() const = delete;

    const aio_space *get_parent_namespace() const = delete;

};

#endif //AIO_FILE_H