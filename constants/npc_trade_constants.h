// npctrade struct members (see data/events/npc_trades.asm)
enum {
    NPCTRADE_DIALOG,
    NPCTRADE_GIVEMON,
    NPCTRADE_GETMON,
    NPCTRADE_NICKNAME,
    NPCTRADE_DVS = NPCTRADE_NICKNAME + MON_NAME_LENGTH,
    NPCTRADE_ITEM = NPCTRADE_DVS + 2,
    NPCTRADE_OT_ID,
    NPCTRADE_OT_NAME = NPCTRADE_OT_ID + 2,
    NPCTRADE_GENDER = NPCTRADE_OT_NAME + NAME_LENGTH,
    NPCTRADE_STRUCT_LENGTH = NPCTRADE_GENDER + 2,
};
// NPCTrades indexes (see data/events/npc_trades.asm)
enum {
    NPC_TRADE_MIKE,    // 0
    NPC_TRADE_KYLE,    // 1
    NPC_TRADE_TIM,     // 2
    NPC_TRADE_EMY,     // 3
    NPC_TRADE_CHRIS,   // 4
    NPC_TRADE_KIM,     // 5
    NPC_TRADE_FOREST,  // 6
    NUM_NPC_TRADES,
};

// trade gender limits
enum {
    TRADE_GENDER_EITHER,
    TRADE_GENDER_MALE,
    TRADE_GENDER_FEMALE,
};

// TradeTexts indexes (see engine/events/npc_trade.asm)

// trade dialogs
enum {
    TRADE_DIALOG_INTRO,
    TRADE_DIALOG_CANCEL,
    TRADE_DIALOG_WRONG,
    TRADE_DIALOG_COMPLETE,
    TRADE_DIALOG_AFTER,
};

// trade dialog sets
enum {
    TRADE_DIALOGSET_COLLECTOR,
    TRADE_DIALOGSET_HAPPY,
    TRADE_DIALOGSET_NEWBIE,
    TRADE_DIALOGSET_GIRL,
};
