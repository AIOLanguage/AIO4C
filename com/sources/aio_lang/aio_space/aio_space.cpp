//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_space/aio_space.h>
//#include <aio_lang/aio_schemable/aio_schemable.cpp>
#include <aio_lang/aio_space/aio_scope/aio_scope.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

using namespace lib4aio;

aio_space::aio_space()
{
    this->marknames = new array_list<aio_class>();
    this->functions = new array_list<aio_function>();
    this->pathnames = new array_list<aio_scope>();
    this->typenames = new array_list<aio_class>();
    this->fields = new array_list<aio_field>();
}

aio_space::~aio_space()
{
    //정의들을 청소하디
    this->typenames->free_elements();
    this->enumnames->free_elements();
    this->pathnames->free_elements();
    this->functions->free_elements();
    this->fields->free_elements();
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete this->typenames;
    delete this->enumnames;
    delete this->pathnames;
    delete this->functions;
    delete this->fields;
}