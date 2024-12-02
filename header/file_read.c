#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "file_read.h"

#define INSTRUCTION_SIZE 4 // 4 bytes for 32 bits
#define NUM_REGISTERS 32
#define BYTES_PER_REGISTER 4
#define FILE_SIZE (NUM_REGISTERS * BYTES_PER_REGISTER)

unsigned int * read_file(char *path){
    FILE* file = fopen(path, "rb"); // Open in binary read mode
    if (!file) {
        perror("Failed to open file");
        return 1;
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



void write_res_file(const char *filename, int32_t registers[NUM_REGISTERS]) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_REGISTERS; i++) {
        uint32_t reg_value = registers[i];
        uint8_t bytes[BYTES_PER_REGISTER];
        bytes[0] = reg_value & 0xFF;         // Least significant byte
        bytes[1] = (reg_value >> 8) & 0xFF;
        bytes[2] = (reg_value >> 16) & 0xFF;
        bytes[3] = (reg_value >> 24) & 0xFF; // Most significant byte
        fwrite(bytes, 1, BYTES_PER_REGISTER, file);
    }

    fclose(file);
}



