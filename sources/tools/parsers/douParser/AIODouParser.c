#include <stdio.h>
#include <process.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../headers/lang/types/AIOType.h"
#include "../../../../headers/lang/object/AIOObject.h"
#include "../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../headers/lang/methods/result/AIOResult.h"
#include "../../../../headers/lib/utils/stringUtils/string_utils.h"
#include "../../../../headers/tools/parsers/AIOParser.h"
#include "../../../../headers/lang/methods/defaultMethodContainer/AIODefaultMethodContainer.h"

//제목들:

AIODouResult *
makePlusOrMinus(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                char *codeLine);

AIODouResult *makeMultiplicationOrDivision(AIOObject *object, AIOMethodDefinition *methodDefinition,
                                           AIOMethodContainer *methodContainer,
                                           char *codeLine);

AIODouResult *
makeBrackets(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
             char *codeLine);

AIODouResult *
makeMethodOrVariable(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                     char *codeLine);

AIODouResult *
makeMethod(char *methodName, AIODouResult *douResult, AIOObject *object);

AIODouResult *makeNumber(char *codeLine);

/**
 * parseDouLineExpression
 * plusOrMinus -> multiplicationOrDivision -> brackets -> method or variable or number:
 */

AIOStr
parseDouLineExpression(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       char *codeLine) {
    const AIODouResult *douResult = makePlusOrMinus(object, methodDefinition, methodContainer, codeLine);
    if (is_not_empty_string(douResult->rest) == 0) {
        perror("cannot full parse code line!");
        exit(1);
    }
    AIOStr result;
    douToStr(*douResult->acc, &result);
    return result;
}

AIODouResult *
makePlusOrMinus(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                char *codeLine) {
    AIODouResult *current = makeMultiplicationOrDivision(object, methodDefinition, methodContainer, codeLine);
    AIODou acc = *current->acc;
    while (is_empty_string(current->rest) == 0) {
        const char sign = current->rest[0];
        if (!(sign == '+' || sign == '-')) {
            break;
        }
        char *next;
        substring(current->rest, 1, strlen(current->rest) - 1, &next);
        current = makeMultiplicationOrDivision(object, methodDefinition, methodContainer, next);
        if (sign == '+') {
            acc = acc + *current->acc;
        } else {
            acc = acc - *current->acc;
        }
    }
    AIODouResult *douResult;
    createAIODouResult(&douResult, acc, current->rest);
    return douResult;
}

AIODouResult *makeMultiplicationOrDivision(AIOObject *object, AIOMethodDefinition *methodDefinition,
                                           AIOMethodContainer *methodContainer,
                                           char *codeLine) {
    AIODouResult *current = makeBrackets(object, methodDefinition, methodContainer, codeLine);
    AIODou acc = *current->acc;
    while (1) {
        if (is_empty_string(current->rest) == 0) {
            return current;
        }
        const char sign = current->rest[0];
        if (sign != '*' && sign != '/') {
            return current;
        }
        char *next;
        substring(current->rest, 1, strlen(current->rest) - 1, &next);
        AIODouResult *aioBracketResult = makeBrackets(object, methodDefinition, methodContainer, next);
        if (sign == '*') {
            acc = acc * *aioBracketResult->acc;
        } else {
            acc = acc / *aioBracketResult->acc;
        }
        AIODouResult *douResult;
        createAIODouResult(&douResult, acc, aioBracketResult->rest);
        current = douResult;
    }
}

AIODouResult *
makeBrackets(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
             char *codeLine) {
    const char zeroChar = codeLine[0];
    if (zeroChar == '(') {
        char *inBracketsCodeLine;
        substring(codeLine, 1, strlen(codeLine) - 1, &inBracketsCodeLine);
        AIODouResult *inBracketsAIOResult = makePlusOrMinus(object, methodDefinition, methodContainer,
                                                            inBracketsCodeLine);
        if (is_not_empty_string(inBracketsAIOResult->rest) == 0 && inBracketsAIOResult->rest[0] == ')') {
            char *afterBracketsCodeLine;
            substring(inBracketsAIOResult->rest, 1, strlen(inBracketsAIOResult->rest) - 1, &afterBracketsCodeLine);
            inBracketsAIOResult->rest = afterBracketsCodeLine;
        } else {
            perror("cannot close bracket!");
            exit(1);
        }
        return inBracketsAIOResult;
    }
    return makeMethodOrVariable(object, methodDefinition, methodContainer, codeLine);
}

