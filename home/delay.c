#include "../constants.h"
#include "delay.h"

void DelayFrame(void){
    //  Wait for one frame
    LD_A(1);
    LD_addr_A(wVBlankOccurred);

//  Wait for the next VBlank, halting to conserve battery

halt:
        //halt ['']  // rgbasm adds a nop after this instruction by default
    LD_A_addr(wVBlankOccurred);
    AND_A_A;
    IF_NZ goto halt;
    RET;

}

void DelayFrames(void){
    //  Wait c frames
    CALL(aDelayFrame);
    DEC_C;
    JR_NZ (mDelayFrames);
    RET;

}
