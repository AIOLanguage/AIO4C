#ifndef AIO_CLASS_H
#define AIO_CLASS_H

/**
 * 연결.
 */

#include <aio_lang/aio_inheritable/aio_inheritable.h>
#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>

using namespace lib4aio;

class aio_class : aio_initializable, aio_inheritable<aio_class> {
public:

    aio_class(
            aio_visibility visibility_type,
            aio_space *parent_namespace,
            array_list<aio_class> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function> *function_definition_list,
            array_list<aio_field> *field_definition_list,
            array_list<aio_class> *annotation_list,
            array_list<aio_constructor> *constructor_definition_list,
            array_list<aio_class> *parent_classes,
            aio_inherited_type inherited_type
    );

    ~aio_class();
};

#endif //AIO_CLASS_H