AIODouResult *
makeMethodOrVariable(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                     char *codeLine) {
    char *methodOrVariableName = "";
    int i = 0;
    // 함수 이름 또는 변수 이름 찾기,
    // 이름은 반드시 문지로 시작해야한다:
    int codeLineLength = strlen(codeLine);
    while (i < codeLineLength && (isalpha(codeLine[i]) || (isdigit(codeLine[i]) && i != 0))) {
        concat_char_to_string(codeLine[i], &methodOrVariableName);
        i = i + 1;
    }
    if (i == codeLineLength) {
        i--;
    }
    if (is_not_empty_string(methodOrVariableName) == 0) { // 무언가가 발견도면
        const size_t methodOrVariableStrLength = strlen(methodOrVariableName);
        if (i < codeLineLength && codeLine[i] == '(' || codeLine[i] == '~') {
            if (codeLine[i] == '(') {
                // 그것은 함수이다:
                char *inBracketsLine;
                substring(methodOrVariableName, methodOrVariableStrLength, codeLineLength - methodOrVariableStrLength,
                          &inBracketsLine);
                AIODouResult *inFunctionAIOResult = makeBrackets(object, methodDefinition, methodContainer,
                                                                 inBracketsLine);
                //하나의 arg:
                return makeMethod(methodOrVariableName, inFunctionAIOResult, object);
            } else {
                //arg 이없는:
                AIODouResult *emptyDouResult;
                createAIODouResult(&emptyDouResult, 0.0, "");
                AIODouResult *insteadMethod = makeMethod(methodOrVariableName, emptyDouResult, object);
                char *accStrResult;
                douToStr(*insteadMethod->acc, &accStrResult);
                char *nextCodeLine;
                substring(codeLine, methodOrVariableStrLength + 1, codeLineLength - methodOrVariableStrLength - 1,
                          &nextCodeLine);
                concat_string_to_string(accStrResult, &nextCodeLine);
                free(nextCodeLine);
                return makePlusOrMinus(object, methodDefinition, methodContainer, accStrResult);
            }
        } else { //그것은 변수이다:
            char *variableName = methodOrVariableName;
            AIOVariable *variable = getVariable(variableName, methodContainer);
            char *rest;
            substring(codeLine, methodOrVariableStrLength, codeLineLength - methodOrVariableStrLength, &rest);
            AIODouResult *douResult;
            AIODou *acc;
            strToDou(variable->value, &acc);
            createAIODouResult(&douResult, *acc, rest);
            return douResult;
        }
    }
    return makeNumber(codeLine);
}

AIODouResult *makeNumber(char *codeLine) {
    char *inputLine = codeLine;
    int i = 0;
    int dot = 0;
    int negative = -1;
    // 숫자는 마이너수로 시작할 수있다:
    char *newNumber;
    if (inputLine[0] == '-') {
        negative = 0;
        substring(inputLine, 1, strlen(inputLine) - 1, &newNumber);
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
    substring(inputLine, 0, i, &foundedNumberStr);
    AIODou *doubleNumber;
    strToDou(foundedNumberStr, &doubleNumber);
    if (negative == 0) {
        *doubleNumber = (-1.0) * *doubleNumber;
    }
    char *restPart;
    substring(inputLine, i, lineLength - i, &restPart);
    AIODouResult *douResult;
    createAIODouResult(&douResult, *doubleNumber, restPart);
    return douResult;
}

AIODouResult *
makeMethod(char *methodName, AIODouResult *douResult, AIOObject *object) {
    //덩으롼 객체에있는 메소드로 작업하기:
    if (isDefaultDouMethod(methodName, douResult) != 0) {
        AIOBundle *bundle;
        StringList *inputValues;
        createStringList(&inputValues);
        AIOStr strResult;
        douToStr(*douResult->acc, &strResult);
        addInStringList(inputValues, strResult);
        createAIOBundle(&bundle, inputValues);
        char *correctedMethodName = "@";
        concat_string_to_string(methodName, &correctedMethodName);
        invokeMethodInManager(object, correctedMethodName, bundle);
        AIOStr stringAcc = bundle->outputValues->strings[0];
        AIODou *acc;
        strToDou(stringAcc, &acc);
        *douResult->acc = *acc;
    }
    return douResult;
}