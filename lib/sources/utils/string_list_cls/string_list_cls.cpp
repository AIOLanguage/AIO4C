#include <malloc.h>
#include <headers/utils/string_list_cls/string_list_cls.h>
#include <headers/utils/memory_utils/memory_utils.h>

#define INIT_CAPACITY 2

void string_list_cls::update_memory_in_string_list()
{
    if (this->size == this->capacity) {
        this->capacity *= INIT_CAPACITY;
        this->strings = static_cast<char **>(reallocate_object_array(
                this->strings,
                this->capacity,
                sizeof(char *)
        ));
    }
}

string_list_cls::string_list_cls()
{
    this->capacity = INIT_CAPACITY;
    this->size = 0;
    this->strings = static_cast<char **>(new_object_array(INIT_CAPACITY, sizeof(char *)));
}

string_list_cls::~string_list_cls()
{
    free(this->strings);
}

void string_list_cls::add(char *string)
{
    this->update_memory_in_string_list();
    this->strings[this->size++] = string;
}

char *string_list_cls::get(const int i)
{
    return this->strings[i];
}

void string_list_cls::free_strings()
{
    auto size = this->size;
    auto strings = this->strings;
    for (int i = 0; i < size; ++i) {
        auto old_string = strings[i];
        strings[i] = nullptr;
        free_object(old_string);
    }
}