#include "../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

#define AIO_EXPRESSION_ASSISTANT_TAG "AIO_EXPRESSION_ASSISTANT"

void make_expression_chunks_and_count_next_point(
        const_str_hook *expression_hook,
        str_hook_list *expression_list,
        int *next_point
)
{
    const_string expression_str = expression_hook->source_ref;
    //Skip first opening parenthesis:
    int parenthesis_up_downer = 1;
    const int start_position = expression_hook->start + 1;
    int last_pointer = start_position;
    for (int j = expression_hook->start + 1; j < expression_hook->end; ++j) {
        const char symbol = expression_str[j];
        if (is_opening_parenthesis(symbol)) {
            parenthesis_up_downer++;
        }
        if (is_closing_parenthesis(symbol)) {
            parenthesis_up_downer--;
            if (parenthesis_up_downer < 0) {
                throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_TAG, "Invalid parenthesis placement!");
            }
            if (parenthesis_up_downer == 0) {
                str_hook *inner_expression = new_str_hook(expression_str);
                inner_expression->start = last_pointer,
                        inner_expression->end = j;
                add_str_hook_in_list(expression_list, inner_expression);
                *next_point = j + 1;
                return;
            }
        }
        if (is_comma(symbol) && parenthesis_up_downer == 1) {
            str_hook *inner_expression = new_str_hook(expression_str);
            inner_expression->start = last_pointer,
                    inner_expression->end = j;
            add_str_hook_in_list(expression_list, inner_expression);
            last_pointer = j + 1;
        }
    }
    throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_TAG, "Incorrect parenthesis placement");
}