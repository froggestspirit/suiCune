#include "../constants.h"
#include "scrolling_menu.h"

void ScrollingMenu(void){
        CALL(aCopyMenuData);
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A(BANK(av_ScrollingMenu));  // aka BANK(_InitScrollingMenu)
    RST(aBankswitch);

    CALL(av_InitScrollingMenu);
    CALL(aScrollingMenu_UpdatePalettes);
    CALL(av_ScrollingMenu);

    POP_AF;
    RST(aBankswitch);

    LD_A_addr(wMenuJoypad);
    RET;


UpdatePalettes:
        LD_HL(wVramState);
    BIT_hl(0);
    JP_NZ (mUpdateTimePals);
    JP(mSetPalettes);

}

void InitScrollingMenu(void){
        LD_A_addr(wMenuBorderTopCoord);
    DEC_A;
    LD_B_A;
    LD_A_addr(wMenuBorderBottomCoord);
    SUB_A_B;
    LD_D_A;
    LD_A_addr(wMenuBorderLeftCoord);
    DEC_A;
    LD_C_A;
    LD_A_addr(wMenuBorderRightCoord);
    SUB_A_C;
    LD_E_A;
    PUSH_DE;
    CALL(aCoord2Tile);
    POP_BC;
    JP(mTextbox);

}

void JoyTextDelay_ForcehJoyDown(void){
        CALL(aDelayFrame);

    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    CALL(aJoyTextDelay);
    POP_AF;
    LDH_addr_A(hInMenu);

    LDH_A_addr(hJoyLast);
    AND_A(D_RIGHT + D_LEFT + D_UP + D_DOWN);
    LD_C_A;
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON + B_BUTTON + SELECT + START);
    OR_A_C;
    LD_C_A;
    RET;

}
