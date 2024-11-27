#include "R-type.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "registers.h"

R_type* RtypeDecode(unsigned int instruction, CPURegisters* reg) {

    R_type* RInstruction = malloc(sizeof(R_type)); // Dynamically allocate memory for the struct
    if (RInstruction == NULL) {
        // Handle allocation failure
        return NULL;
    }   
    
    // Extract the fields correctly using bitwise operations
    RInstruction->opcode = instruction & 0x7F;          // 7 bits for opcode (bits 6:0)
    RInstruction->rd = (instruction >> 7) & 0x1F;       // 5 bits for rd (bits 11:7)
    RInstruction->func3 = (instruction >> 12) & 0x7;    // 3 bits for func3 (bits 14:12)
    RInstruction->rs1 = (instruction >> 15) & 0x1F;     // 5 bits for rs1 (bits 19:15)
    RInstruction->rs2 = (instruction >> 20) & 0x1F;     // 5 bits for rs2 (bits 24:20)
    RInstruction->func7 = (instruction >> 25) & 0x7F;   // 7 bits for func7 (bits 31:25)
    
    return RInstruction;
}

void Rfunc3Decode(R_type* Rinstruct, CPURegisters* reg){

    switch (Rinstruct->func3)
    {
    case (7):
        and(Rinstruct,reg);
        break;
    case (6):
        or(Rinstruct,reg);
        break;
    case (5):
        if (Rinstruct->func7 == 0)
        {
            srl(Rinstruct,reg);
        } else {
            sra(Rinstruct,reg);
        }   
        break;
    case (4):
        xor(Rinstruct,reg);
        break;
    case (3):
        sltu(Rinstruct,reg);
        break;
    case (2):
        slt(Rinstruct,reg);
        break;
    case (1):
        sll(Rinstruct,reg);
        break;
    case (0):
        Rfunc7Decode(Rinstruct,reg);
        break;
    default:
        break;
    }

    free(Rinstruct);
    return;
}


void Rfunc7Decode(R_type* Rinstruct, CPURegisters* reg){

switch (Rinstruct->func7)
    {
    case(0):
        add(Rinstruct,reg);
        break;
    case(32):
        sub(Rinstruct,reg);
        break;
    default:
        break;
    }
    
    return;
}




void add(R_type* Rinstruct, CPURegisters* reg) {
    reg->x[Rinstruct->rd] = reg->x[Rinstruct->rs1] + reg->x[Rinstruct->rs2];
    return;
}

void sub(R_type* Rinstruct, CPURegisters* reg) {
    reg->x[Rinstruct->rd] = reg->x[Rinstruct->rs1] - reg->x[Rinstruct->rs2];
        return;
}

void xor(R_type* Rinstruct, CPURegisters* reg) {
    // Perform bitwise XOR on the values in registers rs1 and rs2
    reg->x[Rinstruct->rd] = reg->x[Rinstruct->rs1] ^ reg->x[Rinstruct->rs2];
    return;
}

void and(R_type* Rinstruct, CPURegisters* reg) {
    // Perform bitwise AND on the values in registers rs1 and rs2
    reg->x[Rinstruct->rd] = reg->x[Rinstruct->rs1] & reg->x[Rinstruct->rs2];
    return;
}

void or(R_type* Rinstruct, CPURegisters* reg) {
    // Perform bitwise OR on the values in registers rs1 and rs2
    reg->x[Rinstruct->rd] = reg->x[Rinstruct->rs1] | reg->x[Rinstruct->rs2];
    return;
}

void sra(R_type* Rinstruct, CPURegisters* reg){

    reg->x[Rinstruct->rd] = (  (reg->x[Rinstruct->rs1]) >> (reg->x[Rinstruct->rs2] & 0x1F));


    return;
}

void srl(R_type* Rinstruct, CPURegisters* reg){
    
    reg->x[Rinstruct->rd] = ( (uint32_t)(reg->x[Rinstruct->rs1]) >> (reg->x[Rinstruct->rs2 ] & 0x1F));


    return;
}

void sltu(R_type* Rinstruct,CPURegisters* reg){
    if (
        (uint32_t) (reg->x[Rinstruct->rs1])
        < 
        (uint32_t) (reg->x[Rinstruct->rs2]))
    {
        reg->x[Rinstruct->rd] = 1;
    }
    else
    {
        reg->x[Rinstruct->rd] = 0;
    }
    
    
}

void slt(R_type* Rinstruct,CPURegisters* reg){
    if (
    (reg->x[Rinstruct->rs1])
    < 
    (reg->x[Rinstruct->rs2]) )
    {
        reg->x[Rinstruct->rd] = 1;
    }
    else
    {
        reg->x[Rinstruct->rd] = 0;
    }
}

void sll(R_type* Rinstruct,CPURegisters* reg){

    reg->x[Rinstruct->rd] = (  (uint32_t)(reg->x[Rinstruct->rs1]) << (reg->x[Rinstruct->rs2] & 0x1F) );

    return;
}