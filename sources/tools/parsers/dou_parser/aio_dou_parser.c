#include <stdio.h>
#include <process.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../headers/lang/types/aio_type.h"
#include "../../../../headers/lang/object/aio_object.h"
#include "../../../../headers/lang/methods/aio_method_container.h"
#include "../../../../headers/lang/methods/result/aio_result.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/tools/parsers/aio_parser.h"
#include "../../../../headers/lang/methods/default_method_container/aio_default_method_container.h"

//제목들:

aio_dou_result *make_plus_or_minus(aio_object *object, aio_method_definition *method_definition,
                                   aio_method_container *method_container, char *code_line);

aio_dou_result *make_multiplication_or_division(aio_object *object, aio_method_definition *method_definition,
                                                aio_method_container *method_container, char *code_line);

aio_dou_result *make_brackets(aio_object *object, aio_method_definition *method_definition,
                              aio_method_container *method_container, char *code_line);

aio_dou_result *make_method_or_variable(aio_object *object, aio_method_definition *method_definition,
                                        aio_method_container *method_container, char *code_line);

aio_dou_result *make_method(char *method_name, aio_dou_result *dou_result, aio_object *object);

aio_dou_result *make_number(char *code_line);

/**
 * parseDouLineExpression
 * plusOrMinus -> multiplicationOrDivision -> brackets -> method or variable or number:
 */

aio_str parse_dou_line_expression(aio_object *object, aio_method_definition *method_definition,
                                  aio_method_container *method_container, char *code_line) {
    const aio_dou_result *dou_result = make_plus_or_minus(object, method_definition, method_container, code_line);
    if (is_not_empty_string(dou_result->rest) == 0) {
        perror("cannot full parse code line!");
        exit(1);
    }
    aio_str str_result = dou_to_str(dou_result->acc);
    return str_result;
}

aio_dou_result *make_plus_or_minus(aio_object *object, aio_method_definition *method_definition,
                                   aio_method_container *method_container, char *code_line) {
    aio_dou_result *current = make_multiplication_or_division(object, method_definition, method_container, code_line);
    aio_dou acc = current->acc;
    while (is_not_empty_string(current->rest) == 0) {
        const char sign = current->rest[0];
        if (!(sign == '+' || sign == '-')) {
            break;
        }
        char *next = substring(current->rest, 1, strlen(current->rest) - 1);
        current = make_multiplication_or_division(object, method_definition, method_container, next);
        if (sign == '+') {
            acc += current->acc;
        } else {
            acc -= current->acc;
        }
    }
    aio_dou_result *dou_result = new_aio_dou_result(acc, current->rest);
    return dou_result;
}

aio_dou_result *make_multiplication_or_division(aio_object *object, aio_method_definition *method_definition,
                                                aio_method_container *method_container, char *code_line) {
    aio_dou_result *current = make_brackets(object, method_definition, method_container, code_line);
    aio_dou acc = current->acc;
    while (1) {
        if (is_empty_string(current->rest) == 0) {
            return current;
        }
        const char sign = current->rest[0];
        if (sign != '*' && sign != '/') {
            return current;
        }
        char *next = substring(current->rest, 1, strlen(current->rest) - 1);
        aio_dou_result *aio_bracket_result = make_brackets(object, method_definition, method_container, next);
        if (sign == '*') {
            acc *= aio_bracket_result->acc;
        } else {
            acc /= aio_bracket_result->acc;
        }
        aio_dou_result *dou_result = new_aio_dou_result(acc, aio_bracket_result->rest);
        current = dou_result;
    }
}

aio_dou_result *make_brackets(aio_object *object, aio_method_definition *method_definition,
                              aio_method_container *method_container, char *code_line) {
    const char zero_char = code_line[0];
    if (zero_char == '(') {
        char *in_brackets_code_line = substring(code_line, 1, strlen(code_line) - 1);
        aio_dou_result *in_brackets_aio_result = make_plus_or_minus(object, method_definition, method_container,
                                                                    in_brackets_code_line);
        if (is_not_empty_string(in_brackets_aio_result->rest) == 0 && in_brackets_aio_result->rest[0] == ')') {
            char *after_brackets_code_line = substring(in_brackets_aio_result->rest, 1,
                                                       strlen(in_brackets_aio_result->rest) - 1);
            in_brackets_aio_result->rest = after_brackets_code_line;
        } else {
            perror("cannot close bracket!");
            exit(1);
        }
        return in_brackets_aio_result;
    }
    return make_method_or_variable(object, method_definition, method_container, code_line);
}

