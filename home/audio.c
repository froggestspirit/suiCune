#include "../constants.h"
#include "audio.h"

//  Audio interfaces.

void InitSound(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_InitSound));
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    CALL(av_InitSound);

    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void UpdateSound(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_UpdateSound));
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    CALL(av_UpdateSound);

    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void v_LoadMusicByte(void){
    //  [wCurMusicByte] = [a:de]
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    LD_A_de;
    LD_addr_A(wCurMusicByte);
    LD_A(BANK(aLoadMusicByte));

    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
    RET;

}

void PlayMusic(void){
    //  Play music de.

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_PlayMusic));  // aka BANK(_InitSound)
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    LD_A_E;
    AND_A_A;
    IF_Z goto nomusic;

    CALL(av_PlayMusic);
    goto end;


nomusic:
        CALL(av_InitSound);


end:
        POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void PlayMusic2(void){
    //  Stop playing music, then play music de.

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_PlayMusic));
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    PUSH_DE;
    LD_DE(MUSIC_NONE);
    CALL(av_PlayMusic);
    CALL(aDelayFrame);
    POP_DE;
    CALL(av_PlayMusic);

    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void PlayCry(void){
    //  Play cry de.

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    LDH_A_addr(hROMBank);
    PUSH_AF;

// Cries are stuck in one bank.
    LD_A(BANK(aPokemonCries));
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    LD_HL(mPokemonCries);
    for(int rept = 0; rept < MON_CRY_LENGTH; rept++){
    ADD_HL_DE;
    }

    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_HL;

    LD_A_hli;
    LD_addr_A(wCryPitch);
    LD_A_hli;
    LD_addr_A(wCryPitch + 1);
    LD_A_hli;
    LD_addr_A(wCryLength);
    LD_A_hl;
    LD_addr_A(wCryLength + 1);

    LD_A(BANK(av_PlayCry));
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    CALL(av_PlayCry);

    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void PlaySFX(void){
    //  Play sound effect de.
//  Sound effects are ordered by priority (highest to lowest)

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

// Is something already playing?
    CALL(aCheckSFX);
    IF_NC goto play;

// Does it have priority?
    LD_A_addr(wCurSFX);
    CP_A_E;
    IF_C goto done;


play:
        LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_PlaySFX));
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    LD_A_E;
    LD_addr_A(wCurSFX);
    CALL(av_PlaySFX);

    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);


done:
        POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void WaitPlaySFX(void){
        CALL(aWaitSFX);
    CALL(aPlaySFX);
    RET;

}

void WaitSFX(void){
    //  infinite loop until sfx is done playing

    PUSH_HL;


wait:
        LD_HL(wChannel5Flags1);
    BIT_hl(0);
    IF_NZ goto wait;
    LD_HL(wChannel6Flags1);
    BIT_hl(0);
    IF_NZ goto wait;
    LD_HL(wChannel7Flags1);
    BIT_hl(0);
    IF_NZ goto wait;
    LD_HL(wChannel8Flags1);
    BIT_hl(0);
    IF_NZ goto wait;

    POP_HL;
    RET;

}

void IsSFXPlaying(void){
    //  Return carry if no sound effect is playing.
//  The inverse of CheckSFX.
    PUSH_HL;

    LD_HL(wChannel5Flags1);
    BIT_hl(0);
    IF_NZ goto playing;
    LD_HL(wChannel6Flags1);
    BIT_hl(0);
    IF_NZ goto playing;
    LD_HL(wChannel7Flags1);
    BIT_hl(0);
    IF_NZ goto playing;
    LD_HL(wChannel8Flags1);
    BIT_hl(0);
    IF_NZ goto playing;

    POP_HL;
    SCF;
    RET;


playing:
        POP_HL;
    AND_A_A;
    RET;

}

void MaxVolume(void){
        LD_A(MAX_VOLUME);
    LD_addr_A(wVolume);
    RET;

}

void LowVolume(void){
        LD_A(0x33);  // 50%
    LD_addr_A(wVolume);
    RET;

}

void MinVolume(void){
        XOR_A_A;
    LD_addr_A(wVolume);
    RET;

}

void FadeOutToMusic(void){
    //  //  unreferenced
    LD_A(4);
    LD_addr_A(wMusicFade);
    RET;

}

void FadeInToMusic(void){
        LD_A(4 | (1 << MUSIC_FADE_IN_F));
    LD_addr_A(wMusicFade);
    RET;

}

void SkipMusic(void){
    //  Skip a frames of music.

loop:
        AND_A_A;
    RET_Z ;
    DEC_A;
    CALL(aUpdateSound);
    goto loop;

    return FadeToMapMusic();
}

