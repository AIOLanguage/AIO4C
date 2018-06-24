#include <stdio.h>
#include <process.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../headers/lang/types/aio_type.h"
#include "../../../../headers/lang/object/aio_object.h"
#include "../../../../headers/lang/methods/aio_method_container.h"
#include "../../../../headers/lang/methods/result/aio_result.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"

//제목들:

aio_dou_result *make_plus_or_minus(aio_object *object, aio_method_definition *method_definition,
                                   aio_method_container *method_container, char *code_line);

aio_dou_result *make_multiplication_or_division(aio_object *object, aio_method_definition *method_definition,
                                                aio_method_container *method_container, char *code_line);

aio_dou_result make_brackets(aio_object *object, aio_method_definition *method_definition,
                             aio_method_container *method_container, char *code_line);

aio_dou_result *make_method_or_variable(aio_object *object, aio_method_definition *method_definition,
                                        aio_method_container *method_container, char *code_line);

aio_dou_result *make_method(char *method_name, aio_dou_result *dou_result, aio_object *object);

aio_dou_result *makeNumber(char *codeLine);

/**
 * parseDouLineExpression
 * plusOrMinus -> multiplicationOrDivision -> brackets -> method or variable or number:
 */

aio_str
parse_dou_line_expression(aio_object *object, aio_method_definition *method_definition,
                          aio_method_container *method_container,
                          char *code_line) {
    const aio_dou_result *douResult = make_plus_or_minus(object, method_definition, method_container, code_line);
    if (is_not_empty_string(douResult->rest) == 0) {
        perror("cannot full parse code line!");
        exit(1);
    }
    aio_str result;
    dou_to_str(*douResult->acc, &result);
    return result;
}

aio_dou_result *
make_plus_or_minus(aio_object *object, aio_method_definition *method_definition, aio_method_container *method_container,
                   char *code_line) {
    aio_dou_result *current = make_multiplication_or_division(object, method_definition, method_container, code_line);
    aio_dou acc = *current->acc;
    while (is_empty_string(current->rest) == 0) {
        const char sign = current->rest[0];
        if (!(sign == '+' || sign == '-')) {
            break;
        }
        char *next;
//        substring(current->rest, 1, strlen(current->rest) - 1, &next);
        current = make_multiplication_or_division(object, method_definition, method_container, next);
        if (sign == '+') {
            acc = acc + *current->acc;
        } else {
            acc = acc - *current->acc;
        }
    }
    aio_dou_result *douResult;
    new_aio_dou_result(&douResult, acc, current->rest);
    return douResult;
}

aio_dou_result *make_multiplication_or_division(aio_object *object, aio_method_definition *method_definition,
                                                aio_method_container *method_container,
                                                char *code_line) {
    aio_dou_result *current = make_brackets(object, method_definition, method_container, code_line);
    aio_dou acc = *current->acc;
    while (1) {
        if (is_empty_string(current->rest) == 0) {
            return current;
        }
        const char sign = current->rest[0];
        if (sign != '*' && sign != '/') {
            return current;
        }
        char *next;
//        substring(current->rest, 1, strlen(current->rest) - 1, &next);
        aio_dou_result *aioBracketResult = make_brackets(object, method_definition, method_container, next);
        if (sign == '*') {
            acc = acc * *aioBracketResult->acc;
        } else {
            acc = acc / *aioBracketResult->acc;
        }
        aio_dou_result *douResult;
        new_aio_dou_result(&douResult, acc, aioBracketResult->rest);
        current = douResult;
    }
}

aio_dou_result *
make_brackets(aio_object *object, aio_method_definition *method_definition, aio_method_container *method_container,
              char *code_line) {
    const char zeroChar = code_line[0];
    if (zeroChar == '(') {
        char *inBracketsCodeLine;
//        substring(code_line, 1, strlen(code_line) - 1, &inBracketsCodeLine);
        aio_dou_result *inBracketsAIOResult = make_plus_or_minus(object, method_definition, method_container,
                                                                 inBracketsCodeLine);
        if (is_not_empty_string(inBracketsAIOResult->rest) == 0 && inBracketsAIOResult->rest[0] == ')') {
            char *afterBracketsCodeLine;
            //  substring(inBracketsAIOResult->rest, 1, strlen(inBracketsAIOResult->rest) - 1, &afterBracketsCodeLine);
            inBracketsAIOResult->rest = afterBracketsCodeLine;
        } else {
            perror("cannot close bracket!");
            exit(1);
        }
        return inBracketsAIOResult;
    }
    return make_method_or_variable(object, method_definition, method_container, code_line);
}

