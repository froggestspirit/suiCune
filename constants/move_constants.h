// move ids
// indexes for:
// - Moves (see data/moves/moves.asm)
// - MoveNames (see data/moves/names.asm)
// - MoveDescriptions (see data/moves/descriptions.asm)
// - BattleAnimations (see data/moves/animations.asm)
enum {
    NO_MOVE,      // 00
    POUND,        // 01
    KARATE_CHOP,  // 02
    DOUBLESLAP,   // 03
    COMET_PUNCH,  // 04
    MEGA_PUNCH,   // 05
    PAY_DAY,      // 06
    FIRE_PUNCH,   // 07
    ICE_PUNCH,    // 08
    THUNDERPUNCH, // 09
    SCRATCH,      // 0a
    VICEGRIP,     // 0b
    GUILLOTINE,   // 0c
    RAZOR_WIND,   // 0d
    SWORDS_DANCE, // 0e
    CUT,          // 0f
    GUST,         // 10
    WING_ATTACK,  // 11
    WHIRLWIND,    // 12
    FLY,          // 13
    BIND,         // 14
    SLAM,         // 15
    VINE_WHIP,    // 16
    STOMP,        // 17
    DOUBLE_KICK,  // 18
    MEGA_KICK,    // 19
    JUMP_KICK,    // 1a
    ROLLING_KICK, // 1b
    SAND_ATTACK,  // 1c
    HEADBUTT,     // 1d
    HORN_ATTACK,  // 1e
    FURY_ATTACK,  // 1f
    HORN_DRILL,   // 20
    TACKLE,       // 21
    BODY_SLAM,    // 22
    WRAP,         // 23
    TAKE_DOWN,    // 24
    THRASH,       // 25
    DOUBLE_EDGE,  // 26
    TAIL_WHIP,    // 27
    POISON_STING, // 28
    TWINEEDLE,    // 29
    PIN_MISSILE,  // 2a
    LEER,         // 2b
    BITE,         // 2c
    GROWL,        // 2d
    ROAR,         // 2e
    SING,         // 2f
    SUPERSONIC,   // 30
    SONICBOOM,    // 31
    DISABLE,      // 32
    ACID,         // 33
    EMBER,        // 34
    FLAMETHROWER, // 35
    MIST,         // 36
    WATER_GUN,    // 37
    HYDRO_PUMP,   // 38
    SURF,         // 39
    ICE_BEAM,     // 3a
    BLIZZARD,     // 3b
    PSYBEAM,      // 3c
    BUBBLEBEAM,   // 3d
    AURORA_BEAM,  // 3e
    HYPER_BEAM,   // 3f
    PECK,         // 40
    DRILL_PECK,   // 41
    SUBMISSION,   // 42
    LOW_KICK,     // 43
    COUNTER,      // 44
    SEISMIC_TOSS, // 45
    STRENGTH,     // 46
    ABSORB,       // 47
    MEGA_DRAIN,   // 48
    LEECH_SEED,   // 49
    GROWTH,       // 4a
    RAZOR_LEAF,   // 4b
    SOLARBEAM,    // 4c
    POISONPOWDER, // 4d
    STUN_SPORE,   // 4e
    SLEEP_POWDER, // 4f
    PETAL_DANCE,  // 50
    STRING_SHOT,  // 51
    DRAGON_RAGE,  // 52
    FIRE_SPIN,    // 53
    THUNDERSHOCK, // 54
    THUNDERBOLT,  // 55
    THUNDER_WAVE, // 56
    THUNDER,      // 57
    ROCK_THROW,   // 58
    EARTHQUAKE,   // 59
    FISSURE,      // 5a
    DIG,          // 5b
    TOXIC,        // 5c
    CONFUSION,    // 5d
    PSYCHIC_M,    // 5e
    HYPNOSIS,     // 5f
    MEDITATE,     // 60
    AGILITY,      // 61
    QUICK_ATTACK, // 62
    RAGE,         // 63
    TELEPORT,     // 64
    NIGHT_SHADE,  // 65
    MIMIC,        // 66
    SCREECH,      // 67
    DOUBLE_TEAM,  // 68
    RECOVER,      // 69
    HARDEN,       // 6a
    MINIMIZE,     // 6b
    SMOKESCREEN,  // 6c
    CONFUSE_RAY,  // 6d
    WITHDRAW,     // 6e
    DEFENSE_CURL, // 6f
    BARRIER,      // 70
    LIGHT_SCREEN, // 71
    HAZE,         // 72
    REFLECT,      // 73
    FOCUS_ENERGY, // 74
    BIDE,         // 75
    METRONOME,    // 76
    MIRROR_MOVE,  // 77
    SELFDESTRUCT, // 78
    EGG_BOMB,     // 79
    LICK,         // 7a
    SMOG,         // 7b
    SLUDGE,       // 7c
    BONE_CLUB,    // 7d
    FIRE_BLAST,   // 7e
    WATERFALL,    // 7f
    CLAMP,        // 80
    SWIFT,        // 81
    SKULL_BASH,   // 82
    SPIKE_CANNON, // 83
    CONSTRICT,    // 84
    AMNESIA,      // 85
    KINESIS,      // 86
    SOFTBOILED,   // 87
    HI_JUMP_KICK, // 88
    GLARE,        // 89
    DREAM_EATER,  // 8a
    POISON_GAS,   // 8b
    BARRAGE,      // 8c
    LEECH_LIFE,   // 8d
    LOVELY_KISS,  // 8e
    SKY_ATTACK,   // 8f
    TRANSFORM,    // 90
    BUBBLE,       // 91
    DIZZY_PUNCH,  // 92
    SPORE,        // 93
    FLASH,        // 94
    PSYWAVE,      // 95
    SPLASH,       // 96
    ACID_ARMOR,   // 97
    CRABHAMMER,   // 98
    EXPLOSION,    // 99
    FURY_SWIPES,  // 9a
    BONEMERANG,   // 9b
    REST,         // 9c
    ROCK_SLIDE,   // 9d
    HYPER_FANG,   // 9e
    SHARPEN,      // 9f
    CONVERSION,   // a0
    TRI_ATTACK,   // a1
    SUPER_FANG,   // a2
    SLASH,        // a3
    SUBSTITUTE,   // a4
    STRUGGLE,     // a5
    SKETCH,       // a6
    TRIPLE_KICK,  // a7
    THIEF,        // a8
    SPIDER_WEB,   // a9
    MIND_READER,  // aa
    NIGHTMARE,    // ab
    FLAME_WHEEL,  // ac
    SNORE,        // ad
    CURSE,        // ae
    FLAIL,        // af
    CONVERSION2,  // b0
    AEROBLAST,    // b1
    COTTON_SPORE, // b2
    REVERSAL,     // b3
    SPITE,        // b4
    POWDER_SNOW,  // b5
    PROTECT,      // b6
    MACH_PUNCH,   // b7
    SCARY_FACE,   // b8
    FAINT_ATTACK, // b9
    SWEET_KISS,   // ba
    BELLY_DRUM,   // bb
    SLUDGE_BOMB,  // bc
    MUD_SLAP,     // bd
    OCTAZOOKA,    // be
    SPIKES,       // bf
    ZAP_CANNON,   // c0
    FORESIGHT,    // c1
    DESTINY_BOND, // c2
    PERISH_SONG,  // c3
    ICY_WIND,     // c4
    DETECT,       // c5
    BONE_RUSH,    // c6
    LOCK_ON,      // c7
    OUTRAGE,      // c8
    SANDSTORM,    // c9
    GIGA_DRAIN,   // ca
    ENDURE,       // cb
    CHARM,        // cc
    ROLLOUT,      // cd
    FALSE_SWIPE,  // ce
    SWAGGER,      // cf
    MILK_DRINK,   // d0
    SPARK,        // d1
    FURY_CUTTER,  // d2
    STEEL_WING,   // d3
    MEAN_LOOK,    // d4
    ATTRACT,      // d5
    SLEEP_TALK,   // d6
    HEAL_BELL,    // d7
    RETURN,       // d8
    PRESENT,      // d9
    FRUSTRATION,  // da
    SAFEGUARD,    // db
    PAIN_SPLIT,   // dc
    SACRED_FIRE,  // dd
    MAGNITUDE,    // de
    DYNAMICPUNCH, // df
    MEGAHORN,     // e0
    DRAGONBREATH, // e1
    BATON_PASS,   // e2
    ENCORE,       // e3
    PURSUIT,      // e4
    RAPID_SPIN,   // e5
    SWEET_SCENT,  // e6
    IRON_TAIL,    // e7
    METAL_CLAW,   // e8
    VITAL_THROW,  // e9
    MORNING_SUN,  // ea
    SYNTHESIS,    // eb
    MOONLIGHT,    // ec
    HIDDEN_POWER, // ed
    CROSS_CHOP,   // ee
    TWISTER,      // ef
    RAIN_DANCE,   // f0
    SUNNY_DAY,    // f1
    CRUNCH,       // f2
    MIRROR_COAT,  // f3
    PSYCH_UP,     // f4
    EXTREMESPEED, // f5
    ANCIENTPOWER, // f6
    SHADOW_BALL,  // f7
    FUTURE_SIGHT, // f8
    ROCK_SMASH,   // f9
    WHIRLPOOL,    // fa
    BEAT_UP,      // fb
};
#define NUM_ATTACKS BEAT_UP

