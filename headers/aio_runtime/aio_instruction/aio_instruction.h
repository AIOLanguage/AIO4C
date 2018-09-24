#ifndef AIO_INSTRUCTION_H
#define AIO_INSTRUCTION_H

class aio_ray;

class aio_instruction {

    virtual void perform(aio_ray* ray) = 0;
};

#endif //AIO_INSTRUCTION_H