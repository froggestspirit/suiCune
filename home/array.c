#include "../constants.h"
#include "array.h"

void IsInArray(void){
    //  Find value a for every de bytes in array hl.
//  Return index in b and carry if found.

    LD_B(0);
    LD_C_A;

loop:
        LD_A_hl;
    CP_A(-1);
    IF_Z goto NotInArray;
    CP_A_C;
    IF_Z goto InArray;
    INC_B;
    ADD_HL_DE;
    goto loop;


NotInArray:
        AND_A_A;
    RET;


InArray:
        SCF;
    RET;

}

void SkipNames(void){
    //  Skip a names.
    LD_BC(NAME_LENGTH);
    AND_A_A;
    RET_Z ;

loop:
        ADD_HL_BC;
    DEC_A;
    IF_NZ goto loop;
    RET;

}

void AddNTimes(void){
    //  Add bc * a to hl.
    AND_A_A;
    RET_Z ;

loop:
        ADD_HL_BC;
    DEC_A;
    IF_NZ goto loop;
    RET;

}
