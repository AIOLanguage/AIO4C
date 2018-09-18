#include <aio_core/aio_core.h>
#include <aio_core/aio_config.h>

int main(int argc, char *argv[])
{
    make_config();
    aio_core::inflate(argc, argv);
    return 0;
}