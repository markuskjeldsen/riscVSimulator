#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "file_read.h"
#include "decode.h"
#include "registers.h"



uint8_t* initSP(){

    uint8_t* SP = (uint8_t* )malloc( sizeof(uint8_t)*0x00100000 );
    if (SP == NULL)
    {
        printf("Stack pointer wasnt created");
    }
    
    return SP;
}

void printmemoryto(uint8_t* sp, int32_t upto){

        for (int i = 100; i < 136; i += 4) {
            printf("%0x: %u, %u, %u, %u\n",
            i, sp[i], sp[i + 1], sp[i + 2], sp[i + 3]);
            }


    
    printf("\n");    
}


void load_program_into_memory(uint8_t* sp, unsigned int* instructions) {
    int num_instructions = 256;

    for (int i = 0; i < num_instructions; i++) {
        sp[i * 4 + 3] = (instructions[i] & 0xFF000000) >> 24; // Extract the most significant byte
        sp[i * 4 + 2] = (instructions[i] & 0x00FF0000) >> 16; // Extract the second byte
        sp[i * 4 + 1] = (instructions[i] & 0x0000FF00) >> 8;  // Extract the third byte
        sp[i * 4 + 0] = (instructions[i] & 0x000000FF);       // Extract the least significant byte
    }
    return;
}

void printReg(CPURegisters* reg){
	for (int i = 0; i < 32 ; i++){
		printf("%d:%0x\n",i,reg->x[i]);
	}

}


int determineLength(unsigned int* I){
    int i = 0;
    while (I[i] != 0)
    {
        i++;
    }
    return i;
}


int main(int argc,char* argv[]) {


    char path[50];
    if(argv[1]){
    strcat(path,argv[1]);
    } else {
    strcat(path,"tests/width.bin");
    }

    uint8_t* sp = initSP();
    unsigned int* instructions = read_file(path);
    if(instructions == 1){
        return 1;
    }     
    CPURegisters* registers = init_registers();

    load_program_into_memory(sp,instructions);




    unsigned int value = 0;  // Create an unsigned int variable
    unsigned int *PC = &value;  // Set the value at the location PC points to as 0

    int length = determineLength(instructions) << 2;


    while (1)
    {
        if(execute(instructions, registers, PC, sp)){
            break;
        }
        *PC = *PC + 4;  

        printf("%0x \n", *PC);
        printmemoryto(sp, 64*4);
        registers->x[0] = 0;
        
    }

    printReg(registers);
    if (argc > 1) {
        int len = strlen(argv[1]);
        if (len > 3) {
            char newstring[18]; // Ensure sufficient space for the string and "res" suffix
            strncpy(newstring, argv[1], len - 3);
            newstring[len - 3] = '\0'; // Null-terminate the string

            strcat(newstring, "res"); // Add "res" to the string

            write_res_file(newstring, registers->x); // Example use with a dummy register value
            printf("%s\n", newstring);
        } else {
            printf("Input string is too short.\n");
        }
    } else {
        printf("No input argument provided.\n");
    }
    free(sp);
    free(instructions);
    return EXIT_SUCCESS;
}
