#ifndef S_TYPE_H
#define S_TYPE_H

#include <stdint.h>
#include "registers.h"  


typedef struct {
    uint32_t opcode;
    int32_t func3;
    int32_t rs1;
    int32_t rs2;
    int32_t immediate;
    int32_t rd;
} S_type;


S_type* StypeDecode(unsigned int, CPURegisters*);


void Sfunc3Decode(S_type* , CPURegisters*, uint8_t*  );



#endif  // S_TYPE_H
