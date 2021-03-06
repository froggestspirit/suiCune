#include "../constants.h"
#include "movement.h"

void InitMovementBuffer(void){
        LD_addr_A(wMovementBufferObject);
    XOR_A_A;
    LD_addr_A(wMovementBufferCount);
    LD_A(0x0);  // was BANK(wMovementBuffer) in G/S
    LD_addr_A(wUnusedMovementBufferBank);
    LD_A(LOW(wMovementBuffer));
    LD_addr_A(wUnusedMovementBufferPointer);
    LD_A(HIGH(wMovementBuffer));
    LD_addr_A(wUnusedMovementBufferPointer + 1);
    RET;

}

void DecrementMovementBufferCount(void){
        LD_A_addr(wMovementBufferCount);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wMovementBufferCount);
    RET;

}

void AppendToMovementBuffer(void){
        PUSH_HL;
    PUSH_DE;
    LD_HL(wMovementBufferCount);
    LD_E_hl;
    INC_hl;
    LD_D(0);
    LD_HL(wMovementBuffer);
    ADD_HL_DE;
    LD_hl_A;
    POP_DE;
    POP_HL;
    RET;

}

void AppendToMovementBufferNTimes(void){
        PUSH_AF;
    LD_A_C;
    AND_A_A;
    IF_NZ goto okay;
    POP_AF;
    RET;


okay:
        POP_AF;

loop:
        CALL(aAppendToMovementBuffer);
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void ComputePathToWalkToPlayer(void){
        PUSH_AF;
//  compare x coords, load left/right into h, and x distance into d
    LD_A_B;
    SUB_A_D;
    LD_H(LEFT);
    IF_NC goto got_x_distance;
    DEC_A;
    CPL;
    LD_H(RIGHT);


got_x_distance:
        LD_D_A;
//  compare y coords, load up/down into l, and y distance into e
    LD_A_C;
    SUB_A_E;
    LD_L(UP);
    IF_NC goto got_y_distance;
    DEC_A;
    CPL;
    LD_L(DOWN);


got_y_distance:
        LD_E_A;
//  if the x distance is less than the y distance, swap h and l, and swap d and e
    CP_A_D;
    IF_NC goto done;
    LD_A_H;
    LD_H_L;
    LD_L_A;
    LD_A_D;
    LD_D_E;
    LD_E_A;


done:
        POP_AF;
    LD_B_A;
//  Add movement in the longer direction first...
    LD_A_H;
    CALL(aComputePathToWalkToPlayer_GetMovementData);
    LD_C_D;
    CALL(aAppendToMovementBufferNTimes);
//  ... then add the shorter direction.
    LD_A_L;
    CALL(aComputePathToWalkToPlayer_GetMovementData);
    LD_C_E;
    CALL(aAppendToMovementBufferNTimes);
    RET;


GetMovementData:
        PUSH_DE;
    PUSH_HL;
    LD_L_B;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_DE(mComputePathToWalkToPlayer_MovementData);
    ADD_HL_DE;
    LD_A_hl;
    POP_HL;
    POP_DE;
    RET;

/* Currently not used?
MovementData:
        //slow_step ['DOWN']
    //slow_step ['UP']
    //slow_step ['LEFT']
    //slow_step ['RIGHT']
    //step ['DOWN']
    //step ['UP']
    //step ['LEFT']
    //step ['RIGHT']
    //big_step ['DOWN']
    //big_step ['UP']
    //big_step ['LEFT']
    //big_step ['RIGHT']
*/
}
