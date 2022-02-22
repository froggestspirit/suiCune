#include "../constants.h"
#include "text.h"

void ClearBox(void) {
    //  Fill a c*b box at hl with blank tiles.
    LD_A(0x7f);
    // fallthrough

    return FillBoxWithByte();
}

void FillBoxWithByte(void) {
row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;
}

void ClearTilemap(void) {
    //  Fill wTilemap with blank tiles.

    hlcoord(0, 0, wTilemap);
    LD_A(0x7f);
    LD_BC(wTilemapEnd - wTilemap);
    CALL(aByteFill);

    // Update the BG Map.
    LDH_A_addr(rLCDC);
    BIT_A(rLCDC_ENABLE);
    RET_Z;
    JP(mWaitBGMap);
}

void ClearScreen(void) {
    LD_A(PAL_BG_TEXT);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    JR(mClearTilemap);
}

void Textbox(void) {
    //  Draw a text box at hl with room for b lines of c characters each.
    //  Places a border around the textbox, then switches the palette to the
    //  text black-and-white scheme.
    PUSH_BC;
    PUSH_HL;
    CALL(aTextboxBorder);
    POP_HL;
    POP_BC;
    JR(mTextboxPalette);
}

void TextboxBorder(void) {
    // Top
    PUSH_HL;
    LD_A(0x79);
    LD_hli_A;
    INC_A;  // "─"
    CALL(aTextboxBorder_PlaceChars);
    INC_A;  // "┐"
    LD_hl_A;
    POP_HL;

    // Middle
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;

row:
    PUSH_HL;
    LD_A(0x7c);
    LD_hli_A;
    LD_A(0x7f);
    CALL(aTextboxBorder_PlaceChars);
    LD_hl(0x7c);
    POP_HL;

    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto row;

    // Bottom
    LD_A(0x7d);
    LD_hli_A;
    LD_A(0x7a);
    CALL(aTextboxBorder_PlaceChars);
    LD_hl(0x7e);

    RET;

PlaceChars:
    //  Place char a c times.
    LD_D_C;

loop:
    LD_hli_A;
    DEC_D;
    IF_NZ goto loop;
    RET;
}

void TextboxPalette(void) {
    //  Fill text box width c height b at hl with pal 7
    LD_DE(wAttrmap - wTilemap);
    ADD_HL_DE;
    INC_B;
    INC_B;
    INC_C;
    INC_C;
    LD_A(PAL_BG_TEXT);

col:
    PUSH_BC;
    PUSH_HL;

row:
    LD_hli_A;
    DEC_C;
    IF_NZ goto row;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto col;
    RET;
}

void SpeechTextbox(void) {
    //  Standard textbox.
    hlcoord(TEXTBOX_X, TEXTBOX_Y, wTilemap);
    LD_B(TEXTBOX_INNERH);
    LD_C(TEXTBOX_INNERW);
    JP(mTextbox);
}

void GameFreakText(void) {
    //  //  unreferenced
    // text ['"ゲームフりーク！"']  // "GAMEFREAK!"
    // done ['?']

    return RadioTerminator();
}

void RadioTerminator(void) {
    LD_HL(mRadioTerminator_stop);
    RET;

stop:
    // text_end ['?']

    return PrintText();
}

void PrintText(void) {
    CALL(aSetUpTextbox);
    // fallthrough

    return BuenaPrintText();
}

void BuenaPrintText(void) {
    PUSH_HL;
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    CALL(aClearBox);
    POP_HL;
    // fallthrough

    return PrintTextboxText();
}

void PrintTextboxText(void) {
    bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    CALL(aPlaceHLTextAtBC);
    RET;
}

void SetUpTextbox(void) {
    PUSH_HL;
    CALL(aSpeechTextbox);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    POP_HL;
    RET;
}

void PlaceString(void) {
    PUSH_HL;
    // fallthrough

    return PlaceNextChar();
}

void PlaceNextChar(void) {
    LD_A_de;
    CP_A(0x50);
    JR_NZ(mCheckDict);
    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;
}

void DummyChar(void) {
    //  //  unreferenced
    POP_DE;
    // fallthrough

    return NextChar();
}

void NextChar(void) {
    INC_DE;
    JP(mPlaceNextChar);
}

