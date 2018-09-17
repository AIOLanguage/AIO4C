#ifndef AIO_BLINK_H
#define AIO_BLINK_H

class aio_invokable_track;

class aio_invokable_instruction {

    virtual void perform(aio_invokable_track* track);
};

#endif //AIO_BLINK_H