#include "S-type.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <registers.h>


int32_t stackpointer(int32_t address, int32_t offset ,  uint8_t* sp){
    int32_t nstackpointer = 0x00100000 - (address + offset);
    return nstackpointer;
    
}




S_type* StypeDecode(unsigned int instruction, CPURegisters* reg) {
    // Dynamically allocate memory for the struct
    S_type* SInstruction = malloc(sizeof(S_type));
    if (SInstruction == NULL) {
        // Handle allocation failure
        return NULL;
    }
    
    
    // Extract the fields correctly using bitwise operations
    SInstruction->opcode = instruction & 0x7F;          // 7 bits for opcode (bits 6:0)
    SInstruction->func3 = (instruction >> 12) & 0x7;       // 3 bits for rd (bits 11:7)


    if (SInstruction->opcode == 3)
    {
        // Extract the fields correctly using bitwise operations
        SInstruction->rd = (instruction >> 7) & 0x1F;       // 5 bits for rd (bits 11:7)
        SInstruction->rs1 = (instruction >> 15) & 0x1F;     // 5 bits for rs1 (bits 19:15)
        SInstruction->immediate = sign_extend_12((instruction >> 20) & 0xFFF);
         
    } else {
    
    SInstruction->rs1 = (instruction & 0x01F00000) >> 20;
    SInstruction->rs2 = (instruction & 0x000F8000) >> 15;


    int first5 = (instruction >> 7) & 0x1F; // Extract first 5 bits
    int last7 = (instruction & 0xFE000000) >> 25; // Extract last 7 bits (shifted down)

    // Combine the fields
    int combined = (first5 | (last7 << 5)); // Merge into a 12-bit immediate

    // Check the sign bit (most significant bit of the immediate field)
    if (combined & (1 << 11)) { // Check the 12th bit (sign bit)
    combined |= 0xFFFFF000; // Sign-extend by setting the upper 20 bits
    }

    //int first5 = (instruction >> 7) & 0x0000001F;
    //int last7 =   instruction       & 0xFE000000;


    SInstruction->immediate = combined;
    }
    



    return SInstruction;
}



void Sfunc3Decode(S_type* Sinstruct, CPURegisters* reg, uint8_t* sp){

    switch (Sinstruct->opcode)
    {
    case 35:
        sw(Sinstruct,reg, sp);
        break;
    case 3:
        lw(Sinstruct,reg, sp);
        break;
    default:
        break;
    }





    free(Sinstruct);
    return;
}


void sw(S_type* Sinstruct, CPURegisters* reg, uint8_t* sp){
    uint8_t first4       = (reg->x[Sinstruct->rs1] & 0xFF000000) >> 24;
    uint8_t uppermiddle4 = (reg->x[Sinstruct->rs1] & 0x00FF0000) >> 16;
    uint8_t lowermiddle4 = (reg->x[Sinstruct->rs1] & 0x0000FF00) >> 8;
    uint8_t last4        = (reg->x[Sinstruct->rs1] & 0x000000FF) >> 0;
    
    int address = reg->x[Sinstruct->rs2];
    int offset = Sinstruct->immediate;

    sp[ 
    stackpointer(address,offset,sp) + 0] = first4;
    sp[ 
    stackpointer(address,offset,sp) + 1] = uppermiddle4;
    sp[ 
    stackpointer(address,offset,sp) + 2] = lowermiddle4;
    sp[ 
    stackpointer(address,offset,sp) + 3] = last4;
    

    return;
}

void lw(S_type* Sinstruct, CPURegisters* reg, uint8_t* sp){

    int address = reg->x[Sinstruct->rs1];
    int offset = Sinstruct->immediate;


    int first4       = sp[stackpointer(address,offset,sp) + 0];
    int uppermiddle4 = sp[stackpointer(address,offset,sp) + 1];
    int lowermiddle4 = sp[stackpointer(address,offset,sp) + 2];
    int last4        = sp[stackpointer(address,offset,sp) + 3];
    
    
    reg->x[Sinstruct->rd] = 
          first4 << 24 | 
    uppermiddle4 << 16 |
    lowermiddle4 << 8  |
           last4 << 0;


    return;
}