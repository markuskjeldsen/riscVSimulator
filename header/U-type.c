#include "U-type.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <registers.h>

U_type* UtypeDecode(unsigned int instruction, CPURegisters* reg) {
    U_type* UInstruction = malloc(sizeof(U_type));
    if (UInstruction == NULL) {
        return NULL;
    }
    
    UInstruction->opcode = (instruction & 0x3F);  // 6 bits for opcode
    UInstruction->rd = (instruction >> 7) & 0x1F;  // 5 bits for rd
    UInstruction->immediate = (instruction >> 12);  // 20 bits for immediate
    
    return UInstruction;
}


void lui(U_type* Uinstruct, CPURegisters* reg){
    int ui = (Uinstruct->immediate) << 12;
    reg->x[(Uinstruct->rd)] = ui;

    free(Uinstruct);
    return;
}

