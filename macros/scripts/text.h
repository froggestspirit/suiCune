/*#define text   0x00,    // Start writing text.
#define next   0x4e,  // Move a line down.
#define line   0x4f,  // Start writing at the bottom line.
#define page   0x50,       // Start a new Pokédex page.
#define para   0x51,  // Start a new paragraph.
#define cont   0x55,  // Scroll to the next line.
#define done   0x57   // End a text box.
#define prompt 0x58 // Prompt the player to end a text box (initiating some other event).
*/
// TextCommands indexes (see home/text.asm)

#define TX_START 0x00
/*text_start: MACRO
    db TX_START
ENDM*/

#define TX_RAM 0x01
/*text_ram: MACRO
    db TX_RAM
    dw \1
ENDM*/

#define TX_BCD 0x02
/*text_bcd: MACRO
    db TX_BCD
    dw \1
    db \2
ENDM*/

#define TX_MOVE 0x03
/*text_move: MACRO
    db TX_MOVE
    dw \1
ENDM*/

#define TX_BOX 0x04
/*text_box: MACRO
    db TX_BOX
    dw \1
    db \2, \3
ENDM*/

#define TX_LOW 0x05
/*text_low: MACRO
    db TX_LOW
ENDM*/

#define TX_PROMPT_BUTTON 0x06
/*text_promptbutton: MACRO
    db TX_PROMPT_BUTTON
ENDM*/

#define TX_SCROLL 0x07
/*text_scroll: MACRO
    db TX_SCROLL
ENDM*/

#define TX_START_ASM 0x08
/*text_asm: MACRO
    db TX_START_ASM
ENDM*/

#define TX_DECIMAL 0x09
/*text_decimal: MACRO
    db TX_DECIMAL
    dw \1 // address
    dn \2, \3 // bytes, digits
ENDM*/

#define TX_PAUSE 0x0a
/*text_pause: MACRO
    db TX_PAUSE
ENDM*/

#define TX_SOUND_DEX_FANFARE_50_79 0x0b
/*sound_dex_fanfare_50_79: MACRO
    db TX_SOUND_DEX_FANFARE_50_79
ENDM*/

#define TX_DOTS 0x0c
/*text_dots: MACRO
    db TX_DOTS
    db \1
ENDM*/

#define TX_WAIT_BUTTON 0x0d
/*text_waitbutton: MACRO
    db TX_WAIT_BUTTON
ENDM*/

#define TX_SOUND_DEX_FANFARE_20_49 0x0e
/*sound_dex_fanfare_20_49: MACRO
    db TX_SOUND_DEX_FANFARE_20_49
ENDM*/

#define TX_SOUND_ITEM 0x0f
/*sound_item: MACRO
    db TX_SOUND_ITEM
ENDM*/

#define TX_SOUND_CAUGHT_MON 0x10
/*sound_caught_mon: MACRO
    db TX_SOUND_CAUGHT_MON
ENDM*/

#define TX_SOUND_DEX_FANFARE_80_109 0x11
/*sound_dex_fanfare_80_109: MACRO
    db TX_SOUND_DEX_FANFARE_80_109
ENDM*/

#define TX_SOUND_FANFARE 0x12
/*sound_fanfare: MACRO
    db TX_SOUND_FANFARE
ENDM*/

#define TX_SOUND_SLOT_MACHINE_START 0x13
/*sound_slot_machine_start: MACRO
    db TX_SOUND_SLOT_MACHINE_START
ENDM*/

#define TX_STRINGBUFFER 0x14
/*text_buffer: MACRO
    db TX_STRINGBUFFER
    db \1
ENDM*/

#define TX_DAY 0x15
/*text_today: MACRO
    db TX_DAY
ENDM*/

#define TX_FAR 0x16
/*text_far: MACRO
    db TX_FAR
    dw \1
    db BANK(\1)
ENDM*/

#define NUM_TEXT_CMDS TX_FAR + 1

#define TX_END 0x50
/*text_end: MACRO
    db TX_END
ENDM*/
