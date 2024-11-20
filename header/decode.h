#ifndef DECODE_H
#define DECODE_H

#include <registers.h>
#include "U-type.h"  // Correctly include the U-type header

int execute(unsigned int *instruction, CPURegisters *registers, int *PC);

#endif  // DECODE_H
