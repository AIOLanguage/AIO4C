namespace lib4aio
{

#ifndef LIB4AIO_LIST_H
#define LIB4AIO_LIST_H

    template<class T>
    class array_list
    {
    private:

        unsigned capacity;

        unsigned size;

        T **elements;

        void update_memory();

    public:

        array_list();

        ~array_list();

        unsigned get_size() const;

        T *get(const int position) const;

        void add(T *element);

        array_list<T> *filter(bool (*filter_condition)(const T *element)) const;

        void foreach(void (*action)(const T *element)) const;

        void free_elements();

    };

#endif //LIB4AIO_LIST_H
}
