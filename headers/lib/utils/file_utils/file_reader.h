#ifndef FILE_READER_H
#define FILE_READER_H

#include "../../collections/lists/string_list.h"
#include "../string_utils/string_utils.h"

#define CHUNK 1024

string_list *read_file_and_collect_to_string_list(const_string path);

#endif //FILE_READER_H