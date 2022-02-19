#include "../constants.h"
#include "printer.h"

void PrinterReceive(void){
        HOMECALL(av_PrinterReceive);
    RET;

}

void AskSerial(void){
    //  send out a handshake while serial int is off
    LD_A_addr(wPrinterConnectionOpen);
    BIT_A(0);
    RET_Z ;

//  if we're still interpreting data, don't try to receive
    LD_A_addr(wPrinterOpcode);
    AND_A_A;
    RET_NZ ;

//  once every 6 frames
    LD_HL(wHandshakeFrameDelay);
    INC_hl;
    LD_A_hl;
    CP_A(6);
    RET_C ;

    XOR_A_A;
    LD_hl_A;

    LD_A(0x0c);
    LD_addr_A(wPrinterOpcode);

//  handshake
    LD_A(0x88);
    LDH_addr_A(rSB);

//  switch to internal clock
    LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);

//  start transfer
    LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);

    RET;

}
