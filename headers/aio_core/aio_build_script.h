#ifndef AIO_BUILD_SCRIPT_H
#define AIO_BUILD_SCRIPT_H

typedef struct aio_build_script_space {
    const char *main_path;
} aio_build_script_space;

aio_build_script_space *new_aio_build_script_materials();

void free_aio_build_script_materials(const aio_build_script_space *materials);

#endif //AIO_BUILD_SCRIPT_H