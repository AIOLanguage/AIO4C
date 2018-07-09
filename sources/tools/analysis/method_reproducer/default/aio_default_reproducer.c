#include <stdio.h>
#include "../../../../../../headers/lang/object/aio_file.h"
#include "../../../../../../headers/lang/methods/aio_method_container.h"
#include "../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../../headers/lang/methods/analysis/method_reproducer/short/aio_short_reproducer.h"

void reproduce_default_method(aio_file *object, aio_method_definition *method_definition,
                              aio_method_container *method_container, aio_bundle *bundle, char *code_line) {
    printf("\nDefault reproducing... %s", method_definition->name);
    const string_list *source_code = method_definition->source_code;
    for (int i = 0; i < source_code->size; ++i) {
        char *clean_line = trim(source_code->strings[i]);
        //variableCreator:
        // if (wasCreatingVariable == 0){
        //      continue;
        // }
        if (starts_with_prefix(source_code->strings[i], ">>") == 0) {
            reproduce_short_method(object, method_definition, method_container, bundle, code_line);
            break;
        }
    }
}