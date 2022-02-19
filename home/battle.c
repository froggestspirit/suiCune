#include "../constants.h"
#include "battle.h"

void GetPartyParamLocation(void){
    //  Get the location of parameter a from wCurPartyMon in hl
    PUSH_BC;
    LD_HL(wPartyMons);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wCurPartyMon);
    CALL(aGetPartyLocation);
    POP_BC;
    RET;

}

void GetPartyLocation(void){
    //  Add the length of a PartyMon struct to hl a times.
    LD_BC(PARTYMON_STRUCT_LENGTH);
    JP(mAddNTimes);

}

void GetDexNumber(void){
    //  //  unreferenced
//  Probably used in gen 1 to convert index number to dex number
//  Not required in gen 2 because index number == dex number
    PUSH_HL;
    LD_A_B;
    DEC_A;
    LD_B(0);
    ADD_HL_BC;
    LD_HL(mBaseData + BASE_DEX_NO);
    LD_BC(BASE_DATA_SIZE);
    CALL(aAddNTimes);
    LD_A(BANK(aBaseData));
    CALL(aGetFarWord);
    LD_B_L;
    LD_C_H;
    POP_HL;
    RET;

}

void UserPartyAttr(void){
        PUSH_AF;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto ot;
    POP_AF;
    JR(mBattlePartyAttr);

ot:
        POP_AF;
    JR(mOTPartyAttr);

}

void OpponentPartyAttr(void){
        PUSH_AF;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ot;
    POP_AF;
    JR(mBattlePartyAttr);

ot:
        POP_AF;
    JR(mOTPartyAttr);

}

void BattlePartyAttr(void){
    //  Get attribute a from the party struct of the active battle mon.
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(wPartyMons);
    ADD_HL_BC;
    LD_A_addr(wCurBattleMon);
    CALL(aGetPartyLocation);
    POP_BC;
    RET;

}

void OTPartyAttr(void){
    //  Get attribute a from the party struct of the active enemy mon.
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartyMon1Species);
    ADD_HL_BC;
    LD_A_addr(wCurOTMon);
    CALL(aGetPartyLocation);
    POP_BC;
    RET;

}

void ResetDamage(void){
        XOR_A_A;
    LD_addr_A(wCurDamage);
    LD_addr_A(wCurDamage + 1);
    RET;

}

void SetPlayerTurn(void){
        XOR_A_A;
    LDH_addr_A(hBattleTurn);
    RET;

}

void SetEnemyTurn(void){
        LD_A(1);
    LDH_addr_A(hBattleTurn);
    RET;

}

void UpdateOpponentInParty(void){
        LDH_A_addr(hBattleTurn);
    AND_A_A;
    JR_Z (mUpdateEnemyMonInParty);
    JR(mUpdateBattleMonInParty);

}

void UpdateUserInParty(void){
        LDH_A_addr(hBattleTurn);
    AND_A_A;
    JR_Z (mUpdateBattleMonInParty);
    JR(mUpdateEnemyMonInParty);

}

void UpdateBattleMonInParty(void){
    //  Update level, status, current HP

    LD_A_addr(wCurBattleMon);

    return UpdateBattleMon();
}

void UpdateBattleMon(void){
        LD_HL(wPartyMon1Level);
    CALL(aGetPartyLocation);

    LD_D_H;
    LD_E_L;
    LD_HL(wBattleMonLevel);
    LD_BC(wBattleMonMaxHP - wBattleMonLevel);
    JP(mCopyBytes);

}

void UpdateEnemyMonInParty(void){
    //  Update level, status, current HP

//  No wildmons.
    LD_A_addr(wBattleMode);
    DEC_A;
    RET_Z ;

    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1Level);
    CALL(aGetPartyLocation);

    LD_D_H;
    LD_E_L;
    LD_HL(wEnemyMonLevel);
    LD_BC(wEnemyMonMaxHP - wEnemyMonLevel);
    JP(mCopyBytes);

}

void RefreshBattleHuds(void){
        CALL(aUpdateBattleHuds);
    LD_C(3);
    CALL(aDelayFrames);
    JP(mWaitBGMap);

}

void UpdateBattleHuds(void){
        FARCALL(aUpdatePlayerHUD);
    FARCALL(aUpdateEnemyHUD);
    RET;

// INCLUDE "home/battle_vars.asm"

    return FarCopyRadioText();
}

void FarCopyRadioText(void){
        INC_HL;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
    LD_A_E;
    LD_L_A;
    LD_A_D;
    LD_H_A;
    LD_DE(wRadioText);
    LD_BC(2 * SCREEN_WIDTH);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
    RET;

}

void MobileTextBorder(void){
    // For mobile link battles only.
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    RET_C ;

// Draw a cell phone icon at the
// top right corner of the border.
    hlcoord(19, 12, wTilemap);
    LD_hl(0x5e);  // top
    hlcoord(19, 13, wTilemap);
    LD_hl(0x5f);  // bottom
    RET;

}

void BattleTextbox(void){
    //  Open a textbox and print text at hl.
    PUSH_HL;
    CALL(aSpeechTextbox);
    CALL(aMobileTextBorder);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    POP_HL;
    CALL(aPrintTextboxText);
    RET;

}

void StdBattleTextbox(void){
    //  Open a textbox and print battle text at 20:hl.

    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A(BANK(aBattleText));
    RST(aBankswitch);

    CALL(aBattleTextbox);

    POP_AF;
    RST(aBankswitch);
    RET;

}

void GetBattleAnimPointer(void){
        LD_A(BANK(aBattleAnimations));
    RST(aBankswitch);

    LD_A_hli;
    LD_addr_A(wBattleAnimAddress);
    LD_A_hl;
    LD_addr_A(wBattleAnimAddress + 1);

// ClearBattleAnims is the only function that calls this...
    LD_A(BANK(aClearBattleAnims));
    RST(aBankswitch);

    RET;

}

void GetBattleAnimByte(void){
        PUSH_HL;
    PUSH_DE;

    LD_HL(wBattleAnimAddress);
    LD_E_hl;
    INC_HL;
    LD_D_hl;

    LD_A(BANK(aBattleAnimations));
    RST(aBankswitch);

    LD_A_de;
    LD_addr_A(wBattleAnimByte);
    INC_DE;

    LD_A(BANK(aBattleAnimCommands));
    RST(aBankswitch);

    LD_hl_D;
    DEC_HL;
    LD_hl_E;

    POP_DE;
    POP_HL;

    LD_A_addr(wBattleAnimByte);
    RET;

}

void PushLYOverrides(void){
        LDH_A_addr(hLCDCPointer);
    AND_A_A;
    RET_Z ;

    LD_A(LOW(wLYOverridesBackup));
    LD_addr_A(wRequested2bppSource);
    LD_A(HIGH(wLYOverridesBackup));
    LD_addr_A(wRequested2bppSource + 1);

    LD_A(LOW(wLYOverrides));
    LD_addr_A(wRequested2bppDest);
    LD_A(HIGH(wLYOverrides));
    LD_addr_A(wRequested2bppDest + 1);

    LD_A((wLYOverridesEnd - wLYOverrides) / LEN_2BPP_TILE);
    LD_addr_A(wRequested2bppSize);
    RET;

}
