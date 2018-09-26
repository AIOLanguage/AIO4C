#ifndef AIO_FILE_H
#define AIO_FILE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>

namespace lib4aio {

    class str_hook;

    class str_builder;
}

using namespace lib4aio;

class aio_file : public aio_space {

protected:

    str_hook *relative_path;

    str_builder *content;

    array_list<str_hook> *import_list;

public:

    explicit aio_file();

    ~aio_file();

    const str_hook *get_relative_path() const;

    const str_builder * get_content() const;

    void set_content(str_builder *content);

    const array_list<str_hook> *get_imports() const;

    const array_list<aio_class> *get_annotation_definition_list() const;

    const aio_space *get_parent_namespace() const;
};

#endif //AIO_FILE_H