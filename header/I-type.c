#include "I-type.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "registers.h"

int32_t sign_extend_12(int32_t value) {
    // If the MSB (bit 11) is set, extend the sign bit.
    if (value & 0x800) { // Check the 12th bit (bit 11, counting from 0)
        value |= ~0xFFF; // Set the upper bits to 1 to preserve the sign
    }
    return value;
}



I_type* ItypeDecode(unsigned int instruction, CPURegisters* reg) {
    // Dynamically allocate memory for the struct
    I_type* IInstruction = malloc(sizeof(I_type));
    if (IInstruction == NULL) {
        // Handle allocation failure
        return NULL;
    }
    
    
    // Extract the fields correctly using bitwise operations
    IInstruction->opcode = instruction & 0x7F;          // 7 bits for opcode (bits 6:0)
    IInstruction->rd = (instruction >> 7) & 0x1F;       // 5 bits for rd (bits 11:7)
    IInstruction->func3 = (instruction >> 12) & 0x7;    // 3 bits for func3 (bits 14:12)
    IInstruction->rs1 = (instruction >> 15) & 0x1F;     // 5 bits for rs1 (bits 19:15)

    if (IInstruction->func3 == 5 || IInstruction->func3 == 1)
    {
    IInstruction->shamt = (instruction >> 20) & 0x1F;      // 5 bits for (sh)ift (am)oun(t)  (bits 24:20)
    IInstruction->shtyp = (instruction >> 25) & 0x3F;      // 7 bits for (sh)ift (typ)e  (bits 31:25)
    IInstruction->immediate = 0;
    } 
    else
    {
    IInstruction->shamt = 0;
    IInstruction->shtyp = 0;
    IInstruction->immediate = sign_extend_12((instruction >> 20) & 0xFFF); // 12 bits for imm (bits 31:20)
    }
    
    return IInstruction;
}



void Ifunc3Decode(I_type* Iinstruct, CPURegisters* reg){

    switch (Iinstruct->func3)
    {
    case (7):
        andi(Iinstruct,reg);
        break;
    case (6):
        ori(Iinstruct,reg);
        break;
    case (5):
        if (Iinstruct->shtyp == 0)
        {
            srli(Iinstruct,reg);
        } else {
            srai(Iinstruct,reg);
        }     
        
        break;
    case (4):
        xori(Iinstruct,reg);
        break;
    case (3):
        sltiu(Iinstruct,reg);
        break;
    case (2):
        slti(Iinstruct,reg);
        break;
    case (1):
        slli(Iinstruct,reg);
        break;
    case (0):
        addi(Iinstruct,reg);
        break;
    default:
        break;
    }

    free(Iinstruct);
    return;
}




void andi(I_type* Iinstruct, CPURegisters* reg) {
    reg->x[Iinstruct->rd] = reg->x[Iinstruct->rs1] & Iinstruct->immediate;
    return;
}

void ori(I_type* Iinstruct, CPURegisters* reg) {
    reg->x[Iinstruct->rd] = reg->x[Iinstruct->rs1] | Iinstruct->immediate;
    return;
}
void srai(I_type* Iinstruct, CPURegisters* reg){ //arithmetic right shift the original sign bit is copied into the vacated upper bits
    reg->x[Iinstruct->rd] = ( (reg->x[Iinstruct->rs1]) >> (Iinstruct->shamt));

    return;
}
void srli(I_type* Iinstruct, CPURegisters* reg){ // logical right shift (zeros are shifted into the upper bits)
    reg->x[Iinstruct->rd] = ( ((uint32_t)reg->x[Iinstruct->rs1]) >> (Iinstruct->shamt));
    
    return;
}


void xori(I_type* Iinstruct, CPURegisters* reg) {
    reg->x[Iinstruct->rd] = reg->x[Iinstruct->rs1] ^ Iinstruct->immediate;
    return;
}
void sltiu(I_type* Iinstruct,CPURegisters* reg){
    if (
        (uint32_t) (reg->x[Iinstruct->rs1])
        < 
        (uint32_t) (Iinstruct->immediate))
    {
        reg->x[Iinstruct->rd] = 1;
    }
    else
    {
        reg->x[Iinstruct->rd] = 0;
    }
    return;
}

void slti(I_type* Iinstruct,CPURegisters* reg){
    if (
        (reg->x[Iinstruct->rs1])
        < 
        (Iinstruct->immediate))
    {
        reg->x[Iinstruct->rd] = 1;
    }
    else
    {
        reg->x[Iinstruct->rd] = 0;
    }
    return;
}

void slli(I_type* Iinstruct,CPURegisters* reg){ // logical left shift (zeros are shifted into the lower bits)

    reg->x[Iinstruct->rd] = ( ((uint32_t)reg->x[Iinstruct->rs1]) << (Iinstruct->shamt));

    return;
}

void addi(I_type* Iinstruct, CPURegisters* reg){
    reg->x[(Iinstruct->rd)] = reg->x[(Iinstruct->rs1)] + Iinstruct->immediate;
    return;
}