//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
//parsing:
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>

#define AIO_FUNCTION_PARTICLE_ERROR_TAG "AIO_FUNCTION_PARTICLE_ERROR_TAG"

#define AIO_FUNCTION_PARTICLE_DEBUG

#ifdef AIO_FUNCTION_PARTICLE_DEBUG

#define AIO_FUNCTION_PARTICLE_INFO_TAG "AIO_FUNCTION_PARTICLE_INFO"

//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/aio_explorer/aio_explorer.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>

#endif

template<typename T>
aio_function_particle<T>::aio_function_particle(aio_runtime *runtime, array_list<aio_function> *function_list)
{
    this->monitor_mode = AIO_MONITOR_MODIFIER;
}

template<typename T>
aio_function_particle<T>::~aio_function_particle()
{}

template<typename T>
const aio_particle_signal aio_function_particle<T>::handle_symbol(const unsigned position)
{
    if (this->iterator < position) {
        this->iterator = position;
        const char symbol = this->string[position];
        switch (this->monitor_mode) {
            case AIO_MONITOR_MODIFIER:
                this->monitor_function_modifier(symbol, position);
                break;
            case AIO_MONITOR_NAME:
                this->monitor_function_name(symbol, position);
                break;
            case AIO_MONITOR_ARGS:
                this->monitor_function_args(symbol, position);
                break;
            case AIO_MONITOR_OUTPUT_TYPE:
                this->monitor_function_output_type(symbol, position);
                break;
            case AIO_MONITOR_BODY:
                this->monitor_function_body(symbol, position);
                break;
        }
    }
    return this->signal;
}

template<typename T>
void aio_function_particle<T>::monitor_function_modifier(const char symbol, const unsigned position)
{

    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
    }
    const bool is_token_scan_finished = is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        if (is_aio_function_modifier(this->token_holder)) {
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
            log_info_str_hook(AIO_FUNCTION_PARTICLE_INFO_TAG, "Found modifier:", this->token_holder);
#endif
            //Create field:
            this->function = new aio_function();
            //Prepare to the next state:
            this->monitor_mode = AIO_MONITOR_NAME;
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
        }
    }
}

template<typename T>
void aio_function_particle<T>::monitor_function_name(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_opening_parenthesis_cond = is_opening_parenthesis(symbol);
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
        log_info(AIO_FUNCTION_PARTICLE_INFO_TAG, "SCAN NAME...");
#endif
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
    }
    const bool is_token_scan_finished = (is_whitespace_cond || is_opening_parenthesis_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_name = is_not_aio_modifier(this->token_holder) && this->token_holder->is_word();
        if (is_valid_name) {
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
            log_info_str_hook(AIO_FUNCTION_PARTICLE_INFO_TAG, "Found name:", this->token_holder);
#endif
            //Create field:
            this->function->name = new str_hook(this->token_holder);
            this->monitor_mode = AIO_MONITOR_ARGS;
            if (is_opening_parenthesis_cond) {
                this->monitor_function_args(symbol, position);
            }
            //Prepare to the next state:
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
        }
    }
}

#define OPENING_PARENTHESIS '('

#define CLOSING_PARENTHESIS ')'

#define ARG_PART_COUNT 2

#define ARG_NAME_INDEX 0

#define ARG_TYPE_INDEX 1

#define ARG_STABILITY true

#define AIO_LIST_SEMANTIC "[]"

#define AIO_LIST_SEMANTIC_SIZE 2

#define AIO_ARG_GLOBALITY false

