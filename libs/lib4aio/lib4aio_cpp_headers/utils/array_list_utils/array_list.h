#ifndef LIB4AIO_CPP_ARRAY_LIST_H
#define LIB4AIO_CPP_ARRAY_LIST_H

#include <functional>

namespace lib4aio {

    using namespace std;

    template<typename T>
    class array_list {

    public:

        array_list();

        ~array_list();

        unsigned get_size() const;

        T *get(unsigned index) const;

        T* last();

        T *&operator[](unsigned index);

        void add(T *element);

        array_list<T> *filter(function<bool(const T *)> feunc) const;

        void foreach(function<void(T *)> func) const;

        void free_elements();

        bool contains_by(function<bool(const T *)> func);

        T *find_by(function<bool(T *)> func) const;

        array_list<T> *collect_by(function<bool(T *)> func);

        class array_list_iterator {

        public:

            explicit array_list_iterator(T **ptr) : p_element(ptr)
            {}

            array_list_iterator operator++()
            {
                array_list_iterator i = *this;
                p_element++;
                return i;
            }

            const array_list_iterator operator++(int junk)
            {
                p_element++;
                return *this;
            }

            T *&operator*()
            {
                return *p_element;
            }

            T **operator->()
            {
                return p_element;
            }

            bool operator==(const array_list_iterator &rhs)
            {
                return p_element == rhs.p_element;
            }

            bool operator!=(const array_list_iterator &rhs)
            {
                return p_element != rhs.p_element;
            }

        private:
            T **p_element;
        };

        array_list_iterator begin()
        {
            return array_list_iterator(this->elements);
        }

        array_list_iterator end()
        {
            return array_list_iterator(this->elements + this->size);
        }

        class const_array_list_iterator {
        public:

            explicit const_array_list_iterator(T **ptr) : p_element(ptr)
            {}

            const_array_list_iterator operator++()
            {
                const_array_list_iterator i = *this;
                p_element++;
                return i;
            }

            const const_array_list_iterator operator++(int junk)
            {
                p_element++;
                return *this;
            }

            const T *&operator*()
            {
                return *p_element;
            }

            const T **operator->()
            {
                return p_element;
            }

            bool operator==(const const_array_list_iterator &rhs)
            {
                return p_element == rhs.p_element;
            }

            bool operator!=(const const_array_list_iterator &rhs)
            {
                return p_element != rhs.p_element;
            }

        private:
            T **p_element;
        };

        const_array_list_iterator begin() const
        {
            return const_array_list_iterator(this->elements);
        }

        const_array_list_iterator end() const
        {
            return const_array_list_iterator(this->elements + this->size);
        }

    private:

        unsigned capacity;

        unsigned size;

        T **elements;

        void grow();
    };
}

#endif //LIB4AIO_CPP_ARRAY_LIST_H