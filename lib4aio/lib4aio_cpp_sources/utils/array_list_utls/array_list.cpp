#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>

namespace lib4aio
{

#define INIT_CAPACITY 2

    template<class T>
    array_list<T>::array_list()
    {
        this->capacity = INIT_CAPACITY;
        this->size = 0;
        this->elements = static_cast<T **>(new_object_array(INIT_CAPACITY, sizeof(T)));
    }

    template<class T>
    void array_list<T>::update_memory()
    {
        if (this->size == this->capacity) {
            this->capacity *= INIT_CAPACITY;
            this->elements = static_cast<T **>(reallocate_object_array(
                    this->elements,
                    this->capacity,
                    sizeof(T))
            );
        }
    }

    template<class T>
    void array_list<T>::add(T *element)
    {
        this->update_memory();
        this->elements[this->size++] = element;
    }

    template<class T>
    unsigned array_list<T>::get_size() const
    {
        return this->size;
    }

    template<class T>
    T *array_list<T>::get(const int position) const
    {
        return this->elements[position];
    }

    template<class T>
    array_list<T> *array_list<T>::filter(bool (*filter_condition)(const T *)) const
    {
        auto size = this->size;
        auto elements = this->elements;
        auto new_list = new array_list<T>();
        for (unsigned k = 0; k < size; ++k) {
            auto element = elements[k];
            if (filter_condition(element)) {
                new_list->add(element);
            }
        }
        return new_list;
    }

    template<class T>
    void array_list<T>::foreach(void (*action)(const T *)) const
    {
        auto size = this->size;
        auto elements = this->elements;
        for (unsigned i = 0; i < size; ++i) {
            action(elements[i]);
        }
    }

    template<class T>
    void array_list<T>::free_elements()
    {
        auto size = this->size;
        auto elements = this->elements;
        for (unsigned i = 0; i < size; ++i) {
            delete elements[i];
        }
    }

    template<class T>
    array_list<T>::~array_list()
    {
        delete this->elements;
    }
}