#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <file_read.c>
#include <decode.c>
#include <registers.c>


// 00 50 01 93 
// 00 31 81 B3

typedef struct {
    int counter;
    
} ProgramCounter;


int determineLength(unsigned int* I){
    int i = 0;
    while (I[i] != 0)
    {
        i++;
    }
    return i;
}







int main() {


    //int opcode = (instructions[0] & (0b000000000000000000000000001111111))
    char* path = "tests/branchcnt.bin";
    unsigned int* instructions = read_file(path);     
    CPURegisters* registers = init_registers();

    unsigned int value = 0;  // Create an unsigned int variable
    unsigned int *PC = &value;  // Set the value at the location PC points to as 0

    int length = determineLength(instructions);
    //int length = sizeof(instructions) / sizeof(instructions[0]); 


    while (1)
    {
        if(execute(instructions, registers, PC)){
            break;
        }
        *PC = *PC + 4;  
        if(length < (*PC) / 4 ){
            break;
        }
    }

    
    free(instructions);
    return EXIT_SUCCESS;
}


// 00 50 01 93 
// 00 31 81 B3

