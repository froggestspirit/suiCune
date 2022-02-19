#include "../constants.h"
#include "palettes.h"

//  Functions dealing with palettes.

void UpdatePalsIfCGB(void){
    //  update bgp data from wBGPals2
//  update obp data from wOBPals2
//  return carry if successful

//  check cgb
    LDH_A_addr(hCGB);
    AND_A_A;
    RET_Z ;

    return UpdateCGBPals();
}

void UpdateCGBPals(void){
    //  return carry if successful
//  any pals to update?
    LDH_A_addr(hCGBPalUpdate);
    AND_A_A;
    RET_Z ;
// fallthrough

    return ForceUpdateCGBPals();
}

void ForceUpdateCGBPals(void){
        LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wBGPals2));
    LDH_addr_A(rSVBK);

    LD_HL(wBGPals2);

//  copy 8 pals to bgpd
    LD_A(1 << rBGPI_AUTO_INCREMENT);
    LDH_addr_A(rBGPI);
    LD_C(LOW(rBGPD));
    LD_B(8 / 2);

bgp:
        for(int rept = 0; rept < (1 * PALETTE_SIZE) * 2; rept++){
    LD_A_hli;
    LDH_c_A;
    }

    DEC_B;
    IF_NZ goto bgp;

//  hl is now wOBPals2

//  copy 8 pals to obpd
    LD_A(1 << rOBPI_AUTO_INCREMENT);
    LDH_addr_A(rOBPI);
    LD_C(LOW(rOBPD));
    LD_B(8 / 2);

obp:
        for(int rept = 0; rept < (1 * PALETTE_SIZE) * 2; rept++){
    LD_A_hli;
    LDH_c_A;
    }

    DEC_B;
    IF_NZ goto obp;

    POP_AF;
    LDH_addr_A(rSVBK);

//  clear pal update queue
    XOR_A_A;
    LDH_addr_A(hCGBPalUpdate);

    SCF;
    RET;

}

void DmgToCgbBGPals(void){
    //  exists to forego reinserting cgb-converted image data

//  input: a -> bgp

    LDH_addr_A(rBGP);
    PUSH_AF;

//  Don't need to be here if DMG
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto end;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    LDH_A_addr(rSVBK);
    PUSH_AF;

    LD_A(BANK(wBGPals2));
    LDH_addr_A(rSVBK);

//  copy & reorder bg pal buffer
    LD_HL(wBGPals2);  // to
    LD_DE(wBGPals1);  // from
//  order
    LDH_A_addr(rBGP);
    LD_B_A;
//  all pals
    LD_C(8);
    CALL(aCopyPals);
//  request pal update
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);

    POP_AF;
    LDH_addr_A(rSVBK);

    POP_BC;
    POP_DE;
    POP_HL;

end:
        POP_AF;
    RET;

}

void DmgToCgbObjPals(void){
    //  exists to forego reinserting cgb-converted image data

//  input: d -> obp1
//         e -> obp2

    LD_A_E;
    LDH_addr_A(rOBP0);
    LD_A_D;
    LDH_addr_A(rOBP1);

    LDH_A_addr(hCGB);
    AND_A_A;
    RET_Z ;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    LDH_A_addr(rSVBK);
    PUSH_AF;

    LD_A(BANK(wOBPals2));
    LDH_addr_A(rSVBK);

//  copy & reorder obj pal buffer
    LD_HL(wOBPals2);  // to
    LD_DE(wOBPals1);  // from
//  order
    LDH_A_addr(rOBP0);
    LD_B_A;
//  all pals
    LD_C(8);
    CALL(aCopyPals);
//  request pal update
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);

    POP_AF;
    LDH_addr_A(rSVBK);

    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void DmgToCgbObjPal0(void){
        LDH_addr_A(rOBP0);
    PUSH_AF;

//  Don't need to be here if not CGB
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto dmg;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wOBPals2));
    LDH_addr_A(rSVBK);

    LD_HL(wOBPals2 + PALETTE_SIZE * 0);
    LD_DE(wOBPals1 + PALETTE_SIZE * 0);
    LDH_A_addr(rOBP0);
    LD_B_A;
    LD_C(1);
    CALL(aCopyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);

    POP_AF;
    LDH_addr_A(rSVBK);

    POP_BC;
    POP_DE;
    POP_HL;


dmg:
        POP_AF;
    RET;

}

void DmgToCgbObjPal1(void){
        LDH_addr_A(rOBP1);
    PUSH_AF;

    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto dmg;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wOBPals2));
    LDH_addr_A(rSVBK);

    LD_HL(wOBPals2 + PALETTE_SIZE * 1);
    LD_DE(wOBPals1 + PALETTE_SIZE * 1);
    LDH_A_addr(rOBP1);
    LD_B_A;
    LD_C(1);
    CALL(aCopyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);

    POP_AF;
    LDH_addr_A(rSVBK);

    POP_BC;
    POP_DE;
    POP_HL;


dmg:
        POP_AF;
    RET;

}

void CopyPals(void){
    //  copy c palettes in order b from de to hl

    PUSH_BC;
    LD_C(NUM_PAL_COLORS);

loop:
        PUSH_DE;
    PUSH_HL;

//  get pal color
    LD_A_B;
    maskbits(1 << PAL_COLOR_SIZE, 0);
//  2 bytes per color
    ADD_A_A;
    LD_L_A;
    LD_H(0);
    ADD_HL_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;

//  dest
    POP_HL;
//  write color
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    INC_HL;
//  next pal color
    for(int rept = 0; rept < PAL_COLOR_SIZE; rept++){
    SRL_B;
    }
//  source
    POP_DE;
//  done pal?
    DEC_C;
    IF_NZ goto loop;

//  de += 8 (next pal)
    LD_A(PALETTE_SIZE);
    ADD_A_E;
    IF_NC goto ok;
    INC_D;

ok:
        LD_E_A;

//  how many more pals?
    POP_BC;
    DEC_C;
    JR_NZ (mCopyPals);
    RET;

}

void ClearVBank1(void){
        LDH_A_addr(hCGB);
    AND_A_A;
    RET_Z ;

    LD_A(1);
    LDH_addr_A(rVBK);

    LD_HL(VRAM_Begin);
    LD_BC(VRAM_End - VRAM_Begin);
    XOR_A_A;
    CALL(aByteFill);

    LD_A(0);
    LDH_addr_A(rVBK);
    RET;

}

void GSReloadPalettes(void){
    //  //  dummied out
    RET;

}

void ReloadSpritesNoPalettes(void){
        LDH_A_addr(hCGB);
    AND_A_A;
    RET_Z ;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wBGPals2));
    LDH_addr_A(rSVBK);
    LD_HL(wBGPals2);
    LD_BC((8 * PALETTE_SIZE) + (2 * PALETTE_SIZE));
    XOR_A_A;
    CALL(aByteFill);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    CALL(aDelayFrame);
    RET;

}

void SwapTextboxPalettes(void){
        HOMECALL(av_SwapTextboxPalettes);
    RET;

}

void ScrollBGMapPalettes(void){
        HOMECALL(av_ScrollBGMapPalettes);
    RET;

}
