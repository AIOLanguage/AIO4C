#ifndef LIB4AIO_CPP_ARRAY_LIST_H
#define LIB4AIO_CPP_ARRAY_LIST_H

namespace lib4aio {

    template <typename z>
    struct array_list_iterator;

    template<typename T>
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

        array_list_iterator<T> begin();

        array_list_iterator<T> end();

    protected:

        unsigned capacity;

        unsigned size;

        T **elements;

        void update_memory();

    };

    template <typename T>
    class array_list_iterator {

    public:

        array_list_iterator(const unsigned position, const array_list<T> *parent);

        bool operator!=(array_list_iterator rhs);

        T &operator*();

        void operator++();

    private:

        unsigned position;

        array_list<T> *parent;
    };

}

#endif //LIB4AIO_CPP_ARRAY_LIST_H