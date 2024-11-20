#include "B-type.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <registers.h>



int32_t offsetDecode(uint32_t instruction) {
    int first4 = (instruction >> 8) & 0xF;
    int next6 = (instruction >> 25) & 0b111111; // Bits [30:25]
    int next1 = (instruction >> 7) & 0x1;
    int last1 = (instruction >> 31) & 0x1;


    // Combine bitfields into the offset
    int32_t offset = (last1 << 11) |  // MSB (12th bit)
                     (next1 << 10) |  // 11th bit
                     (next6 << 4 ) |  // Bits [10:5]
                     (first4     );     // Bit 4

    if(last1){
        offset = offset | 0xFFFFF000;
    }
    offset = offset << 1;

    return offset;
    }



B_type* BtypeDecode(unsigned int instruction, CPURegisters* reg) {

    B_type* BInstruction = malloc(sizeof(B_type)); // Dynamically allocate memory for the struct
    if (BInstruction == NULL) {
        // Handle allocation failure
        return NULL;
    }   
    
    // Extract the fields correctly using bitwise operations
    BInstruction->opcode = instruction & 0x7F;          // 7 bits for opcode (bits 6:0)
    BInstruction->func3 = (instruction >> 12) & 0x7;    // 3 bits for func3 (bits 14:12)
    BInstruction->rs1 = (instruction >> 15) & 0x1F;     // 5 bits for rs1 (bits 19:15)
    BInstruction->rs2 = (instruction >> 20) & 0x1F;     // 5 bits for rs2 (bits 24:20)

    BInstruction->offset = offsetDecode(instruction) - 4;

    return BInstruction;
}

void Bfunc3Decode(B_type* Binstruct, CPURegisters* reg, unsigned int* PC ){
    
    
    
    switch (Binstruct->func3)
    {
    case 7: // bgeu
        bgeu(Binstruct, reg, PC);
        break;    
    case 6: // bltu
        bltu(Binstruct, reg, PC);
        break;
    case 5: // bge
        bge(Binstruct, reg, PC);
        break;
    case 4: // blt
        blt(Binstruct, reg, PC);
        break;
    case 1: // bne
        bne(Binstruct, reg, PC);
        break;
    case 0: // beq
        beq(Binstruct, reg, PC);
        break;
    default:
        break;
    }



    free(Binstruct);
    return;
}
void bgeu(B_type* Binstruct, CPURegisters* reg, unsigned int* PC){
    if (
        ((uint32_t)reg->x[Binstruct->rs1]) >= ((uint32_t)reg->x[Binstruct->rs2])
        )
    {
        *PC = *PC + Binstruct->offset;
    }
    return;

}
void bltu(B_type* Binstruct, CPURegisters* reg, unsigned int* PC){
    if (
        ((uint32_t)reg->x[Binstruct->rs1]) < ((uint32_t)reg->x[Binstruct->rs2])
        )
    {
        *PC = *PC + Binstruct->offset;
    }
    return;

}

void bge(B_type* Binstruct, CPURegisters* reg, unsigned int* PC){
    if (
        reg->x[Binstruct->rs1] > reg->x[Binstruct->rs2]
        )
    {
        *PC = *PC + Binstruct->offset;
    }
    return;

}

void blt(B_type* Binstruct, CPURegisters* reg, unsigned int* PC){
    if (
        reg->x[Binstruct->rs1] < reg->x[Binstruct->rs2]
        )
    {
        *PC = *PC + Binstruct->offset;
    }
    return;

}




void bne(B_type* Binstruct, CPURegisters* reg, unsigned int* PC){
    if (
        reg->x[Binstruct->rs1] != reg->x[Binstruct->rs2]
        )
    {
        *PC = *PC + Binstruct->offset;
    }
    return;
}
void beq(B_type* Binstruct, CPURegisters* reg, unsigned int* PC){
    if (
        reg->x[Binstruct->rs1] == reg->x[Binstruct->rs2]
        )
    {
        *PC = *PC + Binstruct->offset;
    }
    return;

}