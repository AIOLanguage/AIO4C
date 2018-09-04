#ifndef STRING_LIST_H
#define STRING_LIST_H

class string_list_cls
{

private:

    unsigned capacity;

    void update_memory_in_string_list();

public:

    unsigned size;

    char **strings;

    string_list_cls();

    ~string_list_cls();

    void add(char *string);

    char *get(const int i);

    void free_strings();

};

#endif //STRING_LIST_H