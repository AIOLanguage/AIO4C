#ifndef AIO_SPACE_H
#define AIO_SPACE_H

/**
 * 연결.
 */

#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_visibility/aio_visibility.h>
#include <aio_lang/aio_annotatable/aio_annotatable.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

class aio_enum;

class aio_scope;

class aio_space : aio_annotatable {

private:

    aio_visibility visibility_type;

    aio_space *parent_namespace;

    array_list<aio_class> *class_definition_list;

    array_list<aio_enum> *enum_definition_list;

    array_list<aio_scope> *scope_definition_list;

    array_list<aio_function> *function_definition_list;

    array_list<aio_field> *field_definition_list;

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

    ~aio_space();

    const aio_visibility get_visibility_type() const;

    const aio_space *get_parent() const;

    const array_list<aio_class> *get_class_definition_list() const;

    const array_list<aio_enum> *get_enum_definition_list() const;

    const array_list<aio_scope> *get_scope_definition_list() const;

    const array_list<aio_function> *get_function_definition_list() const;

    const array_list<aio_field> *get_field_definition_list() const;
};

#endif //AIO_SPACE_H