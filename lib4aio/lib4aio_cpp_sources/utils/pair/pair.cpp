#include <lib4aio_cpp_headers/utils/pair/pair.h>

namespace lib4aio {

    template<typename K, typename V>
    pair<K, V>::pair(K *first, V *second)
    {
        this->first = first;
        this->second = second;
    }

    template<typename K, typename V>
    pair<K, V>::~pair()
    {
        delete first;
        delete second;
    }
}