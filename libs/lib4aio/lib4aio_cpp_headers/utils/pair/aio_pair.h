#ifndef LIB4AIO_CPP_PAIR_H
#define LIB4AIO_CPP_PAIR_H

namespace lib4aio {

    template<typename K, typename V>
    struct aio_pair {

        K *first;

        V *second;

        aio_pair(K *first, V *second);

        ~aio_pair();
    };
}

#endif //LIB4AIO_CPP_PAIR_H