#include "../constants.h"
#include "item.h"

void DoItemEffect(void){
        FARCALL(av_DoItemEffect);
    RET;

}

void CheckTossableItem(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    FARCALL(av_CheckTossableItem);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void TossItem(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_TossItem));
    RST(aBankswitch);

    CALL(av_TossItem);

    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void ReceiveItem(void){
        PUSH_BC;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_ReceiveItem));
    RST(aBankswitch);
    PUSH_HL;
    PUSH_DE;

    CALL(av_ReceiveItem);

    POP_DE;
    POP_HL;
    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    POP_BC;
    RET;

}

void CheckItem(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_CheckItem));
    RST(aBankswitch);

    CALL(av_CheckItem);

    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}
