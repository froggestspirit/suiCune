#include "../constants.h"
#include "stone_queue.h"

void HandleStoneQueue(void){
        LDH_A_addr(hROMBank);
    PUSH_AF;

    CALL(aSwitchToMapScriptsBank);
    CALL(aHandleStoneQueue_WarpAction);

    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    RET;


WarpAction:
        LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_DE;
    LD_A_hl;
    CP_A(0xff);
    IF_Z goto nope;

    LD_L_A;
    PUSH_HL;
    CALL(aHandleStoneQueue_IsObjectOnWarp);
    POP_HL;
    IF_NC goto nope;
    LD_D_A;
    LD_E_L;
    CALL(aHandleStoneQueue_IsObjectInStoneTable);
    IF_NC goto nope;
    CALL(aCallMapScript);
    FARCALL(aEnableScriptMode);
    SCF;
    RET;


nope:
        AND_A_A;
    RET;


IsObjectOnWarp:
        PUSH_DE;

    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_DE;
    LD_E_hl;

    SUB_A(4);
    LD_D_A;
    LD_A_E;
    SUB_A(4);
    LD_E_A;
    CALL(aHandleStoneQueue_check_on_warp);

    POP_DE;
    RET;


check_on_warp:
        LD_HL(wCurMapWarpsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wCurMapWarpCount);
    AND_A_A;
    IF_Z goto nope2;


loop:
        PUSH_AF;
    LD_A_hl;
    CP_A_E;
    IF_NZ goto not_on_warp;
    INC_HL;
    LD_A_hld;
    CP_A_D;
    IF_NZ goto not_on_warp;
    goto found_warp;


not_on_warp:
        LD_A(WARP_EVENT_SIZE);
    ADD_A_L;
    LD_L_A;
    IF_NC goto no_carry;
    INC_H;

no_carry:
    
    POP_AF;
    DEC_A;
    IF_NZ goto loop;


nope2:
        AND_A_A;
    RET;


found_warp:
        POP_AF;
    LD_D_A;
    LD_A_addr(wCurMapWarpCount);
    SUB_A_D;
    INC_A;
    SCF;
    RET;


IsObjectInStoneTable:
        INC_E;
    LD_HL(CMDQUEUE_ADDR);
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

loop2:
        LD_A_hli;
    CP_A(0xff);
    IF_Z goto nope3;
    CP_A_D;
    IF_NZ goto next_inc3;
    LD_A_hli;
    CP_A_E;
    IF_NZ goto next_inc2;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    goto yes;


next_inc3:
        INC_HL;


next_inc2:
        INC_HL;
    INC_HL;
    goto loop2;


nope3:
        AND_A_A;
    RET;


yes:
        SCF;
    RET;

}