void CheckDict(void) {
    // dict: MACRO
    // assert CHARLEN(\1) == 1
    // if \1 == 0
    //     and a
    // else
    //     cp \1
    // endc
    // if ISCONST(\2)
    //     ; Replace a character with another one
    //     jr nz, .not\@
    //     ld a, \2
    // .not\@:
    // elif STRSUB("\2", 1, 1) == "."
    //     ; Locals can use a short jump
    //     jr z, \2
    // else
    //     jp z, \2
    // endc
    // ENDM

    // dict ['"<MOBILE>"', 'MobileScriptChar']
    // dict ['"<LINE>"', 'LineChar']
    // dict ['"<NEXT>"', 'NextLineChar']
    // dict ['"<CR>"', 'CarriageReturnChar']
    // dict ['"<NULL>"', 'NullChar']
    // dict ['"<SCROLL>"', '_ContTextNoPause']
    // dict ['"<_CONT>"', '_ContText']
    // dict ['"<PARA>"', 'Paragraph']
    // dict ['"<MOM>"', 'PrintMomsName']
    // dict ['"<PLAYER>"', 'PrintPlayerName']
    // dict ['"<RIVAL>"', 'PrintRivalName']
    // dict ['"<ROUTE>"', 'PlaceJPRoute']
    // dict ['"<WATASHI>"', 'PlaceWatashi']
    // dict ['"<KOKO_WA>"', 'PlaceKokoWa']
    // dict ['"<RED>"', 'PrintRedsName']
    // dict ['"<GREEN>"', 'PrintGreensName']
    // dict ['"#"', 'PlacePOKe']
    // dict ['"<PC>"', 'PCChar']
    // dict ['"<ROCKET>"', 'RocketChar']
    // dict ['"<TM>"', 'TMChar']
    // dict ['"<TRAINER>"', 'TrainerChar']
    // dict ['"<KOUGEKI>"', 'PlaceKougeki']
    // dict ['"<LF>"', 'LineFeedChar']
    // dict ['"<CONT>"', 'ContText']
    // dict ['"<……>"', 'SixDotsChar']
    // dict ['"<DONE>"', 'DoneText']
    // dict ['"<PROMPT>"', 'PromptText']
    // dict ['"<PKMN>"', 'PlacePKMN']
    // dict ['"<POKE>"', 'PlacePOKE']
    // dict ['"0b"', 'NextChar']
    // dict ['"¯"', '" "']
    // dict ['"<DEXEND>"', 'PlaceDexEnd']
    // dict ['"<TARGET>"', 'PlaceMoveTargetsName']
    // dict ['"<USER>"', 'PlaceMoveUsersName']
    // dict ['"<ENEMY>"', 'PlaceEnemysName']
    // dict ['"<PLAY_G>"', 'PlaceGenderedPlayerName']
    // dict ['"ﾟ"', '.place']  // should be .diacritic
    // dict ['"ﾞ"', '.place']  // should be .diacritic
    goto not_diacritic;

diacritic:
    //
    SET_PC(aCheckDict_diacritic);  //  unreferenced
    LD_B_A;
    CALL(aDiacritic);
    JP(mNextChar);

not_diacritic:
    CP_A(FIRST_REGULAR_TEXT_CHAR);
    IF_NC goto place;
    //  dakuten or handakuten
    CP_A(0x40);
    IF_NC goto handakuten;
    //  dakuten
    CP_A(FIRST_HIRAGANA_DAKUTEN_CHAR);
    IF_NC goto hiragana_dakuten;
    //  katakana dakuten
    ADD_A(0x85 - 0x05);
    goto place_dakuten;

hiragana_dakuten:
    ADD_A(0xb6 - 0x26);

place_dakuten:
    LD_B(0xe5);  // dakuten
    CALL(aDiacritic);
    goto place;

handakuten:
    CP_A(0x44);
    IF_NC goto hiragana_handakuten;
    //  katakana handakuten
    ADD_A(0x99 - 0x40);
    goto place_handakuten;

hiragana_handakuten:
    ADD_A(0xca - 0x44);

place_handakuten:
    LD_B(0xe4);  // handakuten
    CALL(aDiacritic);

place:
    LD_hli_A;
    CALL(aPrintLetterDelay);
    JP(mNextChar);
}

