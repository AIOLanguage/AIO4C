//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_space/aio_scope/aio_scope.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
#include <aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

using namespace lib4aio;

aio_space::aio_space()
{
    this->typenames = new array_list<aio_class>(true);
    this->enumnames = new array_list<aio_enum>(true);
    this->functions = new array_list<aio_function>(true);
    this->pathnames = new array_list<aio_scope>(true);
}

aio_space::~aio_space()
{
    //찌꺼기 수집기:
    delete this->typenames;
    delete this->enumnames;
    delete this->pathnames;
    delete this->functions;
}