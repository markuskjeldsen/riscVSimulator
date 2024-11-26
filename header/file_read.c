#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "file_read.h"

#define INSTRUCTION_SIZE 4 // 4 bytes for 32 bits


unsigned int * read_file(char *path){
    FILE* file = fopen(path, "rb"); // Open in binary read mode
    if (!file) {
        perror("Failed to open file");
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Calculate number of 32-bit instructions
    size_t num_instructions = file_size / INSTRUCTION_SIZE;

    // Allocate memory for the instructions array
    unsigned int *instructions = malloc(num_instructions * (sizeof(unsigned int) + 1));
    if (!instructions) {
        perror("Failed to allocate memory");
        fclose(file);
    }

    // Read 32-bit instructions from the file
    for (size_t i = 0; i < num_instructions; i++) {
        if (fread(&instructions[i], INSTRUCTION_SIZE, 1, file) != 1) {
            perror("Failed to read instruction");
            free(instructions);
            fclose(file);
        }
    }
    instructions[num_instructions] = 0;

    fclose(file);


        

    return(instructions);
}