void MobileScriptChar(void) {
    LD_C_L;
    LD_B_H;
    FARCALL(aRunMobileScript);
    JP(mPlaceNextChar);

    // print_name: MACRO
    //     push de
    //     ld de, \1
    //     jp PlaceCommandCharacter
    // ENDM
}

void PrintMomsName(void) {
    //  print_name wMomsName
    return PrintPlayerName();
}

void PrintPlayerName(void) {
    // print_name wPlayerName
    return PrintRivalName();
}

void PrintRivalName(void) {
    // print_name wRivalName
    return PrintRedsName();
}

void PrintRedsName(void) {
    //  print_name wRedsName
    return PrintGreensName();
}

void PrintGreensName(void) {
    // print_name wGreensName

    return TrainerChar();
}

void TrainerChar(void) {
    // print_name TrainerCharText
    return TMChar();
}

void TMChar(void) {
    //      print_name TMCharText
    return PCChar();
}

void PCChar(void) {
    //      print_name PCCharText
    return RocketChar();
}

void RocketChar(void) {
    //  print_name RocketCharText
    return PlacePOKe();
}

void PlacePOKe(void) {
    //   print_name PlacePOKeText
    return PlaceKougeki();
}

void PlaceKougeki(void) {
    // print_name KougekiText
    return SixDotsChar();
}

void SixDotsChar(void) {
    // print_name SixDotsCharText
    return PlacePKMN();
}

void PlacePKMN(void) {
    //   print_name PlacePKMNText
    return PlacePOKE();
}

void PlacePOKE(void) {
    //   print_name PlacePOKEText
    return PlaceJPRoute();
}

void PlaceJPRoute(void) {
    // print_name PlaceJPRouteText
    return PlaceWatashi();
}

void PlaceWatashi(void) {
    // print_name PlaceWatashiText
    return PlaceKokoWa();
}

void PlaceKokoWa(void) {
    // print_name PlaceKokoWaText

    return PlaceMoveTargetsName();
}

void PlaceMoveTargetsName(void) {
    LDH_A_addr(hBattleTurn);
    XOR_A(1);
    JR(mPlaceBattlersName);
}

void PlaceMoveUsersName(void) {
    LDH_A_addr(hBattleTurn);
    // fallthrough

    return PlaceBattlersName();
}

void PlaceBattlersName(void) {
    PUSH_DE;
    AND_A_A;
    IF_NZ goto enemy;

    LD_DE(wBattleMonNickname);
    JR(mPlaceCommandCharacter);

enemy:
    LD_DE(mEnemyText);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(wEnemyMonNickname);
    JR(mPlaceCommandCharacter);
}

void PlaceEnemysName(void) {
    PUSH_DE;

    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto linkbattle;

    LD_A_addr(wTrainerClass);
    CP_A(RIVAL1);
    IF_Z goto rival;
    CP_A(RIVAL2);
    IF_Z goto rival;

    LD_DE(wOTClassName);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mString_Space);
    CALL(aPlaceString);
    PUSH_BC;
    CALLFAR(aBattle_GetTrainerName);
    POP_HL;
    LD_DE(wStringBuffer1);
    JR(mPlaceCommandCharacter);

rival:
    LD_DE(wRivalName);
    JR(mPlaceCommandCharacter);

linkbattle:
    LD_DE(wOTClassName);
    JR(mPlaceCommandCharacter);
}

void PlaceGenderedPlayerName(void) {
    PUSH_DE;
    LD_DE(wPlayerName);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    LD_DE(mKunSuffixText);
    JR_Z(mPlaceCommandCharacter);
    LD_DE(mChanSuffixText);
    JR(mPlaceCommandCharacter);
}

void PlaceCommandCharacter(void) {
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    POP_DE;
    JP(mNextChar);
}

void TMCharText(void) {
    //     db "TM@"
    return TrainerCharText();
}

void TrainerCharText(void) {
    // db "TRAINER@"
    return PCCharText();
}

void PCCharText(void) {
    //     db "PC@"
    return RocketCharText();
}

void RocketCharText(void) {
    // db "ROCKET@"
    return PlacePOKeText();
}

