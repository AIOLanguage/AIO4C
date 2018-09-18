#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <lib4aio_cpp_headers/utils/string_utils/trim.h>
#include <lib4aio_cpp_headers/utils/string_utils/split.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

//#define FILE_READER_DEBUG

#ifdef FILE_READER_DEBUG

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

namespace lib4aio {

#define READ "r"

#define FILE_READER_TAG "FILE_READER"

#define AIO_COMMENTS "//"

#define AIO_SUFFIX ".aio"

#define AIO_SUFFIX_LENGTH 4

    static const char *get_code_without_comments(const char *file_content)
    {
#ifdef FILE_READER_DEBUG
        log_info_string(FILE_READER_TAG, "파일 내용:", file_content);
#endif
        struct_list *lines = split_by_line_break(file_content);
        struct_list *clean_line_list = new_struct_list(sizeof(char *));
#ifdef FILE_READER_DEBUG
        for (unsigned k = 0; k < lines->size; ++k) {
            log_info_string(FILE_READER_TAG, "라인:", (char *) lines->elements[k]);
        }
#endif
        for (unsigned i = 0; i < lines->size; i++) {
            const char *line = static_cast<const char *>(lines->elements[i]);
            if (!starts_with_prefix(line, AIO_COMMENTS) && !is_empty_string(line)) {
                struct_list *dirty_lines_with_comments = split_by_string(line, AIO_COMMENTS);
                const char *first_dirty_line = static_cast<const char *>(dirty_lines_with_comments->elements[0]);
                char *clean_line = trim(first_dirty_line);
                if (is_not_empty_string(clean_line)) {
                    add_struct_in_list(clean_line_list, clean_line);
                }
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기:
                free_structs_in_list(dirty_lines_with_comments, free);
                free_struct_list(dirty_lines_with_comments);
            }
        };
        const char *clean_code = join_to_string(clean_line_list, "\n");
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기:
        free_structs_in_list(lines, free);
        free_structs_in_list(clean_line_list, free);
        free_struct_list(lines);
        free_struct_list(clean_line_list);
        //--------------------------------------------------------------------------------------------------------------
#ifdef FILE_READER_DEBUG
        log_info_string(FILE_READER_TAG, "소스 코드:", clean_code);
#endif
        return clean_code;
    }

    const char *get_source_code_by_file_path(const_string path)
    {
        str_builder *string_builder = new str_builder();
        //파일을 만들다:
        FILE *file = fopen(path, READ);
        if (file) {
            while (true) {
                const char current_char = (char) fgetc(file);
                if (current_char != EOF) {
                    string_builder->append(current_char);
                } else {
                    break;
                }
            }
            fclose(file);
            char *file_content = string_builder->pop();
            const char *clean_code = get_code_without_comments(file_content);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            delete string_builder;
            free(file_content);
            //----------------------------------------------------------------------------------------------------------
            return clean_code;
        } else {
            throw_error("소스 파일을 열 수 없습니다 (Cannot open source file).");
        }
    }

    const str_hook *get_name_by_file_path(const_string path)
    {
        if (ends_with_suffix(path, AIO_SUFFIX)) {
            const unsigned last_path_index = static_cast<const unsigned int>(strlen(path) - 1);
            for (unsigned i = last_path_index; i >= 0; --i) {
                const char symbol = path[i];
                //파일 이름 되다 (Pass file name):
                if (symbol == '/') {
                    const unsigned offset = i + 1;
                    const unsigned length = last_path_index - i - AIO_SUFFIX_LENGTH;
                    const str_hook *file_name = new str_hook(path, offset, offset + length);
                    if (file_name->is_word()) {
#ifdef FILE_READER_DEBUG
                        log_info_str_hook(FILE_READER_TAG, "컨텍스트 이름 (Context name):", file_name);
#endif
                        return file_name;
                    } else {
                        throw_error_with_tag(
                                FILE_READER_TAG,
                                "*.aio 파일 이름을 잘못되었습니다 (*.aio file name is invalid)!"
                        );
                    }
                }
            }
            throw_error_with_tag(
                    FILE_READER_TAG,
                    "*.aio 파일 이름을 잘못되었습니다 (*.aio file name is invalid)!"
            );
        } else {
            throw_error_with_tag(
                    FILE_READER_TAG,
                    "파일 형식이 'aio' 가 아닙니다 (File type is not 'aio')!"
            );
        }
    }
}