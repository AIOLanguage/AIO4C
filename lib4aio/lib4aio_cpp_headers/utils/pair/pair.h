#ifndef LIB4AIO_CPP_PAIR_H
#define LIB4AIO_CPP_PAIR_H

namespace lib4aio {

    template<typename K, typename V>
    struct pair {

        K *first;

        V *second;

        pair(K *first, V *second);

        ~pair();
    };
}

#endif //LIB4AIO_CPP_PAIR_H