void PlacePOKeText(void) {
    //  db "POKé@"
    return KougekiText();
}

void KougekiText(void) {
    //    db "こうげき@"
    return SixDotsCharText();
}

void SixDotsCharText(void) {
    // db "……@"
    return EnemyText();
}

void EnemyText(void) {
    //      db "Enemy @"
    return PlacePKMNText();
}

void PlacePKMNText(void) {
    //  db "<PK><MN>@"
    return PlacePOKEText();
}

void PlacePOKEText(void) {
    //  db "<PO><KE>@"
    return String_Space();
}

void String_Space(void) {
    //   db " @"
    //  These strings have been dummied out.
    return PlaceJPRouteText();
}

void PlaceJPRouteText(void) {
    return PlaceWatashiText();
}

void PlaceWatashiText(void) {
    return PlaceKokoWaText();
}

void PlaceKokoWaText(void) {
    // db "@"
    return KunSuffixText();
}

void KunSuffixText(void) {
    //  db "@"
    return ChanSuffixText();
}

void ChanSuffixText(void) {
    // db "@"

    return NextLineChar();
}

void NextLineChar(void) {
    POP_HL;
    LD_BC(SCREEN_WIDTH * 2);
    ADD_HL_BC;
    PUSH_HL;
    JP(mNextChar);
}

void LineFeedChar(void) {
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    PUSH_HL;
    JP(mNextChar);
}

void CarriageReturnChar(void) {
    POP_HL;
    PUSH_DE;
    LD_BC(-wTilemap + 0x10000);
    ADD_HL_BC;
    LD_DE(-SCREEN_WIDTH);
    LD_C(1);

loop:
    LD_A_H;
    AND_A_A;
    IF_NZ goto next;
    LD_A_L;
    CP_A(SCREEN_WIDTH);
    IF_C goto done;

next:
    ADD_HL_DE;
    INC_C;
    goto loop;

done:
    hlcoord(0, 0, wTilemap);
    LD_DE(SCREEN_WIDTH);
    LD_A_C;

loop2:
    AND_A_A;
    IF_Z goto done2;
    ADD_HL_DE;
    DEC_A;
    goto loop2;

done2:
    POP_DE;
    INC_DE;
    LD_A_de;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    PUSH_HL;
    JP(mNextChar);
}

void LineChar(void) {
    POP_HL;
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    PUSH_HL;
    JP(mNextChar);
}

void Paragraph(void) {
    PUSH_DE;

    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    IF_Z goto linkbattle;
    CP_A(LINK_MOBILE);
    IF_Z goto linkbattle;
    CALL(aLoadBlinkingCursor);

linkbattle:
    CALL(aText_WaitBGMap);
    CALL(aPromptButton);
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    CALL(aClearBox);
    CALL(aUnloadBlinkingCursor);
    LD_C(20);
    CALL(aDelayFrames);
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    POP_DE;
    JP(mNextChar);
}

void v_ContText(void) {
    LD_A_addr(wLinkMode);
    OR_A_A;
    IF_NZ goto communication;
    CALL(aLoadBlinkingCursor);

communication:
    CALL(aText_WaitBGMap);

    PUSH_DE;
    CALL(aPromptButton);
    POP_DE;

    LD_A_addr(wLinkMode);
    OR_A_A;
    CALL_Z(aUnloadBlinkingCursor);
    // fallthrough

    return v_ContTextNoPause();
}

void v_ContTextNoPause(void) {
    PUSH_DE;
    CALL(aTextScroll);
    CALL(aTextScroll);
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    POP_DE;
    JP(mNextChar);
}

void ContText(void) {
    PUSH_DE;
    LD_DE(mContText_cont);
    LD_B_H;
    LD_C_L;
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    POP_DE;
    JP(mNextChar);

cont:
    // db "<_CONT>@"

    return PlaceDexEnd();
}

void PlaceDexEnd(void) {
    //  Ends a Pokédex entry in Gen 1.
    //  Dex entries are now regular strings.
    LD_hl(0xe8);
    POP_HL;
    RET;
}

