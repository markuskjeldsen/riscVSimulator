#ifndef DECODE_H
#define DECODE_H

#include <registers.h>
#include "U-type.h"  // Correctly include the U-type header

int execute(unsigned int *instruction, CPURegisters *registers, int *PC, uint8_t* sp);

#endif  // DECODE_H
