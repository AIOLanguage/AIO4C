#ifndef AIO_BUILD_SCRIPT_H
#define AIO_BUILD_SCRIPT_H

typedef struct aio_build_script_space {
    char *project_path;
    char *main_path;
    char *result_path;
} aio_build_script_space;

aio_build_script_space *new_aio_build_script_materials();

void free_aio_build_script_materials(aio_build_script_space *materials);

#endif //AIO_BUILD_SCRIPT_H