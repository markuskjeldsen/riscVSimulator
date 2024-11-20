#ifndef B_TYPE_H
#define B_TYPE_H

#include <stdint.h>
#include <registers.h>  // Assuming you need this for the CPURegisters type

typedef struct {
    uint32_t opcode;
    uint32_t func3;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t offset;
} B_type;

B_type* BtypeDecode(unsigned int, CPURegisters*);
void Bfunc3Decode(B_type* , CPURegisters* ,unsigned int* );




#endif  // B_TYPE_H
