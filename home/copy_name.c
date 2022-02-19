#include "../constants.h"
#include "copy_name.h"

void CopyName1(void){
    //  Copies the name from de to wStringBuffer2
    LD_HL(wStringBuffer2);

    return CopyName2();
}

void CopyName2(void){
    //  Copies the name from de to hl

loop:
        LD_A_de;
    INC_DE;
    LD_hli_A;
    CP_A(0x50);
    IF_NZ goto loop;
    RET;

}
