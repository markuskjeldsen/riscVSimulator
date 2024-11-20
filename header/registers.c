#include <stdlib.h>
#include "registers.h"  // Include the correct header file

// Function definition
CPURegisters* init_registers() {
    // Allocate memory for the struct
    CPURegisters* reg = (CPURegisters*)malloc(sizeof(CPURegisters));
    if (reg == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Initialize all registers to 0
    for (int i = 0; i < 32; i++) {
        reg->x[i] = 0;
    }

    return reg; // Return the pointer to the allocated struct
}