template<typename T>
void aio_function_particle<T>::monitor_function_args(const char symbol, const unsigned position)
{
    const str_hook *current_scope = new str_hook(this->string, this->left_border, this->right_border);
    //Find arg scope:
    const str_hook *arg_hook = explore_hook_scope(position, OPENING_PARENTHESIS, CLOSING_PARENTHESIS, current_scope);
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
    log_info_str_hook(AIO_FUNCTION_PARTICLE_INFO_TAG, "Arg hook:", arg_hook);
#endif
    //Get args:
    str_hook_list *arg_vs_type_list = arg_hook->split_by_comma();
    const unsigned args_count = arg_vs_type_list->get_size();
    //Create args:
    for (unsigned i = 0; i < args_count; i++) {
        const str_hook *arg_vs_type = arg_vs_type_list->get(i);
        const str_hook_list *arg_parts = arg_vs_type->split_by_whitespace();
        const unsigned parts_count = arg_parts->get_size();
        str_hook_list *clean_parts = new str_hook_list();
        for (unsigned j = 0; j < parts_count; j++) {
            str_hook *part = arg_parts->get(i);
            if (part->is_not_empty()) {
                clean_parts->add(part);
            } else {
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기:
                delete part;
                //------------------------------------------------------------------------------------------------------
            }
        }
        if (clean_parts->get_size() == ARG_PART_COUNT) {
            aio_field *arg = new aio_field();
            arg->visibility_type = AIO_VISIBILITY_LOCAL;
            arg->is_const = ARG_STABILITY;
            arg->is_static = AIO_ARG_GLOBALITY;
            arg->name = clean_parts->get(ARG_NAME_INDEX);
            str_hook *type = clean_parts->get(ARG_TYPE_INDEX);
            const bool is_list = type->ends_with(AIO_LIST_SEMANTIC);
            if (is_list) {
                type->end -= AIO_LIST_SEMANTIC_SIZE;
            }
            arg->is_list = is_list;
            arg->type = type;
            //Put arg:
            this->function->fields->add(arg);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기:
            delete clean_parts;
            delete arg_parts;
            //----------------------------------------------------------------------------------------------------------
        } else {
            throw_error_with_str_hook(AIO_FUNCTION_PARTICLE_ERROR_TAG, "Invalid arg chunk:", arg_vs_type);
        }
    }
    //Set iterator position:
    this->iterator = arg_hook->end;
    //Set arg count:
    this->function->arg_count = args_count;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    arg_vs_type_list->free_elements();
    delete arg_vs_type_list;
    delete arg_hook;
    delete current_scope;
    //------------------------------------------------------------------------------------------------------------------
    this->monitor_mode = AIO_MONITOR_OUTPUT_TYPE;
}

template<typename T>
void aio_function_particle<T>::monitor_function_output_type(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_opening_brace_cond = is_opening_brace(symbol);
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
        log_info(AIO_FUNCTION_PARTICLE_INFO_TAG, "SCAN TYPE...");
#endif
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
    }
    const bool is_token_scan_finished = (is_whitespace_cond || is_opening_brace_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_output_type = is_not_aio_modifier(this->token_holder) && this->token_holder->is_word();
        if (is_valid_output_type) {
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
            log_info_str_hook(AIO_FUNCTION_PARTICLE_INFO_TAG, "Found output type:", this->token_holder);
#endif
            //Create field:
            this->function->name = new str_hook(this->token_holder);
            this->monitor_mode = AIO_MONITOR_ARGS;
            if (is_opening_brace_cond) {
                this->monitor_function_body(symbol, position);
            }
            //Prepare to the next state:
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
        }
    }
}

#define OPENING_BRACE '{'

#define CLOSING_BRACE '}'

template<typename T>
void aio_function_particle<T>::monitor_function_body(const char symbol, const unsigned position)
{
    const str_hook *current_hook = new str_hook(this->string, this->left_border, this->right_border);
    const str_hook *body_hook = explore_hook_scope(position, OPENING_BRACE, CLOSING_BRACE, current_hook);
#ifdef AIO_FUNCTION_PARTICLE_DEBUG
    log_info_str_hook(AIO_FUNCTION_PARTICLE_INFO_TAG, "Body hook:", body_hook);
#endif
    aio_orbit<aio_function> function_orbit = new aio_function_orbit(this->function);
    this->function = function_orbit.make(body_hook);
    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete function_orbit;
    delete
}

template<typename T>
unsigned aio_function_particle<T>::illuminate(T *space)
{
    return 0;
}