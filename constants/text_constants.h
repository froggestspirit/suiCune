// name lengths
#define NAME_LENGTH 11
#define PLAYER_NAME_LENGTH 8
#define BOX_NAME_LENGTH 9
#define MON_NAME_LENGTH 11
#define MOVE_NAME_LENGTH 13
#define ITEM_NAME_LENGTH 13
#define TRAINER_CLASS_NAME_LENGTH 13
#define NAME_LENGTH_JAPANESE 6

// GetName types (see home/names.asm)
enum {
    MON_NAME = 1,          // 1
    MOVE_NAME,             // 2
    DUMMY_NAME,            // 3
    ITEM_NAME,             // 4
    PARTY_OT_NAME,         // 5
    ENEMY_OT_NAME,         // 6
    TRAINER_NAME,          // 7
    MOVE_DESC_NAME_BROKEN, // 8
};

// see home/text.asm
#define BORDER_WIDTH 2
#define TEXTBOX_WIDTH SCREEN_WIDTH
#define TEXTBOX_INNERW (TEXTBOX_WIDTH - BORDER_WIDTH)
#define TEXTBOX_HEIGHT 6
#define TEXTBOX_INNERH (TEXTBOX_HEIGHT - BORDER_WIDTH)
#define TEXTBOX_X 0
#define TEXTBOX_INNERX (TEXTBOX_X + 1)
#define TEXTBOX_Y (SCREEN_HEIGHT - TEXTBOX_HEIGHT)
#define TEXTBOX_INNERY (TEXTBOX_Y + 2)

// see gfx/frames/*.png
#define TEXTBOX_FRAME_TILES 6

// PrintNum bit flags
enum {
    PRINTNUM_MONEY_F = 5,    // 5
    PRINTNUM_LEFTALIGN_F,    // 6
    PRINTNUM_LEADINGZEROS_F, // 7
};

// PrintNum arguments (see engine/math/print_num.asm)
#define PRINTNUM_MONEY (1 << PRINTNUM_MONEY_F)
#define PRINTNUM_LEFTALIGN (1 << PRINTNUM_LEFTALIGN_F)
#define PRINTNUM_LEADINGZEROS (1 << PRINTNUM_LEADINGZEROS_F)

// character sets (see charmap.asm)
#define FIRST_REGULAR_TEXT_CHAR 0x60
#define FIRST_HIRAGANA_DAKUTEN_CHAR 0x20

// gfx/font/unown_font.png
#define FIRST_UNOWN_CHAR 0x40
