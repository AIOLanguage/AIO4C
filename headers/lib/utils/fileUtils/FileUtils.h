#ifndef AIO_PATH_UTILS_H
#define AIO_PATH_UTILS_H

#include "../../../lang/object/AIOObject.h"

void mergeNewFolderPath(char *folderPath, char *nextObjectName, char **absoluteNextObjectPath);


StringPair *extractNameAndFolderPathFromPath(char *path);

#endif //AIO_PATH_UTILS_H