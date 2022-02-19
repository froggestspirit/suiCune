#include "../constants.h"
#include "print_text.h"

void PrintLetterDelay(void) {
        //  Wait before printing the next letter.

    //  The text speed setting in wOptions is actually a frame count:
    //      fast: 1 frame
    //      mid:  3 frames
    //      slow: 5 frames

    //  wTextboxFlags[!0] and A or B override text speed with a one-frame delay.
    //  wOptions[4] and wTextboxFlags[!1] disable the delay.

    LD_A_addr(wOptions);
    BIT_A(NO_TEXT_SCROLL);
    RET_NZ;

    //  non-scrolling text?
    LD_A_addr(wTextboxFlags);
    BIT_A(NO_TEXT_DELAY_F);
    RET_Z;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    LD_HL(hOAMUpdate);
    LD_A_hl;
    PUSH_AF;

    //  orginally turned oam update off...
    //     ld a, 1
    LD_hl_A;

    //  force fast scroll?
    LD_A_addr(wTextboxFlags);
    BIT_A(FAST_TEXT_DELAY_F);
    IF_Z goto fast;

    //  text speed
    LD_A_addr(wOptions);
    AND_A(0b111);
    goto updatedelay;

fast:
        LD_A(TEXT_DELAY_FAST);

updatedelay:
        LD_addr_A(wTextDelayFrames);

checkjoypad:
        CALL(aGetJoypad);

    //  input override
    LD_A_addr(wDisableTextAcceleration);
    AND_A_A;
    IF_NZ goto wait;

    //  Wait one frame if holding A or B.
    LDH_A_addr(hJoyDown);
    BIT_A(A_BUTTON_F);
    IF_Z goto checkb;
    goto delay;

checkb:
        BIT_A(B_BUTTON_F);
    IF_Z goto wait;

delay:
        CALL(aDelayFrame);
    goto end;

wait:
        LD_A_addr(wTextDelayFrames);
    AND_A_A;
    // IF_NZ goto checkjoypad;

end:
        POP_AF;
    LDH_addr_A(hOAMUpdate);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;
}

void CopyDataUntil(void) {
        //  Copy [hl .. bc) to de.

    //  In other words, the source data is
    //  from hl up to but not including bc,
    //  and the destination is de.

    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_H;
    CP_A_B;
    JR_NZ(mCopyDataUntil);
    LD_A_L;
    CP_A_C;
    JR_NZ(mCopyDataUntil);
    RET;
}

void PrintNum(void) {
        HOMECALL(av_PrintNum);
    RET;
}

void MobilePrintNum(void) {
        HOMECALL(av_MobilePrintNum);
    RET;
}

void FarPrintText(void) {
        LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

    CALL(aPrintText);

    POP_AF;
    RST(aBankswitch);
    RET;
}

void CallPointerAt(void) {
        LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_hli;
    RST(aBankswitch);

    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    CALL(av_hl_);

    POP_HL;
    LD_A_H;
    RST(aBankswitch);
    RET;
}