void PromptText(void) {
    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    IF_Z goto ok;
    CP_A(LINK_MOBILE);
    IF_Z goto ok;
    CALL(aLoadBlinkingCursor);

ok:
    CALL(aText_WaitBGMap);
    CALL(aPromptButton);
    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    JR_Z(mDoneText);
    CP_A(LINK_MOBILE);
    JR_Z(mDoneText);
    CALL(aUnloadBlinkingCursor);

    return DoneText();
}

void DoneText(void) {
    POP_HL;
    LD_DE(mDoneText_stop);
    DEC_DE;
    RET;

stop:
    // text_end ['?']

    return NullChar();
}

void NullChar(void) {
    LD_A(0xe6);
    LD_hli_A;
    CALL(aPrintLetterDelay);
    JP(mNextChar);
}

void TextScroll(void) {
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    decoord(TEXTBOX_INNERX, TEXTBOX_INNERY - 1, wTilemap);
    LD_A(TEXTBOX_INNERH - 1);

col:
    PUSH_AF;
    LD_C(TEXTBOX_INNERW);

row:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto row;

    INC_DE;
    INC_DE;
    INC_HL;
    INC_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto col;

    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    LD_A(0x7f);
    LD_BC(TEXTBOX_INNERW);
    CALL(aByteFill);
    LD_C(5);
    CALL(aDelayFrames);
    RET;
}

void Text_WaitBGMap(void) {
    PUSH_BC;
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(1);
    LDH_addr_A(hOAMUpdate);

    CALL(aWaitBGMap);

    POP_AF;
    LDH_addr_A(hOAMUpdate);
    POP_BC;
    RET;
}

void Diacritic(void) {
    RET;
}

void LoadBlinkingCursor(void) {
    LD_A(0xee);
    ldcoord_a(18, 17, wTilemap);
    RET;
}

void UnloadBlinkingCursor(void) {
    lda_coord(17, 17, wTilemap);
    ldcoord_a(18, 17, wTilemap);
    RET;
}

void PlaceFarString(void) {
    LD_B_A;
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A_B;
    RST(aBankswitch);
    CALL(aPlaceString);

    POP_AF;
    RST(aBankswitch);
    RET;
}

void PokeFluteTerminator(void) {
    LD_HL(mPokeFluteTerminator_stop);
    RET;

stop:
    // text_end ['?']

    return PlaceHLTextAtBC();
}

void PlaceHLTextAtBC(void) {
    LD_A_addr(wTextboxFlags);
    PUSH_AF;
    SET_A(NO_TEXT_DELAY_F);
    LD_addr_A(wTextboxFlags);

    CALL(aDoTextUntilTerminator);

    POP_AF;
    LD_addr_A(wTextboxFlags);
    RET;
}

void DoTextUntilTerminator(void) {
    LD_A_hli;
    CP_A(TX_END);
    RET_Z;
    CALL(aDoTextUntilTerminator_TextCommand);
    JR(mDoTextUntilTerminator);
}

void DoTextUntilTerminator_TextCommand(void) {
    PUSH_HL;
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(mTextCommands);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    POP_BC;
    POP_HL;
    JP(REG_DE);
}

void TextCommands(void) {
    //  entries correspond to TX_* constants (see macros/scripts/text.asm)
    // table_width ['2', 'TextCommands']
    // dw ['TextCommand_START'];  // TX_START
    // dw ['TextCommand_RAM'];  // TX_RAM
    // dw ['TextCommand_BCD'];  // TX_BCD
    // dw ['TextCommand_MOVE'];  // TX_MOVE
    // dw ['TextCommand_BOX'];  // TX_BOX
    // dw ['TextCommand_LOW'];  // TX_LOW
    // dw ['TextCommand_PROMPT_BUTTON'];  // TX_PROMPT_BUTTON
    // dw ['TextCommand_SCROLL'];  // TX_SCROLL
    // dw ['TextCommand_START_ASM'];  // TX_START_ASM
    // dw ['TextCommand_DECIMAL'];  // TX_DECIMAL
    // dw ['TextCommand_PAUSE'];  // TX_PAUSE
    // dw ['TextCommand_SOUND'];  // TX_SOUND_DEX_FANFARE_50_79
    // dw ['TextCommand_DOTS'];  // TX_DOTS
    // dw ['TextCommand_WAIT_BUTTON'];  // TX_WAIT_BUTTON
    // dw ['TextCommand_SOUND'];  // TX_SOUND_DEX_FANFARE_20_49
    // dw ['TextCommand_SOUND'];  // TX_SOUND_ITEM
    // dw ['TextCommand_SOUND'];  // TX_SOUND_CAUGHT_MON
    // dw ['TextCommand_SOUND'];  // TX_SOUND_DEX_FANFARE_80_109
    // dw ['TextCommand_SOUND'];  // TX_SOUND_FANFARE
    // dw ['TextCommand_SOUND'];  // TX_SOUND_SLOT_MACHINE_START
    // dw ['TextCommand_STRINGBUFFER'];  // TX_STRINGBUFFER
    // dw ['TextCommand_DAY'];  // TX_DAY
    // dw ['TextCommand_FAR'];  // TX_FAR
    // assert_table_length ['NUM_TEXT_CMDS']

    return TextCommand_START();
}