aio_dou_result *make_method_or_variable(aio_object *object, aio_method_definition *method_definition,
                                        aio_method_container *method_container, char *code_line) {
    char *method_or_variable_name = "";
    int i = 0;
    // 함수 이름 또는 변수 이름 찾기,
    // 이름은 반드시 문지로 시작해야한다:
    int code_line_length = strlen(code_line);
    while (i < code_line_length && (isalpha(code_line[i]) || (isdigit(code_line[i]) && i != 0))) {
        concat_char_to_string(method_or_variable_name, code_line[i]);
        i++;
    }
    if (i == code_line_length) {
        i--;
    }
    if (is_not_empty_string(method_or_variable_name) == 0) { // 무언가가 발견도면
        const size_t method_or_variable_str_length = strlen(method_or_variable_name);
        if (i < code_line_length && code_line[i] == '(' || code_line[i] == '~') {
            if (code_line[i] == '(') {
                // 그것은 함수이다:
                char *in_brackets_line = substring(method_or_variable_name, method_or_variable_str_length,
                                                   code_line_length - method_or_variable_str_length);
                aio_dou_result *in_function_aio_result = make_brackets(object, method_definition, method_container,
                                                                       in_brackets_line);
                //하나의 arg:
                return make_method(method_or_variable_name, in_function_aio_result, object);
            } else {
                //arg 이없는:
                aio_dou_result *empty_dou_result = new_aio_dou_result(0.0, "");
                aio_dou_result *instead_method_result = make_method(method_or_variable_name, empty_dou_result, object);
                char *acc_str_result = dou_to_str(instead_method_result->acc);
                char *next_code_line = substring(code_line, method_or_variable_str_length + 1,
                                                 code_line_length - method_or_variable_str_length - 1);
                concat_string_to_string(acc_str_result, next_code_line);
                free(next_code_line);
                return make_plus_or_minus(object, method_definition, method_container, acc_str_result);
            }
        } else { //그것은 변수이다:
            char *variable_name = method_or_variable_name;
            aio_variable *variable = get_variable_from_method_container(variable_name, method_container);
            char *rest = substring(code_line, method_or_variable_str_length,
                                   code_line_length - method_or_variable_str_length);
            aio_dou acc = str_to_dou(variable->value);
            aio_dou_result *dou_result = new_aio_dou_result(acc, rest);
            return dou_result;
        }
    }
    return make_number(code_line);
}

aio_dou_result *make_number(char *code_line) {
    char *input_line = code_line;
    int i = 0;
    int dot = 0;
    int negative = -1;
    // 숫자는 마이너수로 시작할 수있다:
    if (input_line[0] == '-') {
        negative = 0;
        char *new_number = substring(input_line, 1, strlen(input_line) - 1);
        input_line = new_number;
    }
    // 숫자와 점을 허용하다:
    int line_length = strlen(input_line);
    while (i < line_length && (isdigit(input_line[i]) || input_line[i] == '.')) {
        // 오직 한 점!
        if (input_line[i] == '.' && ++dot > 1) {
            perror("cannot make a input_line in dou parser!");
            exit(1);
        }
        i++;
    }
    if (i == 0) { // 숫자를 찾지 못했습니다!
        perror("can't get valid input_line in '$input_line'");
        exit(1);
    }
    char *founded_number_str = substring(input_line, 0, i);
    aio_dou double_number = str_to_dou(founded_number_str);
    if (negative == 0) {
        double_number = (-1.0) * double_number;
    }
    char *rest_part = substring(input_line, i, line_length - i);
    aio_dou_result *dou_result = new_aio_dou_result(double_number, rest_part);
    return dou_result;
}

aio_dou_result *
make_method(char *method_name, aio_dou_result *dou_result, aio_object *object) {
    //덩으롼 객체에있는 메소드로 작업하기:
    if (is_default_dou_method(method_name, dou_result) != 0) {
        string_list *input_values = new_string_list();
        aio_str str_result = dou_to_str(dou_result->acc);
        add_in_string_list(input_values, str_result);
        aio_bundle *bundle = new_aio_bundle(input_values);
        char *corrected_method_name = "@";
        concat_string_to_string(corrected_method_name, method_name);
        invoke_method_in_manager(object, corrected_method_name, bundle);
        aio_str string_acc = bundle->output_values->strings[0];
        aio_dou acc = str_to_dou(string_acc);
        dou_result->acc = acc;
    }
    return dou_result;
}