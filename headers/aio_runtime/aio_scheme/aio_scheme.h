#ifndef AIO_SCHEME_H
#define AIO_SCHEME_H

namespace lib4aio {

    template<class T>
    class array_list;
}

using namespace lib4aio;

class aio_field;

class aio_instruction;

class aio_ray;

class aio_scheme {

public:

    explicit aio_scheme();

    ~aio_scheme();

    const aio_scheme *get_parent() const;

    const array_list<aio_field> *get_field_definitions() const;

    const array_list<aio_instruction> *get_instructions() const;

private:

    aio_scheme *parent;

    array_list<aio_field> *field_definitions;

    array_list<aio_instruction> *instructions;
};

#endif //AIO_SCHEME_H