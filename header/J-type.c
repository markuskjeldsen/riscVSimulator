#include "J-type.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <registers.h>



J_type* JtypeDecode(unsigned int instruction, CPURegisters* reg) {
    // Dynamically allocate memory for the struct
    J_type* JInstruction = malloc(sizeof(J_type));
    if (JInstruction == NULL) {
        // Handle allocation failure
        return NULL;
    }




    
    
    // Extract the fields correctly using bitwise operations
    JInstruction->opcode = instruction & 0x7F;          // 7 bits for opcode (bits 6:0)
    if (JInstruction->opcode == 103)
    {

    JInstruction->opcode = instruction & 0x7F;          // 7 bits for opcode (bits 6:0)
    JInstruction->rd = (instruction >> 7) & 0x1F;       // 5 bits for rd (bits 11:7)
    JInstruction->func3 = (instruction >> 12) & 0x7;    // 3 bits for func3 (bits 14:12)
    JInstruction->rs1 = (instruction >> 15) & 0x1F;     // 5 bits for rs1 (bits 19:15)
    JInstruction->immediate = sign_extend_12((instruction >> 20) & 0xFFF);
        
    } else {

    JInstruction->rd = (instruction >> 7) & 0x1F;       // 5 bits for rd (bits 11:7)

    int lastbit = instruction       & 0x80000000;
    int first1_10bits = instruction & 0x7FE00000;
    int bit11 = instruction         & 0x00100000;
    int bit12_19 = instruction      & 0x000FF000;
    
    int32_t offset = (first1_10bits >> 20 ) |  // MSB (12th bit)
                     (bit11         >> 9  ) |  // 11th bit
                     (bit12_19      >> 1  ) |  //  >> 12   Bits [10:5]
                     (lastbit       >> 11 );   // Bit 4

    offset = (offset << 20) >> 20;

    

    JInstruction->immediate = offset;
    }
    






    
    return JInstruction;
}



void Jfunc3Decode(J_type* Jinstruct, CPURegisters* reg, unsigned int* PC){


    switch (Jinstruct->opcode)
    {
    case 111:
        jal(Jinstruct, reg, PC);
        break;
    case 103:
        jalr(Jinstruct, reg, PC);
        break;
    default:
        break;
    }



    free(Jinstruct);
    return;
}



void jal(J_type* Jinstruct, CPURegisters* reg, unsigned int* PC){

    reg->x[Jinstruct->rd] = *PC;
    *PC = *PC + Jinstruct->immediate - 4;
    
    return;
}

void jalr(J_type* Jinstruct, CPURegisters* reg, unsigned int* PC){

    // link register part
    reg->x[Jinstruct->rd] = *PC + 4;

    
    // target address is obtained by adding the sign-extended 12-bit I-immediate to the register rs1,
    // then setting the least-significant bit of the result to zero
    //jump part
    int32_t new_address = Jinstruct->immediate + reg->x[Jinstruct->rs1];
    new_address = new_address & 0xFFFFFFFE;

    *PC = new_address;
    
    return;
}