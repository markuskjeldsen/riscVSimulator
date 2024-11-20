#ifndef I_TYPE_H
#define I_TYPE_H

#include <stdint.h>
#include <registers.h>  // Assuming you need this for the CPURegisters type

typedef struct {
    uint32_t opcode;
    int32_t immediate;
    uint32_t rd;
    uint32_t rs1;
    uint32_t func3;
    uint32_t shamt;
    uint32_t shtyp;
} I_type;



int32_t sign_extend_12(int32_t);
I_type* ItypeDecode(unsigned int, CPURegisters*);


void Ifunc3Decode(I_type* , CPURegisters* );
void addi(I_type*, CPURegisters*);
void andi(I_type* , CPURegisters* );
void ori(I_type* , CPURegisters* );
void xori(I_type* , CPURegisters* );
void sltiu(I_type* ,CPURegisters* );
void slti(I_type* ,CPURegisters* );




#endif  // I_TYPE_H