void TextCommand_START(void) {
    //  write text until "@"
    LD_D_H;
    LD_E_L;
    LD_H_B;
    LD_L_C;
    CALL(aPlaceString);
    LD_H_D;
    LD_L_E;
    INC_HL;
    RET;
}

void TextCommand_RAM(void) {
    //  write text from a ram address (little endian)
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    PUSH_HL;
    LD_H_B;
    LD_L_C;
    CALL(aPlaceString);
    POP_HL;
    RET;
}

void TextCommand_FAR(void) {
    //  write text from a different bank (little endian)
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;

    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    PUSH_HL;
    LD_H_D;
    LD_L_E;
    CALL(aDoTextUntilTerminator);
    POP_HL;

    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
    RET;
}

void TextCommand_BCD(void) {
    //  write bcd from address, typically ram
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    PUSH_HL;
    LD_H_B;
    LD_L_C;
    LD_C_A;
    CALL(aPrintBCDNumber);
    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;
}

void TextCommand_MOVE(void) {
    //  move to a new tile
    LD_A_hli;
    LD_addr_A(wMenuScrollPosition + 2);
    LD_C_A;
    LD_A_hli;
    LD_addr_A(wMenuScrollPosition + 2 + 1);
    LD_B_A;
    RET;
}

void TextCommand_BOX(void) {
    //  draw a box (height, width)
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_C_A;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    CALL(aTextbox);
    POP_HL;
    RET;
}

void TextCommand_LOW(void) {
    //  write text at (1,16)
    bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    RET;
}

void TextCommand_PROMPT_BUTTON(void) {
    //  wait for button press
    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    JP_Z(mTextCommand_WAIT_BUTTON);
    CP_A(LINK_MOBILE);
    JP_Z(mTextCommand_WAIT_BUTTON);

    PUSH_HL;
    CALL(aLoadBlinkingCursor);
    PUSH_BC;
    CALL(aPromptButton);
    POP_BC;
    CALL(aUnloadBlinkingCursor);
    POP_HL;
    RET;
}

void TextCommand_SCROLL(void) {
    //  pushes text up two lines and sets the BC cursor to the border tile
    //  below the first character column of the text box.
    PUSH_HL;
    CALL(aUnloadBlinkingCursor);
    CALL(aTextScroll);
    CALL(aTextScroll);
    POP_HL;
    bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    RET;
}

void TextCommand_START_ASM(void) {
    //  run assembly code
    BIT_H(7);
    IF_NZ goto not_rom;
    JP_hl;

not_rom:
    LD_A(TX_END);
    LD_hl_A;
    RET;
}

void TextCommand_DECIMAL(void) {
    //  print a decimal number
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    PUSH_HL;
    LD_H_B;
    LD_L_C;
    LD_B_A;
    AND_A(0xf);
    LD_C_A;
    LD_A_B;
    AND_A(0xf0);
    SWAP_A;
    SET_A(PRINTNUM_LEFTALIGN_F);
    LD_B_A;
    CALL(aPrintNum);
    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;
}

void TextCommand_PAUSE(void) {
    //  wait for button press or 30 frames
    PUSH_HL;
    PUSH_BC;
    CALL(aGetJoypad);
    LDH_A_addr(hJoyDown);
    AND_A(A_BUTTON | B_BUTTON);
    IF_NZ goto done;
    LD_C(30);
    CALL(aDelayFrames);

done:
    POP_BC;
    POP_HL;
    RET;
}

