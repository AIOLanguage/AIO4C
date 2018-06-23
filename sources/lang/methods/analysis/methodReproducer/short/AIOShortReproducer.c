#include <stdio.h>
#include "../../../../../../headers/lang/object/AIOObject.h"
#include "../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../headers/lib/utils/stringUtils/string_utils.h"
#include "../../../../../../headers/tools/parsers/AIOParser.h"

void deleteBorders(char *codeLine, char **cleanLine) {
    char *trimmedLine;
//    trim(codeLine, &trimmedLine);
    char *withoutPrefix;
//    remove_prefix(trimmedLine, ">>", &withoutPrefix);
  //  trim_start(withoutPrefix, cleanLine);
    free(trimmedLine);
    free(withoutPrefix);
}

void squeezeCodeLine(char *codeLine, char **cleanLine) {
    char **words;
//    split_by_string(codeLine, " ", &words);
    char **cleanedWords;
    filter(words, _msize(words) / 4, &cleanedWords, is_not_empty_string);
    join_to_string_without_spaces(cleanedWords, cleanLine);
    free(words);
    free(cleanedWords);
}

void reproduceShortMethod(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                          AIOBundle *bundle, char* codeLine) {
    printf("Short reproducing... %s\n", methodDefinition->name);
    char *withoutBordersLine;
    deleteBorders(codeLine, &withoutBordersLine);
    char *cleanedLine;
    squeezeCodeLine(withoutBordersLine, &cleanedLine);
    char *result = parseLineExpression(object, methodDefinition, methodContainer, codeLine);
    addInStringList(bundle->outputValues, result);
    free(withoutBordersLine);
    free(cleanedLine);
}