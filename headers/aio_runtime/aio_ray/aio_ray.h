#ifndef AIO_RAY_H
#define AIO_RAY_H

class aio_scheme;

class aio_ray {

public:

    aio_ray(const aio_scheme *scheme);

    void perform();

    ~aio_ray();
};

#endif //AIO_RAY_H