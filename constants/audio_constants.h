
// pitch
// FrequencyTable indexes (see audio/notes.asm)
enum {
    C_ = 1,
    Cs,
    D_,
    Ds,
    E_,
    F_,
    Fs,
    G_,
    Gs,
    A_,
    As,
    B_,
    NUM_NOTES = B_
};

// channel
// ChannelPointers indexes (see audio/engine.asm)
enum {
    CHAN1 = 0,
    CHAN2, // 1
    CHAN3, // 2
    CHAN4, // 3
    CHAN5, // 4
    CHAN6, // 5
    CHAN7, // 6
    CHAN8, // 7
};
#define NUM_MUSIC_CHANS (CHAN4 + 1)
#define NUM_NOISE_CHANS ((CHAN8 + 1) - NUM_MUSIC_CHANS)
#define NUM_CHANNELS (CHAN8 + 1)

// channel_struct members (see macros/wram.asm)
enum {
    CHANNEL_MUSIC_ID                    = 0,
    CHANNEL_MUSIC_BANK                  = 2,
    CHANNEL_FLAGS1                      = 3,
    CHANNEL_FLAGS2                      = 4,
    CHANNEL_FLAGS3                      = 5,
    CHANNEL_MUSIC_ADDRESS               = 6,
    CHANNEL_LAST_MUSIC_ADDRESS          = 8,

    CHANNEL_NOTE_FLAGS                  = 12,
    CHANNEL_CONDITION                   = 13,
    CHANNEL_DUTY_CYCLE                  = 14,
    CHANNEL_VOLUME_ENVELOPE             = 15,
    CHANNEL_FREQUENCY                   = 16,
    CHANNEL_PITCH                       = 18,
    CHANNEL_OCTAVE                      = 19,
    CHANNEL_TRANSPOSITION               = 20,
    CHANNEL_NOTE_DURATION               = 21,
    CHANNEL_FIELD16                     = 22,

    CHANNEL_LOOP_COUNT                  = 24,
    CHANNEL_TEMPO                       = 25,
    CHANNEL_TRACKS                      = 27,
    CHANNEL_DUTY_CYCLE_PATTERN          = 28,
    CHANNEL_VIBRATO_DELAY_COUNT         = 29,
    CHANNEL_VIBRATO_DELAY               = 30,
    CHANNEL_VIBRATO_EXTENT              = 31,
    CHANNEL_VIBRATO_RATE                = 32,
    CHANNEL_PITCH_SLIDE_TARGET          = 33,
    CHANNEL_PITCH_SLIDE_AMOUNT          = 35,
    CHANNEL_PITCH_SLIDE_AMOUNT_FRACTION = 36,
    CHANNEL_FIELD25                     = 37,

    CHANNEL_PITCH_OFFSET                = 39,
    CHANNEL_FIELD29                     = 41,
    CHANNEL_FIELD2A                     = 42,
    CHANNEL_FIELD2C                     = 44,
    CHANNEL_NOTE_LENGTH                 = 45,
    CHANNEL_FIELD2E                     = 46,
    CHANNEL_FIELD2F                     = 47,
    CHANNEL_FIELD30                     = 48,
};
#define CHANNEL_STRUCT_LENGTH 50

#define NOISE_CHAN_F 2 // bit set in CHAN5-CHAN7

// Flags1
enum {
    SOUND_CHANNEL_ON = 0,
    SOUND_SUBROUTINE, // 1
    SOUND_LOOPING,    // 2
    SOUND_SFX,        // 3
    SOUND_NOISE,      // 4
    SOUND_CRY,        // 5
};
// Flags2
enum {
    SOUND_VIBRATO = 0,
    SOUND_PITCH_SLIDE,  // 1
    SOUND_DUTY_LOOP,    // 2
    SOUND_UNKN_0B,      // 3
    SOUND_PITCH_OFFSET, // 4
    SOUND_UNKN_0D,      // 5
    SOUND_UNKN_0E,      // 6
    SOUND_UNKN_0F,      // 7
};
// Flags3
enum {
    SOUND_VIBRATO_DIR = 0,
    SOUND_PITCH_SLIDE_DIR, // 1
};
// NoteFlags
enum {
    NOTE_DUTY_OVERRIDE = 0,
    NOTE_FREQ_OVERRIDE,    // 1
    NOTE_UNUSED,           // 2
    NOTE_PITCH_SWEEP,      // 3
    NOTE_NOISE_SAMPLING,   // 4
    NOTE_REST,             // 5
    NOTE_VIBRATO_OVERRIDE, // 6
};
// wVolume
#define VOLUME_SO1_F     3
#define VOLUME_SO2_F     7
#define VOLUME_SO1_LEVEL 0b00000111
#define VOLUME_SO2_LEVEL 0b01110000
#define MAX_VOLUME       0x77

// wSoundInput
#define SOUND_INPUT_CH1_F    0
#define SOUND_INPUT_CH2_F    1
#define SOUND_INPUT_CH3_F    2
#define SOUND_INPUT_CH4_F    3
#define SOUND_INPUT_GLOBAL_F 7

// wLowHealthAlarm
#define DANGER_PITCH_F 4
#define DANGER_ON_F    7

// wMusicFade
#define MUSIC_FADE_IN_F 7
