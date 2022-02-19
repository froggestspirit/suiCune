#include "../constants.h"
#include "sprite_anims.h"

void InitSpriteAnimStruct(void){
        LD_addr_A(wSpriteAnimID);
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A(BANK(av_InitSpriteAnimStruct));
    RST(aBankswitch);
    LD_A_addr(wSpriteAnimID);

    CALL(av_InitSpriteAnimStruct);

    POP_AF;
    RST(aBankswitch);

    RET;

}

void ReinitSpriteAnimFrame(void){
        LD_addr_A(wSpriteAnimID);
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A(BANK(av_ReinitSpriteAnimFrame));
    RST(aBankswitch);
    LD_A_addr(wSpriteAnimID);

    CALL(av_ReinitSpriteAnimFrame);

    POP_AF;
    RST(aBankswitch);

    RET;

}
