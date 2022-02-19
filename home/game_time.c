#include "../constants.h"
#include "game_time.h"

void ResetGameTime(void){
        XOR_A_A;
    LD_addr_A(wGameTimeCap);
    LD_addr_A(wGameTimeHours);
    LD_addr_A(wGameTimeHours + 1);
    LD_addr_A(wGameTimeMinutes);
    LD_addr_A(wGameTimeSeconds);
    LD_addr_A(wGameTimeFrames);
    RET;

}

void GameTimer(void){
        NOP;

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wGameTime));
    LDH_addr_A(rSVBK);

    CALL(aGameTimer_Function);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


Function:
    //  Increment the game timer by one frame.
//  The game timer is capped at 999:59:59.00.

//  Don't update if game logic is paused.
    LD_A_addr(wGameLogicPaused);
    AND_A_A;
    RET_NZ ;

//  Is the timer paused?
    LD_HL(wGameTimerPaused);
    BIT_hl(GAME_TIMER_PAUSED_F);
    RET_Z ;

//  Is the timer already capped?
    LD_HL(wGameTimeCap);
    BIT_hl(0);
    RET_NZ ;

//  +1 frame
    LD_HL(wGameTimeFrames);
    LD_A_hl;
    INC_A;

    CP_A(60);  // frames/second
    IF_NC goto second;

    LD_hl_A;
    RET;


second:
        XOR_A_A;
    LD_hl_A;

//  +1 second
    LD_HL(wGameTimeSeconds);
    LD_A_hl;
    INC_A;

    CP_A(60);  // seconds/minute
    IF_NC goto minute;

    LD_hl_A;
    RET;


minute:
        XOR_A_A;
    LD_hl_A;

//  +1 minute
    LD_HL(wGameTimeMinutes);
    LD_A_hl;
    INC_A;

    CP_A(60);  // minutes/hour
    IF_NC goto hour;

    LD_hl_A;
    RET;


hour:
        XOR_A_A;
    LD_hl_A;

//  +1 hour
    LD_A_addr(wGameTimeHours);
    LD_H_A;
    LD_A_addr(wGameTimeHours + 1);
    LD_L_A;
    INC_HL;

//  Cap the timer after 1000 hours.
    LD_A_H;
    CP_A(HIGH(1000));
    IF_C goto ok;

    LD_A_L;
    CP_A(LOW(1000));
    IF_C goto ok;

    LD_HL(wGameTimeCap);
    SET_hl(0);

    LD_A(59);  // 999:59:59.00
    LD_addr_A(wGameTimeMinutes);
    LD_addr_A(wGameTimeSeconds);
    RET;


ok:
        LD_A_H;
    LD_addr_A(wGameTimeHours);
    LD_A_L;
    LD_addr_A(wGameTimeHours + 1);
    RET;

}