void FadeToMapMusic(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    CALL(aGetMapMusic_MaybeSpecial);
    LD_A_addr(wMapMusic);
    CP_A_E;
    IF_Z goto done;

    LD_A(8);
    LD_addr_A(wMusicFade);
    LD_A_E;
    LD_addr_A(wMusicFadeID);
    LD_A_D;
    LD_addr_A(wMusicFadeID + 1);
    LD_A_E;
    LD_addr_A(wMapMusic);


done:
        POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void PlayMapMusic(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    CALL(aGetMapMusic_MaybeSpecial);
    LD_A_addr(wMapMusic);
    CP_A_E;
    IF_Z goto done;

    PUSH_DE;
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    CALL(aDelayFrame);
    POP_DE;
    LD_A_E;
    LD_addr_A(wMapMusic);
    CALL(aPlayMusic);


done:
        POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void PlayMapMusicBike(void){
    //  If the player's on a bike, play the bike music instead of the map music
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    XOR_A_A;
    LD_addr_A(wDontPlayMapMusicOnReload);
    LD_DE(MUSIC_BICYCLE);
    LD_A_addr(wPlayerState);
    CP_A(PLAYER_BIKE);
    IF_Z goto play;
    CALL(aGetMapMusic_MaybeSpecial);

play:
        PUSH_DE;
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    CALL(aDelayFrame);
    POP_DE;

    LD_A_E;
    LD_addr_A(wMapMusic);
    CALL(aPlayMusic);

    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void TryRestartMapMusic(void){
        LD_A_addr(wDontPlayMapMusicOnReload);
    AND_A_A;
    JR_Z (mRestartMapMusic);
    XOR_A_A;
    LD_addr_A(wMapMusic);
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    CALL(aDelayFrame);
    XOR_A_A;
    LD_addr_A(wDontPlayMapMusicOnReload);
    RET;

}

void RestartMapMusic(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    CALL(aDelayFrame);
    LD_A_addr(wMapMusic);
    LD_E_A;
    LD_D(0);
    CALL(aPlayMusic);
    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void SpecialMapMusic(void){
        LD_A_addr(wPlayerState);
    CP_A(PLAYER_SURF);
    IF_Z goto surf;
    CP_A(PLAYER_SURF_PIKA);
    IF_Z goto surf;

    LD_A_addr(wStatusFlags2);
    BIT_A(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
    IF_NZ goto contest;


no:
        AND_A_A;
    RET;


bike:
// 
    SET_PC(aSpecialMapMusic_bike);  //  unreferenced
    LD_DE(MUSIC_BICYCLE);
    SCF;
    RET;


surf:
        LD_DE(MUSIC_SURF);
    SCF;
    RET;


contest:
        LD_A_addr(wMapGroup);
    CP_A(GROUP_ROUTE_35_NATIONAL_PARK_GATE);
    IF_NZ goto no;
    LD_A_addr(wMapNumber);
    CP_A(MAP_ROUTE_35_NATIONAL_PARK_GATE);
    IF_Z goto ranking;
    CP_A(MAP_ROUTE_36_NATIONAL_PARK_GATE);
    IF_NZ goto no;


ranking:
        LD_DE(MUSIC_BUG_CATCHING_CONTEST_RANKING);
    SCF;
    RET;

}

void GetMapMusic_MaybeSpecial(void){
        CALL(aSpecialMapMusic);
    RET_C ;
    CALL(aGetMapMusic);
    RET;

}

void PlaceBCDNumberSprite(void){
    //  //  unreferenced
//  Places a BCD number at the upper center of the screen.
    LD_A(4 * TILE_WIDTH);
    LD_addr_A(wVirtualOAMSprite38YCoord);
    LD_addr_A(wVirtualOAMSprite39YCoord);
    LD_A(10 * TILE_WIDTH);
    LD_addr_A(wVirtualOAMSprite38XCoord);
    LD_A(11 * TILE_WIDTH);
    LD_addr_A(wVirtualOAMSprite39XCoord);
    XOR_A_A;
    LD_addr_A(wVirtualOAMSprite38Attributes);
    LD_addr_A(wVirtualOAMSprite39Attributes);
    LD_A_addr(wUnusedBCDNumber);
    CP_A(100);
    IF_NC goto max;
    ADD_A(1);
    DAA;
    LD_B_A;
    SWAP_A;
    AND_A(0xf);
    ADD_A(0xf6);
    LD_addr_A(wVirtualOAMSprite38TileID);
    LD_A_B;
    AND_A(0xf);
    ADD_A(0xf6);
    LD_addr_A(wVirtualOAMSprite39TileID);
    RET;


max:
        LD_A(0xff);
    LD_addr_A(wVirtualOAMSprite38TileID);
    LD_addr_A(wVirtualOAMSprite39TileID);
    RET;

}

void CheckSFX(void){
    //  Return carry if any SFX channels are active.
    LD_A_addr(wChannel5Flags1);
    BIT_A(0);
    IF_NZ goto playing;
    LD_A_addr(wChannel6Flags1);
    BIT_A(0);
    IF_NZ goto playing;
    LD_A_addr(wChannel7Flags1);
    BIT_A(0);
    IF_NZ goto playing;
    LD_A_addr(wChannel8Flags1);
    BIT_A(0);
    IF_NZ goto playing;
    AND_A_A;
    RET;

playing:
        SCF;
    RET;

}

void TerminateExpBarSound(void){
        XOR_A_A;
    LD_addr_A(wChannel5Flags1);
    LD_addr_A(wPitchSweep);
    LDH_addr_A(rNR10);
    LDH_addr_A(rNR11);
    LDH_addr_A(rNR12);
    LDH_addr_A(rNR13);
    LDH_addr_A(rNR14);
    RET;

}

void ChannelsOff(void){
    //  Quickly turn off music channels
    XOR_A_A;
    LD_addr_A(wChannel1Flags1);
    LD_addr_A(wChannel2Flags1);
    LD_addr_A(wChannel3Flags1);
    LD_addr_A(wChannel4Flags1);
    LD_addr_A(wPitchSweep);
    RET;

}

void SFXChannelsOff(void){
    //  Quickly turn off sound effect channels
    XOR_A_A;
    LD_addr_A(wChannel5Flags1);
    LD_addr_A(wChannel6Flags1);
    LD_addr_A(wChannel7Flags1);
    LD_addr_A(wChannel8Flags1);
    LD_addr_A(wPitchSweep);
    RET;

}
