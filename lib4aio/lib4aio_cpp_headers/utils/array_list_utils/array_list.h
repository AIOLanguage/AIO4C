#ifndef LIB4AIO_CPP_ARRAY_LIST_H
#define LIB4AIO_CPP_ARRAY_LIST_H

namespace lib4aio {

    template<class T>
    class array_list {

    public:

        array_list();

        ~array_list();

        unsigned get_size() const;

        T *get(const int position) const;

        void add(T *element);

        array_list<T> *filter(bool (*filter_condition)(const T *element)) const;

        void foreach(void (*action)(T *element)) const;

        void free_elements();

    protected:

        unsigned capacity;

        unsigned size;

        T **elements;

        void update_memory();

    };

}

#endif //LIB4AIO_CPP_ARRAY_LIST_H