#include <stdio.h>
#include "../../../../../../headers/lang/object/aio_file.h"
#include "../../../../../../headers/lang/methods/aio_method_container.h"
#include "../../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../../headers/tools/parsers/aio_parser.h"

char *delete_borders(char *code_line) {
    char *trimmed_line = trim(code_line);
    char *without_prefix = remove_prefix(trimmed_line, ">>");
    char *clean_line = trim_start(without_prefix);
    free(trimmed_line);
    free(without_prefix);
    return clean_line;
}

char *squeeze_code_line(char *code_line) {
    char **words = split_by_string(code_line, " ");
    char **cleaned_words = filter(words, _msize(words) / 4, is_not_empty_string);
    char *clean_line = join_to_string(cleaned_words, "", _msize(cleaned_words) / 4);
    free(words);
    free(cleaned_words);
    return clean_line;
}

void reproduce_short_method(aio_file *object, aio_method_definition *method_definition,
                            aio_method_container *method_container,
                            aio_bundle *bundle, char *code_line) {
    printf("Short reproducing... %s\n", method_definition->name);
    char *without_borders_line = delete_borders(code_line);
    char *cleanedLine = squeeze_code_line(without_borders_line);
    char *result = parse_line_expression(object, method_definition, method_container, code_line);
    add_in_string_list(bundle->output_values, result);
    free(without_borders_line);
    free(cleanedLine);
}