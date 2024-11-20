#ifndef R_TYPE_H
#define R_TYPE_H

#include <stdint.h>
#include <registers.h>  // Assuming you need this for the CPURegisters type

typedef struct {
    uint32_t opcode;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t func3;
    uint32_t func7;
} R_type;

R_type* RtypeDecode(unsigned int, CPURegisters*);
void Rfunc3Decode(R_type* , CPURegisters* );
void Rfunc7Decode(R_type* , CPURegisters* );


void add(R_type*, CPURegisters*);
void sub(R_type*, CPURegisters*);
void xor(R_type*, CPURegisters*);
void and(R_type*, CPURegisters*);
void or (R_type*, CPURegisters*);
void sltu(R_type* Rinstruct,CPURegisters* reg);
void slt (R_type* Rinstruct,CPURegisters* reg);


#endif  // R_TYPE_H
