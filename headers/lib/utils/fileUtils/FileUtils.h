#ifndef AIO_PATH_UTILS_H
#define AIO_PATH_UTILS_H

#include "../../../lang/object/AIOObject.h"

void merge_new_folder_path(char *folderPath, char *nextObjectName, char **absoluteNextObjectPath);


string_pair *extract_name_and_folder_path_from_path(char *path);

#endif //AIO_PATH_UTILS_H