// Battle animations use the same constants as the moves up to this point
enum {
    ANIM_SWEET_SCENT_2 = 0xFF,
    ANIM_THROW_POKE_BALL,   // 100
    ANIM_SEND_OUT_MON,      // 101
    ANIM_RETURN_MON,        // 102
    ANIM_CONFUSED,          // 103
    ANIM_SLP,               // 104
    ANIM_BRN,               // 105
    ANIM_PSN,               // 106
    ANIM_SAP,               // 107
    ANIM_FRZ,               // 108
    ANIM_PAR,               // 109
    ANIM_IN_LOVE,           // 10a
    ANIM_IN_SANDSTORM,      // 10b
    ANIM_IN_NIGHTMARE,      // 10c
    ANIM_IN_WHIRLPOOL,      // 10d
// battle anims
    ANIM_MISS,              // 10e
    ANIM_ENEMY_DAMAGE,      // 10f
    ANIM_ENEMY_STAT_DOWN,   // 110
    ANIM_PLAYER_STAT_DOWN,  // 111
    ANIM_PLAYER_DAMAGE,     // 112
    ANIM_WOBBLE,            // 113
    ANIM_SHAKE,             // 114
    ANIM_HIT_CONFUSION,     // 115
};
#define NUM_BATTLE_ANIMS ANIM_HIT_CONFUSION

// wNumHits uses offsets from ANIM_MISS
enum {
    BATTLEANIM_NONE,
    BATTLEANIM_ENEMY_DAMAGE,
    BATTLEANIM_ENEMY_STAT_DOWN,
    BATTLEANIM_PLAYER_STAT_DOWN,
    BATTLEANIM_PLAYER_DAMAGE,
    BATTLEANIM_WOBBLE,
    BATTLEANIM_SHAKE,
    BATTLEANIM_HIT_CONFUSION,
};