#ifndef AIO_INSTRUCTION_LIST_H
#define AIO_INSTRUCTION_LIST_H

typedef union aio_instruction_entry;

typedef struct aio_instruction_list {
    int capacity;
    int size;
    union aio_instruction_entry **instruction_entries;
} aio_instruction_list;

#endif //AIO_INSTRUCTION_LIST_H