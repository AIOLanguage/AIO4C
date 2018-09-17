#ifndef AIO_BLINK_H
#define AIO_BLINK_H

#include <aio_runtime/aio_invokable_track/aio_invokable_track.h>

class aio_invokable_instruction {

    virtual void perform(aio_invokable_track* track);
};

#endif //AIO_BLINK_H