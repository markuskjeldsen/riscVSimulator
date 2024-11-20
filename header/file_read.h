#include <file_read.c>



typedef struct {
    unsigned int *instructions;
    uint32_t length;
} instruction_file;


unsigned int * read_file(char *path);
