#ifndef AIO_INITIALIZABLE_H
#define AIO_INITIALIZABLE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_visibility/aio_visibility.h>

class aio_constructor;

class aio_initializable : public aio_space {

public:

    explicit aio_initializable(
            aio_visibility visibility_type,
            aio_space *parent_namespace,
            array_list<aio_class> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function> *function_definition_list,
            array_list<aio_field> *field_definition_list,
            array_list<aio_class> *annotation_list,
            array_list<aio_constructor> *constructor_definition_list
    );

    virtual ~aio_initializable();

private:

    array_list<aio_constructor> *constructor_definition_list;
};


#endif //AIO_INITIALIZABLE_H