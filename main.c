#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <file_read.c>
#include <decode.c>
#include <registers.c>


uint8_t* initSP(){

    uint8_t* SP = (uint8_t* )malloc( sizeof(uint8_t)*0x00100000 );
    if (SP == NULL)
    {
        printf("Stack pointer wasnt created");
    }
    
    return SP;
}

void printmemoryto(uint8_t* sp, int32_t upto){

        printf("one cycle more!\n");
        

        for(int i = 0x00100000; i > 0x00100000 - upto; i--){
            if(i%4 == 0){
                printf("\n");
            }
                printf("%0x",sp[i]);
         
         
         
            
        }
        /*
        for (int32_t i = 0; i < upto; i++)
        {
        if (i == 0)
        {
            printf("%0x:%d \t",i,sp[i]);
        } else if (i % 4 == 0)
        {
            printf("\n");
           printf("%0x:%d \t",i,sp[i]);
        } else if (i % 4 == 3){
            printf("%0x:%d \t \n",i,sp[i]);
        }
        }
        */

    
    printf("\n");    
}


void load_program_into_memory(uint8_t* sp, unsigned int* instructions) {
    int num_instructions = 100;

    for (int i = 0; i < num_instructions; i++) {
        sp[i * 4 + 3] = (instructions[i] & 0xFF000000) >> 24; // Extract the most significant byte
        sp[i * 4 + 2] = (instructions[i] & 0x00FF0000) >> 16; // Extract the second byte
        sp[i * 4 + 1] = (instructions[i] & 0x0000FF00) >> 8;  // Extract the third byte
        sp[i * 4 + 0] = (instructions[i] & 0x000000FF);       // Extract the least significant byte
    }
/*
    for (int i = 0; i < num_instructions * 4; i += 4) {
        printf("%2zu: %u, %u, %u, %u\n",
                i, sp[i], sp[i + 1], sp[i + 2], sp[i + 3]
            );
    }
*/
    return;
}




int determineLength(unsigned int* I){
    int i = 0;
    while (I[i] != 0)
    {
        i++;
    }
    return i;
}


int main() {


    char* path = "tests/string.bin";
    uint8_t* sp = initSP();
    unsigned int* instructions = read_file(path);     
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

    free(sp);
    free(instructions);
    return EXIT_SUCCESS;
}


// 00 50 01 93 
// 00 31 81 B3

