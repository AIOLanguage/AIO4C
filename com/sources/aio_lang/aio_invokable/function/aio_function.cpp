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
    this->visibility_type = AIO_VISIBILITY_UNDEFINED;
}

aio_function::~aio_function()
{
    delete this->name;
}

/**
 * Boilerplate.
 */

#define DEBUG

#define TAG "ASSERT FUNCTION"

bool aio_function::equals(const aio_function *other) const
{
    //Check name:
    if (!this->name->equals_string(other->name)) {
        return false;
    }
#ifdef DEBUG
    log_info(TAG, "NAME IS OK!");
#endif
    //Check arg count:
    const array_list<aio_field> *other_fields = other->fields;
    const unsigned other_field_size = other_fields->get_size();
    if (this->arg_count != other->arg_count || this->fields->get_size() != other_field_size) {
        return false;
    }
#ifdef DEBUG
    log_info(TAG, "ARG COUNT IS OK!");
#endif
    //Check fields:
    for (unsigned i = 0; i < this->fields->get_size(); ++i) {
        if (!this->fields->get(i)->equals(other_fields->get(i))) {
            return false;
        }
    }
#ifdef DEBUG
    log_info(TAG, "FIELDS ARE OK!");
#endif
    //Check output type:
    if (!this->output_type->equals_string(other->output_type)) {
        return false;
    }
#ifdef DEBUG
    log_info(TAG, "OUTPUT TYPE IS OK!");
#endif
    //Check visibility:
    if (this->visibility_type != other->visibility_type) {
        return false;
    }
#ifdef DEBUG
    log_info(TAG, "VISIBILITY IS OK!");
#endif
    //Check output amount:
    if (this->is_array_output != other->is_array_output) {
        return false;
    }
    //Check instructions:
    const array_list<aio_task> *other_instructions = other->instructions;;

    if (this->instructions->get_size() != other_instructions->get_size()) {
        return false;
    }
#ifdef DEBUG
    log_info(TAG, "ARRAY IS OK!");
    log_info_int(TAG, "MY:", this->instructions->get_size());
    log_info_int(TAG, "OTHER:", other_instructions->get_size());
#endif
    for (unsigned j = 0; j < this->instructions->get_size(); ++j) {
        printf("AAA: \n");
        if (!this->instructions->get(j)->equals(other_instructions->get(j))) {
            return false;
        }
    }
#ifdef DEBUG
    log_info(TAG, "TASKS ARE OK!");
#endif
    return true;
}