#ifndef U_TYPE_H
#define U_TYPE_H

#include <stdint.h>
#include <registers.h>  

typedef struct {
    uint32_t opcode;
    int32_t immediate;
    uint32_t rd;
} U_type;

U_type* UtypeDecode(unsigned int, CPURegisters*);
void lui(U_type*, CPURegisters*);

#endif  // U_TYPE_H