void TextCommand_SOUND(void) {
    //  play a sound effect from TextSFX
    PUSH_BC;
    DEC_HL;
    LD_A_hli;
    LD_B_A;
    PUSH_HL;
    LD_HL(mTextSFX);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    CP_A_B;
    IF_Z goto play;
    INC_HL;
    INC_HL;
    goto loop;

play:
    PUSH_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    POP_DE;

done:
    POP_HL;
    POP_BC;
    RET;
}

void TextCommand_CRY(void) {
    //  //  unreferenced
    //  play a pokemon cry
    PUSH_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALL(aPlayMonCry);
    POP_DE;
    POP_HL;
    POP_BC;
    RET;
}

void TextSFX(void) {
    // dbw ['TX_SOUND_DEX_FANFARE_50_79', 'SFX_DEX_FANFARE_50_79']
    // dbw ['TX_SOUND_FANFARE', 'SFX_FANFARE']
    // dbw ['TX_SOUND_DEX_FANFARE_20_49', 'SFX_DEX_FANFARE_20_49']
    // dbw ['TX_SOUND_ITEM', 'SFX_ITEM']
    // dbw ['TX_SOUND_CAUGHT_MON', 'SFX_CAUGHT_MON']
    // dbw ['TX_SOUND_DEX_FANFARE_80_109', 'SFX_DEX_FANFARE_80_109']
    // dbw ['TX_SOUND_SLOT_MACHINE_START', 'SFX_SLOT_MACHINE_START']
    // db ['-1'];

    return TextCommand_DOTS();
}

void TextCommand_DOTS(void) {
    //  wait for button press or 30 frames while printing "…"s
    LD_A_hli;
    LD_D_A;
    PUSH_HL;
    LD_H_B;
    LD_L_C;

loop:
    PUSH_DE;
    LD_A(0x75);
    LD_hli_A;
    CALL(aGetJoypad);
    LDH_A_addr(hJoyDown);
    AND_A(A_BUTTON | B_BUTTON);
    IF_NZ goto next;
    LD_C(10);
    CALL(aDelayFrames);

next:
    POP_DE;
    DEC_D;
    IF_NZ goto loop;

    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;
}

void TextCommand_WAIT_BUTTON(void) {
    //  wait for button press
    PUSH_HL;
    PUSH_BC;
    CALL(aPromptButton);
    POP_BC;
    POP_HL;
    RET;
}

void TextCommand_STRINGBUFFER(void) {
    //  Print a string from one of the following:
    //  0: wStringBuffer3
    //  1: wStringBuffer4
    //  2: wStringBuffer5
    //  3: wStringBuffer2
    //  4: wStringBuffer1
    //  5: wEnemyMonNickname
    //  6: wBattleMonNickname
    LD_A_hli;
    PUSH_HL;
    LD_E_A;
    LD_D(0);
    LD_HL(mStringBufferPointers);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A(BANK(aStringBufferPointers));
    CALL(aGetFarWord);
    LD_D_H;
    LD_E_L;
    LD_H_B;
    LD_L_C;
    CALL(aPlaceString);
    POP_HL;
    RET;
}

void TextCommand_DAY(void) {
    //  print the day of the week
    CALL(aGetWeekday);
    PUSH_HL;
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(mTextCommand_DAY_Days);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mTextCommand_DAY_Day);
    CALL(aPlaceString);
    POP_HL;
    RET;

/*Currently not used?
Days:
    // dw ['.Sun'];
    // dw ['.Mon'];
    // dw ['.Tues'];
    // dw ['.Wednes'];
    // dw ['.Thurs'];
    // dw ['.Fri'];
    // dw ['.Satur'];

Sun:
    //    db "SUN@"

Mon:
    //    db "MON@"

Tues:
    //   db "TUES@"

Wednes:
    // db "WEDNES@"

Thurs:
    //  db "THURS@"

Fri:
    //    db "FRI@"

Satur:
    //  db "SATUR@"

Day:
    //    db "DAY@"
*/
}
