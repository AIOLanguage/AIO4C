#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

#include <iostream>

namespace lib4aio {

#define INIT_CAPACITY 2

    template<class T>
    array_list<T>::array_list()
    {
        this->capacity = INIT_CAPACITY;
        this->size = 0;
        this->elements = (T **) calloc(INIT_CAPACITY, sizeof(T));
    }

    template<class T>
    void array_list<T>::grow()
    {
        if (this->size == this->capacity) {
            this->capacity *= INIT_CAPACITY;
            this->elements = (T **) (realloc(this->elements, this->capacity * sizeof(T)));
        }
    }

    template<class T>
    void array_list<T>::add(T *element)
    {
        this->grow();
        this->elements[this->size++] = element;
    }

    template<class T>
    unsigned array_list<T>::get_size() const
    {
        return this->size;
    }

    template<class T>
    array_list<T> *array_list<T>::filter(function<bool(const T *)> func) const
    {
        auto size = this->size;
        auto elements = this->elements;
        auto new_list = new array_list<T>();
        for (unsigned k = 0; k < size; ++k) {
            auto element = elements[k];
            if (func(element)) {
                new_list->add(element);
            }
        }
        return new_list;
    }

    template<class T>
    void array_list<T>::foreach(function<void(const T *)> func) const
    {
        auto size = this->size;
        auto elements = this->elements;
        for (unsigned i = 0; i < size; ++i) {
            func(elements[i]);
        }
    }

    template<class T>
    void array_list<T>::free_elements()
    {
        const unsigned size = this->size;
        T **elements = this->elements;
        for (unsigned i = 0; i < size; ++i) {
            delete elements[i];
        }
    }

    template<class T>
    array_list<T>::~array_list()
    {
        std::cout << "delete" << endl;
        delete this->elements;
    }


    template<typename T>
    bool array_list<T>::contains_by(function<bool(const T *)> func)
    {
        for (unsigned i = 0; i < this->size; ++i) {
            if (func(this->elements[i])) {
                return true;
            }
        }
        return false;
    }

    template<typename T>
    T *&array_list<T>::operator[](unsigned index)
    {
        std::cout << "[]" << endl;
        return this->elements[index];
    }

    template<typename T>
    const T *array_list<T>::get(unsigned index) const
    {
        return this->elements[index];
    }

    template<typename T>
    const T *array_list<T>::find_by(function<bool(const T *)> func) const
    {
        bool is_found = false;
        T *unique_element = nullptr;
        for (unsigned i = 0; i < this->size; ++i) {
            const T *element = this->elements[i];
            if (func(element)) {
                if (!is_found) {
                    is_found = true;
                    unique_element = element;
                } else {
                    unique_element = nullptr;
                }
            }
        }
        return unique_element;
    }

    template<typename T>
    const T *array_list<T>::last()
    {
        return this->elements[this->size - 1];
    }

    template<typename T>
    array_list<T> *array_list<T>::collect_by(function<bool(T *)> func)
    {
        array_list<T> *collected_list = new array_list<T>();
        for (unsigned i = 0; i < this->size; ++i) {
            T *element = this->elements[i];
            if (func) {
                collected_list->add(element);
            }
        }
        return collected_list;
    }
}