aio_dou_result *
make_method_or_variable(aio_object *object, aio_method_definition *method_definition,
                        aio_method_container *method_container,
                        char *code_line) {
    char *methodOrVariableName = "";
    int i = 0;
    // 함수 이름 또는 변수 이름 찾기,
    // 이름은 반드시 문지로 시작해야한다:
    int codeLineLength = strlen(code_line);
    while (i < codeLineLength && (isalpha(code_line[i]) || (isdigit(code_line[i]) && i != 0))) {
        concat_char_to_string(code_line[i], &methodOrVariableName);
        i = i + 1;
    }
    if (i == codeLineLength) {
        i--;
    }
    if (is_not_empty_string(methodOrVariableName) == 0) { // 무언가가 발견도면
        const size_t methodOrVariableStrLength = strlen(methodOrVariableName);
        if (i < codeLineLength && code_line[i] == '(' || code_line[i] == '~') {
            if (code_line[i] == '(') {
                // 그것은 함수이다:
                char *inBracketsLine;
//                substring(methodOrVariableName, methodOrVariableStrLength, codeLineLength - methodOrVariableStrLength,
                //      &inBracketsLine);
                aio_dou_result *inFunctionAIOResult = make_brackets(object, method_definition, method_container,
                                                                    inBracketsLine);
                //하나의 arg:
                return make_method(methodOrVariableName, inFunctionAIOResult, object);
            } else {
                //arg 이없는:
                aio_dou_result *emptyDouResult;
                new_aio_dou_result(&emptyDouResult, 0.0, "");
                aio_dou_result *insteadMethod = make_method(methodOrVariableName, emptyDouResult, object);
                char *accStrResult;
                dou_to_str(*insteadMethod->acc, &accStrResult);
                char *nextCodeLine;
                //      substring(code_line, methodOrVariableStrLength + 1, codeLineLength - methodOrVariableStrLength - 1,
                //   &nextCodeLine);
                concat_string_to_string(accStrResult, &nextCodeLine);
                free(nextCodeLine);
                return make_plus_or_minus(object, method_definition, method_container, accStrResult);
            }
        } else { //그것은 변수이다:
            char *variableName = methodOrVariableName;
            aio_variable *variable = get_variable_from_method_container(variableName, method_container);
            char *rest;
//            substring(code_line, methodOrVariableStrLength, codeLineLength - methodOrVariableStrLength, &rest);
            aio_dou_result *douResult;
            aio_dou *acc;
            str_to_dou(variable->value, &acc);
            new_aio_dou_result(&douResult, *acc, rest);
            return douResult;
        }
    }
    return makeNumber(code_line);
}

aio_dou_result *makeNumber(char *codeLine) {
    char *inputLine = codeLine;
    int i = 0;
    int dot = 0;
    int negative = -1;
    // 숫자는 마이너수로 시작할 수있다:
    char *newNumber;
    if (inputLine[0] == '-') {
        negative = 0;
        //     substring(inputLine, 1, strlen(inputLine) - 1, &newNumber);
    }
    // 숫자와 점을 허용하다:
    int lineLength = strlen(inputLine);
    while (i < lineLength && (isdigit(inputLine[i]) || inputLine[i] == '.')) {
        // 오직 한 점!
        if (inputLine[i] == '.' && ++dot > 1) {
            perror("cannot make a inputLine in dou parser!");
            exit(1);
        }
        i = i + 1;
    }
    if (i == 0) { // 숫자를 찾지 못했습니다!
        perror("can't get valid inputLine in '$inputLine'");
        exit(1);
    }
    char *foundedNumberStr;
//    substring(inputLine, 0, i, &foundedNumberStr);
    aio_dou *doubleNumber;
    str_to_dou(foundedNumberStr, &doubleNumber);
    if (negative == 0) {
        *doubleNumber = (-1.0) * *doubleNumber;
    }
    char *restPart;
    // substring(inputLine, i, lineLength - i, &restPart);
    aio_dou_result *douResult;
    new_aio_dou_result(&douResult, *doubleNumber, restPart);
    return douResult;
}

aio_dou_result *
make_method(char *method_name, aio_dou_result *dou_result, aio_object *object) {
    //덩으롼 객체에있는 메소드로 작업하기:
    if (is_default_dou_method(method_name, dou_result) != 0) {
        aio_bundle *bundle;
        string_list *inputValues;
        new_string_list(&inputValues);
        aio_str strResult;
        dou_to_str(*dou_result->acc, &strResult);
        add_in_string_list(inputValues, strResult);
        new_aio_bundle(&bundle, inputValues);
        char *correctedMethodName = "@";
        concat_string_to_string(method_name, &correctedMethodName);
        invoke_method_in_manager(object, correctedMethodName, bundle);
        aio_str stringAcc = bundle->output_values->strings[0];
        aio_dou *acc;
        str_to_dou(stringAcc, &acc);
        *dou_result->acc = *acc;
    }
    return dou_result;
}