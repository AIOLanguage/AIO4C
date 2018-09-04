#include <headers/utils/string_list_cls/string_list_cls.h>
#include <headers/utils/log_utils/log_utils.h>

#define AIO_TAG "AIO"

static string_list_cls create_test_arguments()
{
    string_list_cls args;
    args.add(const_cast<char *>(""));
    args.add(const_cast<char *>("../aioPrograms/tests/complexTests/variables/Trivial.aio"));
    args.add(const_cast<char *>("countSqrHypotenuse"));
    args.add(const_cast<char *>("3"));
    args.add(const_cast<char *>("'4'"));
    return args;
}

static void make_test()
{
    //Prepare test:
    auto arg_list = create_test_arguments();
    auto size = arg_list.size;
    auto args = arg_list.strings;
    log_info_int(AIO_TAG, "SIZE:", size);
    for (int i = 0; i < size; ++i) {
        log_info_string(AIO_TAG, "VALUE:", args[i]);
    }
    //Make AIO:
    //make_aio(size, args);
    //----------------------------------------------------------------------------------------------------------------—
    //찌꺼기 수집기 (Garbage collector):
    //free_string_list(arg_list);
}

int main(int argc, char *argv[])
{
    make_test();
    return 0;
}