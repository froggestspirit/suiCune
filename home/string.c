#include "../constants.h"
#include "string.h"

void InitString(void){
    //  Init a string of length c.
    PUSH_HL;
    JR(mv_InitString);

}

void InitName(void){
    //  Intended for names, so this function is limited to ten characters.
    PUSH_HL;
    LD_C(NAME_LENGTH - 1);
    return v_InitString();
}

void v_InitString(void){
    //  if the string pointed to by hl is empty (defined as "zero or more spaces
//  followed by a null"), then initialize it to the string pointed to by de.
    PUSH_BC;

loop:
        LD_A_hli;
    CP_A(0x50);
    IF_Z goto blank;
    CP_A(0x7f);
    IF_NZ goto notblank;
    DEC_C;
    IF_NZ goto loop;

blank:
        POP_BC;
    LD_L_E;
    LD_H_D;
    POP_DE;
    LD_B(0);
    INC_C;
    CALL(aCopyBytes);
    RET;


notblank:
        POP_BC;
    POP_HL;
    RET;

}
