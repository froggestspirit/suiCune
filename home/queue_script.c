#include "../constants.h"
#include "queue_script.h"

void QueueScript(void){
    //  Push pointer hl in the current bank to wQueuedScriptBank.
    LDH_A_addr(hROMBank);

    return FarQueueScript();
}

void FarQueueScript(void){
    //  Push pointer a:hl to wQueuedScriptBank.
    LD_addr_A(wQueuedScriptBank);
    LD_A_L;
    LD_addr_A(wQueuedScriptAddr);
    LD_A_H;
    LD_addr_A(wQueuedScriptAddr + 1);
    RET;

}
