#ifndef AIO_PATH_UTILS_H
#define AIO_PATH_UTILS_H

#include "../../../lang/object/aio_object.h"
#include "../../pair/string_pair.h"

char *merge_new_folder_path(char *folder_path, char *next_object_name);


string_pair *extract_name_and_folder_path_from_path(char *path);

#endif //AIO_PATH_UTILS_H