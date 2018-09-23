#include <lib4aio_cpp_headers/utils/pair/aio_pair.h>

namespace lib4aio {

    template<typename K, typename V>
    aio_pair<K, V>::aio_pair(K *first, V *second)
    {
        this->first = first;
        this->second = second;
    }

    template<typename K, typename V>
    aio_pair<K, V>::~aio_pair()
    {
        delete first;
        delete second;
    }
}