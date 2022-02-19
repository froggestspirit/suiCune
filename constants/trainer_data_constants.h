// TrainerClassAttributes struct members (see data/trainers/attributes.asm)
enum {
    TRNATTR_ITEM1,
    TRNATTR_ITEM2,
    TRNATTR_BASEMONEY,
    TRNATTR_AI_MOVE_WEIGHTS,
    TRNATTR_AI_ITEM_SWITCH = TRNATTR_AI_MOVE_WEIGHTS + 2,
    NUM_TRAINER_ATTRIBUTES = TRNATTR_AI_ITEM_SWITCH + 2,
};

// TRNATTR_AI_MOVE_WEIGHTS bit flags (wEnemyTrainerAIFlags)
// AIScoringPointers indexes (see engine/battle/ai/move.asm)
enum {
    AI_BASIC = 1,
    AI_SETUP = 2,
    AI_TYPES = 4,
    AI_OFFENSIVE = 8,
    AI_SMART = 16,
    AI_OPPORTUNIST = 32,
    AI_AGGRESSIVE = 64,
    AI_CAUTIOUS = 128,
    AI_STATUS = 256,
    AI_RISKY = 512,
};
#define NO_AI 0

// TRNATTR_AI_ITEM_SWITCH bit flags
enum {
    SWITCH_OFTEN_F,     // 0
    SWITCH_RARELY_F,    // 1
    SWITCH_SOMETIMES_F, // 2
    ALWAYS_USE_F = 4,   // 4
    UNKNOWN_USE_F,      // 5
    CONTEXT_USE_F,      // 6
};

#define SWITCH_OFTEN (1 << SWITCH_OFTEN_F)
#define SWITCH_RARELY (1 << SWITCH_RARELY_F)
#define SWITCH_SOMETIMES (1 << SWITCH_SOMETIMES_F)
#define ALWAYS_USE (1 << ALWAYS_USE_F)
#define UNKNOWN_USE (1 << UNKNOWN_USE_F)
#define CONTEXT_USE (1 << CONTEXT_USE_F)

// TrainerTypes indexes (see engine/battle/read_trainer_party.asm)
enum {
    TRAINERTYPE_NORMAL,
    TRAINERTYPE_MOVES,
    TRAINERTYPE_ITEM,
    TRAINERTYPE_ITEM_MOVES,
};
