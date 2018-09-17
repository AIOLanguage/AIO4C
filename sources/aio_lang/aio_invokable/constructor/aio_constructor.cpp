#include <aio_lang/aio_invokable/aio_constructor/aio_constructor.h>

const aio_inherited_type CONSTRUCTOR_INHERITED_TYPE = AIO_OPEN;

aio_constructor::aio_constructor(
        const unsigned arg_count,
        aio_invokable_circuit *root_circuit,
        array_list<str_hook> *output_types,
        array_list<aio_class> *annotations,
        array_list<aio_constructor> *parents
) : aio_invokable(
        arg_count,
        root_circuit,
        output_types,
        annotations
), aio_inheritable(
        parents,
        CONSTRUCTOR_INHERITED_TYPE
)
{}

aio_constructor::~aio_constructor()
{}
