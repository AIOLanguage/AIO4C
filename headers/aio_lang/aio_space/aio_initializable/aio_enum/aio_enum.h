#ifndef AIO_ENUM_H
#define AIO_ENUM_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>

using namespace lib4aio;

class aio_enum : aio_initializable {

public:

    explicit aio_enum(
            aio_visibility visibility_type,
            aio_space *parent,
            array_list<aio_class> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function> *function_definition_list,
            array_list<aio_field> *field_definition_list,
            array_list<aio_class> *annotation_list,
            array_list<aio_constructor> *constructor_definition_list,
            array_list<aio_field> *elements
    );

    ~aio_enum();

    const array_list<aio_field> *get_values() const;

private:

    array_list<aio_field> *elements;

};

#endif //AIO_ENUM_H