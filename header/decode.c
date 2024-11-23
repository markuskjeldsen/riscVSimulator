#include "decode.h"
#include <stdio.h>
#include <stdint.h>
#include <U-type.c>
#include <I-type.c>
#include <R-type.c>
#include <B-type.c>
#include <J-type.c>
#include <S-type.c>




int ecall(unsigned int instruction,CPURegisters* reg){
        int callCode = reg->x[17];

        switch (callCode)
        {
        case (10): // end program
            return 1;
            break;
        
        default:
            break;
        }



    return 0;
}



int execute(unsigned int *instruction, CPURegisters *registers, int *PC, uint8_t* sp) {
    int opcode = (instruction[*PC / 4] & 0b000000000000000000000000001111111);  // Corrected semicolon
    S_type* SInstruct;

    switch (opcode) {
        case 111: //JAL
        case 103: //JALR
            J_type* JInstruct = JtypeDecode(instruction[*PC/4], registers);
            Jfunc3Decode(JInstruct,registers,PC);
            break;
        case 99: //B-type
            B_type* BInstruct = BtypeDecode(instruction[*PC / 4], registers);
            Bfunc3Decode(BInstruct, registers, PC);
            break;
        case 55: // lui
            U_type* UInstruct = UtypeDecode(instruction[*PC / 4], registers);  // Corrected variable name
            lui(UInstruct, registers);
            break;
        case 51: // add register-register operations
            R_type* RInstruct = RtypeDecode(instruction[*PC/4], registers);
            Rfunc3Decode(RInstruct,registers);
            break;
        case 35: // sw  store and load functions
            SInstruct = StypeDecode(instruction[*PC/4], registers);
            Sfunc3Decode(SInstruct,registers,sp);
            break;
        case 19: // addi
            I_type* IInstruct = ItypeDecode(instruction[*PC / 4], registers);
            Ifunc3Decode(IInstruct,registers);
            break;
        case 3: // lW
            SInstruct = StypeDecode(instruction[*PC/4], registers);
            Sfunc3Decode(SInstruct,registers,sp);
            break;
        
        case 115: //ecall
            if(ecall(instruction[*PC/4], registers)){
                return 1;
            }


        default:
            break;
    }

    return 0;
}
