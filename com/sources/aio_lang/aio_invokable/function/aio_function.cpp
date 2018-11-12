//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_inheritable/aio_inheritable.cpp>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
//runtime:
#include <aio_runtime/aio_task/aio_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_function::aio_function()
{
    this->name = nullptr;
}

aio_function::~aio_function()
{
    delete this->name;
}

/**
 * Boilerplate.
 */

bool aio_function::operator==(const aio_function &rhs) const
{
    return static_cast<const aio_invokable &>(*this)
           == static_cast<const aio_invokable &>(rhs)
           && static_cast<const aio_inheritable<aio_function> &>(*this)
              == static_cast<const aio_inheritable<aio_function> &>(rhs)
           && *this->name == *rhs.name;
}

bool aio_function::operator!=(const aio_function &rhs) const
{
    return !(rhs == *this);
}

bool aio_function::compare(const aio_function *o1, const aio_function *o2) const{
    return *o1 == *o2;
}

bool aio_function::compare_functions(const aio_function *o1, const aio_function *o2) {
    return *o1 == *o2;
}
