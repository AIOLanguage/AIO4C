#ifndef AIO_PROGRAM_RUNTIME_H
#define AIO_PROGRAM_RUNTIME_H

#include <aio_runtime/aio_runtime.h>

class aio_build_runtime;

class aio_program_runtime : public aio_runtime {

public:

    explicit aio_program_runtime(aio_build_runtime *build_runtime);

    ~aio_program_runtime();

    aio_build_runtime *get_build_runtime();

private:

    aio_build_runtime *build_runtime;

};

#endif //AIO_PROGRAM_RUNTIME_H
