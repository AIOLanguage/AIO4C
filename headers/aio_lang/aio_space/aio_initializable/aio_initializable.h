#ifndef AIO_INITIALIZABLE_H
#define AIO_INITIALIZABLE_H

#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_invokable/aio_constructor/aio_constructor.h>
#include <aio_lang/aio_visibility/aio_visibility.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>

class aio_initializable : aio_space {

private:

    array_list<aio_constructor> *constructor_definition_list;

public:

    explicit aio_initializable(
            aio_visibility visibility_type,
            aio_space *parent_namespace,
            array_list<aio_class> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function> *function_definition_list,
            array_list<aio_field> *field_definition_list,
            array_list<aio_constructor> *constructor_definition_list
    );

    virtual ~aio_initializable();
};

#endif //AIO_INITIALIZABLE_H