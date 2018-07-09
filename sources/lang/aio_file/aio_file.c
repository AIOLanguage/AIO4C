#include "../../../headers/lang/aio_file/aio_file.h"
#include "../../../headers/lib/utils/file_utils/file_reader.h"
#include "../../../headers/lang/aio_method/aio_method.h"

void find_methods_in_manager(aio_file *aio_object);

const_string extract_name_from_path(const_string path);

/**
 * function is_valid_return_types:
 *
 * @param code_line - string, method signature;
 * @param ref_list - empty reference of string list which will be filled with return types;
 * @param next_point - start point of rest code line. This is a next point for future parsing of code_line.
 * @return has string method return types or not.
 */

boolean is_valid_return_types(const_string code_line, string_list **ref_list, int *next_point);

//Path example:
//"../aioPrograms/test.aio", "r"
aio_file *new_aio_file(const_string path) {
    aio_file *file = calloc(1, sizeof(aio_file));
    file->method_manager = new_aio_method_manager();
    //set name from path:
    file->name = extract_name_from_path(path);
    //loading code:
    file->source_code = read_file_and_collect_to_string_list(path);
    find_methods_in_manager(file);
    return file;
}

aio_method_manager *new_aio_method_manager() {
    aio_method_manager *method_manager = calloc(1, sizeof(aio_method_manager));
    method_manager->method_definition_map = new_aio_method_definition_map();
    return method_manager;
}

void invoke_method_in_manager(aio_file *object, const_string method_name, aio_bundle *bundle) {
    aio_method_definition *method_definition = get_aio_method_definition_in_map_by_name(
            object->method_manager->method_definition_map, method_name);
    invoke_new_aio_method(object, method_definition, bundle);
}