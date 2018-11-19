//#ifdef __linux__

//#include <aio_parsing/aio_context_inflater/>
//void aio_core_builder::linux_builder::grub_aio_files() {
//#include <fts.h>
//#include <err.h>
//    //Create fts to list files and folders recursively:
//    const int fts_options = FTS_COMFOLLOW | FTS_LOGICAL | FTS_NOCHDIR;
//    char *const *build_path_ptr = &this->build_path;
//    //Open fts:
//    FTS *fts_ptr = fts_open(build_path_ptr, fts_options, nullptr);
//    if (!fts_ptr) {
//#ifdef AIO_CORE_BUILDER_DEBUG
//        log_info(AIO_CORE_BUILDER_WARNING_TAG, "fts is already opened!");
//#endif
//    }
//    //Check directory list:
//    FTSENT *child_ptr = fts_children(fts_ptr, 0);
//    if (!child_ptr) {
//        throw_error_with_tag(AIO_CORE_BUILDER_ERROR_TAG, "Project directory is empty");
//    }
//    //List files and folders:
//    while (true) {
//        FTSENT *ptr = fts_read(fts_ptr);
//        if (ptr) {
//            switch (ptr->fts_info) {
//                case FTS_D:
//#ifdef AIO_CORE_BUILDER_DEBUG
//                    log_info_string(AIO_CORE_BUILDER_INFO_TAG, "Detected directory: ", ptr->fts_path);
//#endif
//                    break;
//                case FTS_F : {
//                    const char *file_path = ptr->fts_path;
//#ifdef AIO_CORE_BUILDER_DEBUG
//                    log_info_string(AIO_CORE_BUILDER_INFO_TAG, "Detected file path:", file_path);
//#endif
//                    //If this is aio file:
//                    const bool is_aio_file_format = ends_with_suffix(file_path, AIO_FORMAT);
//                    if (is_aio_file_format) {
//                        grub_aio_file(file_path);
//                    }
//                }
//                    break;
//                default:
//                    break;
//            }
//        } else {
//            break;
//        }
//    }
//    fts_close(fts_ptr);
//}
//
//#endif