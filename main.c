#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <file_read.c>
#include <decode.c>
#include <registers.c>


uint8_t* initSP(){

    uint8_t* SP = (uint8_t)malloc( sizeof(uint32_t)*1048576 );
    if (SP == NULL)
    {
        printf("Stack pointer wasnt created");
    }
    
    return SP;
}

void printmemoryto(uint8_t* sp, int32_t upto){

        printf("one cycle more!\n");
        for (int32_t i = 0; i < upto; i++)
        {
        if (i == 0)
        {
            printf("%0x:%d \t",i,sp[i]);
        } else if (i % 4 == 0)
        {
            printf("\n");
            printf("%0x:%d \t",i,sp[i]);
        } else {
            printf("%0x:%d \t",i,sp[i]);
        }
        }

    
    printf("\n");    
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


    char* path = "tests/loop.bin";
    uint8_t* sp = initSP();
    unsigned int* instructions = read_file(path);     
    CPURegisters* registers = init_registers();

    unsigned int value = 0;  // Create an unsigned int variable
    unsigned int *PC = &value;  // Set the value at the location PC points to as 0

    int length = determineLength(instructions) << 2;


    while (1)
    {
        if(execute(instructions, registers, PC, sp)){
            break;
        }
        *PC = *PC + 4;  
        if(length < *PC ){
            break;
        }
        printf("%d \n", *PC);
        printmemoryto(sp, 32);
        
    }

    free(sp);
    free(instructions);
    return EXIT_SUCCESS;
}


// 00 50 01 93 
// 00 31 81 B3

