#include <aio_core/aio_build_script.h>
#include <aio_lang/aio_field/aio_field.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_BUILD_SCRIPT_ERROR_TAG "AIO_BUILD_SCRIPT_ERROR"

aio_build_script::aio_build_script(str_builder *content)
{
    this->content = content;
}

aio_build_script::~aio_build_script()
{}

const aio_field *aio_build_script::get_main_property() const
{
    return this->field_definition_list->find_by([](const aio_field *field) -> bool {
        return field->get_name()->equals_string(AIO_BUILD_SCRIPT_MAIN_KEYWORD);
    });
}