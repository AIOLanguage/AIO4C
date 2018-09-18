#include <iostream>
#include <cstring>
#include <sys/utsname.h>
#include <lib4aio_cpp_headers/utils/color_utils/color_utils.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>

using namespace lib4aio;

void make_config()
{

#ifdef _WIN32_
#include <windows.h>
    const unsigned UTF_8 = 65001;
    SetConsoleOutputCP(UTF_8);
    SetConsoleCP(UTF_8);
#elif __linux__

#elif  __APPLE__
#endif
    std::cout << BLUE << "\nAIO 이 시작됩다...\n\n" << RESET;
    utsname *os_data = static_cast<utsname *>(new_object(sizeof(utsname)));
    uname(os_data);
    std::cout << CYAN << os_data->sysname << " 운영 체제가 감지되었습니다!\n\n";
    std::cout << "정부:\n"
              << os_data->machine << "\n"
              << os_data->nodename << "\n"
              << os_data->release << "\n"
              << os_data->version << "\n\n"
              << RESET;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete os_data;
}