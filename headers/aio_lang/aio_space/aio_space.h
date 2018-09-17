#ifndef AIO_SPACE_H
#define AIO_SPACE_H

/**
 * 연결.
 */

#include <aio_lang/aio_visibility/aio_visibility.h>
#include <aio_lang/aio_annotatable/aio_annotatable.h>

class aio_enum;

class aio_scope;

class aio_function;

class aio_field;

class aio_space : public aio_annotatable {

public:

    explicit aio_space(
            aio_visibility visibility_type,
            aio_space *parent_namespace,
            array_list<aio_class> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function> *function_definition_list,
            array_list<aio_field> *field_definition_list,
            array_list<aio_class> *annotations
    );

    virtual ~aio_space();

    const aio_visibility get_visibility_type() const;

    const aio_space *get_parent_namespace() const;

    const array_list<aio_class> *get_class_definition_list() const;

    const array_list<aio_enum> *get_enum_definition_list() const;

    const array_list<aio_scope> *get_scope_definition_list() const;

    const array_list<aio_function> *get_function_definition_list() const;

    const array_list<aio_field> *get_field_definition_list() const;

private:

    aio_visibility visibility_type;

    aio_space *parent_namespace;

    array_list<aio_class> *class_definition_list;

    array_list<aio_enum> *enum_definition_list;

    array_list<aio_scope> *scope_definition_list;

    array_list<aio_function> *function_definition_list;

    array_list<aio_field> *field_definition_list;

};

#endif //AIO_SPACE_H