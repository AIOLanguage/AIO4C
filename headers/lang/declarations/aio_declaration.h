#ifndef AIO_DECLARATION_H
#define AIO_DECLARATION_H

#include "../../lib/collections/lists/string_list.h"

typedef struct aio_declaration {
    char* methodName;
    string_list* argList;
} aio_declaration;

aio_declaration* new_aio_declaration(char *method_name, string_list *args);

#endif //AIO_DECLARATION_H