#include "../constants.h"
#include "math.h"

void SimpleMultiply(void){
    //  Return a * c.
    AND_A_A;
    RET_Z ;

    PUSH_BC;
    LD_B_A;
    XOR_A_A;

loop:
        ADD_A_C;
    DEC_B;
    IF_NZ goto loop;
    POP_BC;
    RET;

}

void SimpleDivide(void){
    //  Divide a by c. Return quotient b and remainder a.
    LD_B(0);

loop:
        INC_B;
    SUB_A_C;
    IF_NC goto loop;
    DEC_B;
    ADD_A_C;
    RET;

}

void Multiply(void){
    //  Multiply hMultiplicand (3 bytes) by hMultiplier. Result in hProduct.
//  All values are big endian.
    PUSH_HL;
    PUSH_BC;

    CALLFAR(av_Multiply);

    POP_BC;
    POP_HL;
    RET;

}

void Divide(void){
    //  Divide hDividend length b (max 4 bytes) by hDivisor. Result in hQuotient.
//  All values are big endian.
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    HOMECALL(av_Divide);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void SubtractAbsolute(void){
    //  //  unreferenced
//  Return |a - b|, sign in carry.
    SUB_A_B;
    RET_NC ;
    CPL;
    ADD_A(1);
    SCF;
    RET;

}
