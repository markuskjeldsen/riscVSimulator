#ifndef J_TYPE_H
#define J_TYPE_H

#include <stdint.h>
#include "registers.h"  // Assuming you need this for the CPURegisters type

typedef struct {
    uint32_t opcode;
    int32_t rd;
    int32_t immediate;
    int32_t rs1; 
    int32_t func3; 
} J_type;


J_type* JtypeDecode(unsigned int, CPURegisters*);


void Jfunc3Decode(J_type* , CPURegisters*, unsigned int* PC);



#endif  // J_TYPE_H
