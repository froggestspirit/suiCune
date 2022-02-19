// joypad buttons
enum {
    A_BUTTON_F, // 0
    B_BUTTON_F, // 1
    SELECT_F,   // 2
    START_F,    // 3
    D_RIGHT_F,  // 4
    D_LEFT_F,   // 5
    D_UP_F,     // 6
    D_DOWN_F,   // 7
};

#define NO_INPUT 0b00000000
#define A_BUTTON (1 << A_BUTTON_F)
#define B_BUTTON (1 << B_BUTTON_F)
#define SELECT (1 << SELECT_F)
#define START (1 << START_F)
#define D_RIGHT (1 << D_RIGHT_F)
#define D_LEFT (1 << D_LEFT_F)
#define D_UP (1 << D_UP_F)
#define D_DOWN (1 << D_DOWN_F)

#define BUTTONS A_BUTTON | B_BUTTON | SELECT | START
#define D_PAD D_RIGHT | D_LEFT | D_UP | D_DOWN

#define R_DPAD 0b00100000
#define R_BUTTONS 0b00010000
