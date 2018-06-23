#include <stdio.h>
#include "../../../../../../headers/lang/object/AIOObject.h"
#include "../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../headers/lib/utils/stringUtils/StringUtils.h"
#include "../../../../../../headers/tools/parsers/AIOParser.h"

void deleteBorders(char *codeLine, char **cleanLine){
    char* trimmedLine;
    trim(codeLine, &trimmedLine);
    char* withoutPrefix;
    removePrefix(trimmedLine, ">>", &withoutPrefix);
    trimStart(withoutPrefix, cleanLine);
    free(trimmedLine);
    free(withoutPrefix);
}

void squeezeCodeLine(char *codeLine, char **cleanLine){
    char** words;
    splitByChar(codeLine, ' ', &words);
    char** cleanedWords;
    filter(words, _msize(words) / 4, &cleanedWords, isNotEmpty);
    joinToStringWithoutSpaces(cleanedWords, cleanLine);
    free(words);
    free(cleanedWords);
}

void reproduceShortMethod(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                          AIOBundle *bundle, char *codeLine){
    printf("Short reproducing... %s\n", methodDefinition->name);
    char* withoutBordersLine;
    deleteBorders(codeLine, &withoutBordersLine);
    char* cleanedLine;
    squeezeCodeLine(withoutBordersLine, &cleanedLine);
    char* result = parseLineExpression(object, methodDefinition, methodContainer, codeLine);
    addInListOfString(bundle->outputValues, result);
    free(withoutBordersLine);
    free(cleanedLine);
}