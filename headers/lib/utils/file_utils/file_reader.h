#ifndef FILE_READER_H
#define FILE_READER_H

#include "../../collections/lists/string_list.h"
#include "../string_utils/string_utils.h"

#define CHUNK 1024

const_string read_file_and_join_to_string_without_comments(const_string path);

#endif //FILE_READER_H