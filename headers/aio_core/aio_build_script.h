#ifndef AIO_BUILD_SCRIPT_H
#define AIO_BUILD_SCRIPT_H

#include <aio_lang/aio_space/aio_file/aio_file.h>

#define AIO_BUILD_SCRIPT_MAIN_KEYWORD "main"

using namespace lib4aio;

class aio_build_script : public aio_file {

public:

    explicit aio_build_script(str_builder *content);

    ~aio_build_script();

    const aio_field * get_main_property() const;
};

#endif //AIO_BUILD_SCRIPT_H