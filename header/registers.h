#ifndef REGISTER_H
#define REGISTER_H

// Define CPURegisters as a named struct type
typedef struct CPURegisters {
    int32_t x[32];
} CPURegisters;

// Function declaration
CPURegisters* init_registers();

#endif // REGISTER_H
