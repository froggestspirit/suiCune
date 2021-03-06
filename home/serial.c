#include "../constants.h"
#include "serial.h"

void Serial(void){
    //  The serial interrupt.

    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;

    LDH_A_addr(hMobileReceive);
    AND_A_A;
    IF_NZ goto mobile;

    LD_A_addr(wPrinterConnectionOpen);
    BIT_A(0);
    IF_NZ goto printer;

    LDH_A_addr(hSerialConnectionStatus);
    INC_A;  // is it equal to CONNECTION_NOT_ESTABLISHED?
    IF_Z goto establish_connection;

    LDH_A_addr(rSB);
    LDH_addr_A(hSerialReceive);

    LDH_A_addr(hSerialSend);
    LDH_addr_A(rSB);

    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_Z goto player2;

    LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    goto player2;


mobile:
        CALL(aMobileReceive);
    goto end;


printer:
        CALL(aPrinterReceive);
    goto end;


establish_connection:
        LDH_A_addr(rSB);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto player1;
    CP_A(USING_INTERNAL_CLOCK);
    IF_NZ goto player2;


player1:
        LDH_addr_A(hSerialReceive);
    LDH_addr_A(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_Z goto _player2;

    XOR_A_A;
    LDH_addr_A(rSB);

    LD_A(3);
    LDH_addr_A(rDIV);

delay_loop:
        LDH_A_addr(rDIV);
    BIT_A(7);
    IF_NZ goto delay_loop;

    LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    goto player2;


_player2:
        XOR_A_A;
    LDH_addr_A(rSB);


player2:
        LD_A(TRUE);
    LDH_addr_A(hSerialReceivedNewData);
    LD_A(SERIAL_NO_DATA_BYTE);
    LDH_addr_A(hSerialSend);


end:
        POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    RET;

}

void Serial_ExchangeBytes(void){
    //  send bc bytes from hl, receive bc bytes to de
    LD_A(TRUE);
    LDH_addr_A(hSerialIgnoringInitialData);


loop:
        LD_A_hl;
    LDH_addr_A(hSerialSend);
    CALL(aSerial_ExchangeByte);
    PUSH_BC;
    LD_B_A;
    INC_HL;

    LD_A(48);

wait:
        DEC_A;
    IF_NZ goto wait;

    LDH_A_addr(hSerialIgnoringInitialData);
    AND_A_A;
    LD_A_B;
    POP_BC;
    IF_Z goto load;
    DEC_HL;
    CP_A(SERIAL_PREAMBLE_BYTE);
    IF_NZ goto loop;
    XOR_A_A;
    LDH_addr_A(hSerialIgnoringInitialData);
    goto loop;


load:
        LD_de_A;
    INC_DE;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;

}

void Serial_ExchangeByte(void){
    
timeout_loop:
        XOR_A_A;
    LDH_addr_A(hSerialReceivedNewData);
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_NZ goto not_player_2;
    LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);

not_player_2:
    
loop:
        LDH_A_addr(hSerialReceivedNewData);
    AND_A_A;
    IF_NZ goto await_new_data;
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_NZ goto not_player_1_or_timed_out;
    CALL(aCheckLinkTimeoutFramesNonzero);
    IF_Z goto not_player_1_or_timed_out;
    CALL(aSerial_ExchangeByte_ShortDelay);
    PUSH_HL;
    LD_HL(wLinkTimeoutFrames + 1);
    INC_hl;
    IF_NZ goto no_rollover_up;
    DEC_HL;
    INC_hl;


no_rollover_up:
        POP_HL;
    CALL(aCheckLinkTimeoutFramesNonzero);
    IF_NZ goto loop;
    JP(mSerialDisconnected);


not_player_1_or_timed_out:
        LDH_A_addr(rIE);
    AND_A((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
    CP_A(1 << SERIAL);
    IF_NZ goto loop;
    LD_A_addr(wLinkByteTimeout);
    DEC_A;
    LD_addr_A(wLinkByteTimeout);
    IF_NZ goto loop;
    LD_A_addr(wLinkByteTimeout + 1);
    DEC_A;
    LD_addr_A(wLinkByteTimeout + 1);
    IF_NZ goto loop;
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto await_new_data;

    LD_A(255);

long_delay_loop:
        DEC_A;
    IF_NZ goto long_delay_loop;


await_new_data:
        XOR_A_A;
    LDH_addr_A(hSerialReceivedNewData);
    LDH_A_addr(rIE);
    AND_A((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
    SUB_A(1 << SERIAL);
    IF_NZ goto non_serial_interrupts_enabled;

// a == 0
    //assert ['LOW(SERIAL_LINK_BYTE_TIMEOUT) == 0'];
    LD_addr_A(wLinkByteTimeout);
    LD_A(HIGH(SERIAL_LINK_BYTE_TIMEOUT));
    LD_addr_A(wLinkByteTimeout + 1);


non_serial_interrupts_enabled:
        LDH_A_addr(hSerialReceive);
    CP_A(SERIAL_NO_DATA_BYTE);
    RET_NZ ;
    CALL(aCheckLinkTimeoutFramesNonzero);
    IF_Z goto timed_out;
    PUSH_HL;
    LD_HL(wLinkTimeoutFrames + 1);
    LD_A_hl;
    DEC_A;
    LD_hld_A;
    INC_A;
    IF_NZ goto no_rollover;
    DEC_hl;


no_rollover:
        POP_HL;
    CALL(aCheckLinkTimeoutFramesNonzero);
    JR_Z (mSerialDisconnected);


timed_out:
        LDH_A_addr(rIE);
    AND_A((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
    CP_A(1 << SERIAL);
    LD_A(SERIAL_NO_DATA_BYTE);
    RET_Z ;
    LD_A_hl;
    LDH_addr_A(hSerialSend);
    CALL(aDelayFrame);
    JP(mSerial_ExchangeByte_timeout_loop);


ShortDelay:
        LD_A(15);

short_delay_loop:
        DEC_A;
    IF_NZ goto short_delay_loop;
    RET;

}

void CheckLinkTimeoutFramesNonzero(void){
        PUSH_HL;
    LD_HL(wLinkTimeoutFrames);
    LD_A_hli;
    OR_A_hl;
    POP_HL;
    RET;

//  This sets wLinkTimeoutFrames to $ffff, since
//  a is always 0 when it is called.
    return SerialDisconnected();
}

void SerialDisconnected(void){
        DEC_A;
    LD_addr_A(wLinkTimeoutFrames);
    LD_addr_A(wLinkTimeoutFrames + 1);
    RET;

//  This is used to check that both players entered the same Cable Club room.
    return Serial_ExchangeSyncBytes();
}

void Serial_ExchangeSyncBytes(void){
        LD_HL(wLinkPlayerSyncBuffer);
    LD_DE(wLinkReceivedSyncBuffer);
    LD_C(2);
    LD_A(TRUE);
    LDH_addr_A(hSerialIgnoringInitialData);

exchange:
        CALL(aDelayFrame);
    LD_A_hl;
    LDH_addr_A(hSerialSend);
    CALL(aSerial_ExchangeByte);
    LD_B_A;
    INC_HL;
    LDH_A_addr(hSerialIgnoringInitialData);
    AND_A_A;
    LD_A(FALSE);
    LDH_addr_A(hSerialIgnoringInitialData);
    IF_NZ goto exchange;
    LD_A_B;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto exchange;
    RET;

}

void Serial_PrintWaitingTextAndSyncAndExchangeNybble(void){
        CALL(aLoadTilemapToTempTilemap);
    CALLFAR(aPlaceWaitingText);
    CALL(aWaitLinkTransfer);
    JP(mSafeLoadTempTilemapToTilemap);

}

void Serial_SyncAndExchangeNybble(void){
    //  //  unreferenced
    CALL(aLoadTilemapToTempTilemap);
    CALLFAR(aPlaceWaitingText);
    JP(mWaitLinkTransfer);  // pointless

}

void WaitLinkTransfer(void){
        LD_A(0xff);
    LD_addr_A(wOtherPlayerLinkAction);

loop:
        CALL(aLinkTransfer);
    CALL(aDelayFrame);
    CALL(aCheckLinkTimeoutFramesNonzero);
    IF_Z goto check;
    PUSH_HL;
    LD_HL(wLinkTimeoutFrames + 1);
    DEC_hl;
    IF_NZ goto skip;
    DEC_HL;
    DEC_hl;
    IF_NZ goto skip;
// We might be disconnected
    POP_HL;
    XOR_A_A;
    JP(mSerialDisconnected);


skip:
        POP_HL;


check:
        LD_A_addr(wOtherPlayerLinkAction);
    INC_A;
    IF_Z goto loop;

    LD_B(10);

receive:
        CALL(aDelayFrame);
    CALL(aLinkTransfer);
    DEC_B;
    IF_NZ goto receive;

    LD_B(10);

acknowledge:
        CALL(aDelayFrame);
    CALL(aLinkDataReceived);
    DEC_B;
    IF_NZ goto acknowledge;

    LD_A_addr(wOtherPlayerLinkAction);
    LD_addr_A(wOtherPlayerLinkMode);
    RET;

}

void LinkTransfer(void){
        PUSH_BC;
    LD_B(SERIAL_TIMECAPSULE);
    LD_A_addr(wLinkMode);
    CP_A(LINK_TIMECAPSULE);
    IF_Z goto got_high_nybble;
    LD_B(SERIAL_TIMECAPSULE);
    IF_C goto got_high_nybble;
    CP_A(LINK_TRADECENTER);
    LD_B(SERIAL_TRADECENTER);
    IF_Z goto got_high_nybble;
    LD_B(SERIAL_BATTLE);


got_high_nybble:
        CALL(aLinkTransfer_Receive);
    LD_A_addr(wPlayerLinkAction);
    ADD_A_B;
    LDH_addr_A(hSerialSend);
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_NZ goto player_1;
    LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);


player_1:
        CALL(aLinkTransfer_Receive);
    POP_BC;
    RET;


Receive:
        LDH_A_addr(hSerialReceive);
    LD_addr_A(wOtherPlayerLinkMode);
    AND_A(0xf0);
    CP_A_B;
    RET_NZ ;
    XOR_A_A;
    LDH_addr_A(hSerialReceive);
    LD_A_addr(wOtherPlayerLinkMode);
    AND_A(0xf);
    LD_addr_A(wOtherPlayerLinkAction);
    RET;

}

void LinkDataReceived(void){
    //  Let the other system know that the data has been received.
    XOR_A_A;
    LDH_addr_A(hSerialSend);
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    RET_NZ ;
    LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    RET;

}

void SetBitsForTimeCapsuleRequestIfNotLinked(void){
    //  //  unreferenced
//  Similar to SetBitsForTimeCapsuleRequest (see engine/link/link.asm).
    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;
    LD_A(USING_INTERNAL_CLOCK);
    LDH_addr_A(rSB);
    XOR_A_A;
    LDH_addr_A(hSerialReceive);
    LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    RET;

}
