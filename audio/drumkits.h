#include "../macros/scripts/audio.h"

// noise_note([xy], [envelope volume], [envelope fade], [frequency])
// x = 2 or 3?
// y = length - 1

static uint8_t Drum00[] = {
    noise_note(32, 1, 1, 0),
    sound_ret,
};

static uint8_t Snare1[] = {
    noise_note(32, 12, 1, 51),
    sound_ret,
};

static uint8_t Snare2[] = {
    noise_note(32, 11, 1, 51),
    sound_ret,
};

static uint8_t Snare3[] = {
    noise_note(32, 10, 1, 51),
    sound_ret,
};

static uint8_t Snare4[] = {
    noise_note(32, 8, 1, 51),
    sound_ret,
};

static uint8_t Drum05[] = {
    noise_note(39, 8, 4, 55),
    noise_note(38, 8, 4, 54),
    noise_note(37, 8, 3, 53),
    noise_note(36, 8, 3, 52),
    noise_note(35, 8, 2, 51),
    noise_note(34, 8, 1, 50),
    sound_ret,
};

static uint8_t Triangle1[] = {
    noise_note(32, 5, 1, 42),
    sound_ret,
};

static uint8_t Triangle2[] = {
    noise_note(33, 4, 1, 43),
    noise_note(32, 6, 1, 42),
    sound_ret,
};

static uint8_t HiHat1[] = {
    noise_note(32, 8, 1, 16),
    sound_ret,
};

static uint8_t Snare5[] = {
    noise_note(32, 8, 2, 35),
    sound_ret,
};

static uint8_t Snare6[] = {
    noise_note(32, 8, 2, 37),
    sound_ret,
};

static uint8_t Snare7[] = {
    noise_note(32, 8, 2, 38),
    sound_ret,
};

static uint8_t HiHat2[] = {
    noise_note(32, 10, 1, 16),
    sound_ret,
};

static uint8_t HiHat3[] = {
    noise_note(32, 10, 2, 17),
    sound_ret,
};

static uint8_t Snare8[] = {
    noise_note(32, 10, 2, 80),
    sound_ret,
};

static uint8_t Triangle3[] = {
    noise_note(32, 10, 1, 24),
    noise_note(32, 3, 1, 51),
    sound_ret,
};

static uint8_t Triangle4[] = {
    noise_note(34, 9, 1, 40),
    noise_note(32, 7, 1, 24),
    sound_ret,
};

static uint8_t Snare9[] = {
    noise_note(32, 9, 1, 34),
    sound_ret,
};

static uint8_t Snare10[] = {
    noise_note(32, 7, 1, 34),
    sound_ret,
};

static uint8_t Snare11[] = {
    noise_note(32, 6, 1, 34),
    sound_ret,
};

static uint8_t Drum20[] = {
    noise_note(32, 1, 1, 17),
    sound_ret,
};

static uint8_t Drum21[] = {
    sound_ret,
};

static uint8_t Snare12[] = {
    noise_note(32, 9, 1, 51),
    sound_ret,
};

static uint8_t Snare13[] = {
    noise_note(32, 5, 1, 50),
    sound_ret,
};

static uint8_t Snare14[] = {
    noise_note(32, 8, 1, 49),
    sound_ret,
};

static uint8_t Kick1[] = {
    noise_note(32, 8, 8, 107),
    noise_note(32, 7, 1, 0),
    sound_ret,
};

static uint8_t Triangle5[] = {
    noise_note(48, 9, 1, 24),
    sound_ret,
};

static uint8_t Drum27[] = {
    noise_note(39, 9, 2, 16),
    sound_ret,
};

static uint8_t Drum28[] = {
    noise_note(51, 9, 1, 0),
    noise_note(51, 1, 1, 0),
    sound_ret,
};

static uint8_t Drum29[] = {
    noise_note(51, 9, 1, 17),
    noise_note(51, 1, 1, 0),
    sound_ret,
};

static uint8_t Crash1[] = {
    noise_note(51, 8, 8, 21),
    noise_note(32, 6, 5, 18),
    sound_ret,
};

static uint8_t Drum31[] = {
    noise_note(51, 5, 1, 33),
    noise_note(51, 1, 1, 17),
    sound_ret,
};

static uint8_t Drum32[] = {
    noise_note(51, 5, 1, 80),
    noise_note(51, 1, 1, 17),
    sound_ret,
};

static uint8_t Drum33[] = {
    noise_note(32, 10, 1, 49),
    sound_ret,
};

static uint8_t Crash2[] = {
    noise_note(32, 8, 4, 18),
    sound_ret,
};

static uint8_t Drum35[] = {
    noise_note(51, 8, 1, 0),
    noise_note(51, 1, 1, 0),
    sound_ret,
};

static uint8_t Drum36[] = {
    noise_note(51, 8, 1, 33),
    noise_note(51, 1, 1, 17),
    sound_ret,
};

static uint8_t Kick2[] = {
    noise_note(32, 10, 8, 107),
    noise_note(32, 7, 1, 0),
    sound_ret,
};

static uint8_t *Drumkit0[] = {
    Drum00,
    Snare1,
    Snare2,
    Snare3,
    Snare4,
    Drum05,
    Triangle1,
    Triangle2,
    HiHat1,
    Snare5,
    Snare6,
    Snare7,
    HiHat2,
};

static uint8_t *Drumkit1[] = {
    Drum00,
    HiHat1,
    Snare5,
    Snare6,
    Snare7,
    HiHat2,
    HiHat3,
    Snare8,
    Triangle3,
    Triangle4,
    Snare9,
    Snare10,
    Snare11,
};

static uint8_t *Drumkit2[] = {
    Drum00,
    Snare1,
    Snare9,
    Snare10,
    Snare11,
    Drum05,
    Triangle1,
    Triangle2,
    HiHat1,
    Snare5,
    Snare6,
    Snare7,
    HiHat2,
};

static uint8_t *Drumkit3[] = {
    Drum21,
    Snare12,
    Snare13,
    Snare14,
    Kick1,
    Triangle5,
    Drum20,
    Drum27,
    Drum28,
    Drum29,
    Drum21,
    Kick2,
    Crash2,
};

static uint8_t *Drumkit4[] = {
    Drum21,
    Drum20,
    Snare13,
    Snare14,
    Kick1,
    Drum33,
    Triangle5,
    Drum35,
    Drum31,
    Drum32,
    Drum36,
    Kick2,
    Crash1,
};

static uint8_t *Drumkit5[] = {
    Drum00,
    Snare9,
    Snare10,
    Snare11,
    Drum27,
    Drum28,
    Drum29,
    Drum05,
    Triangle1,
    Crash1,
    Snare14,
    Snare13,
    Kick2,
};

static uint8_t **Drumkits[] = {
    Drumkit0,
    Drumkit1,
    Drumkit2,
    Drumkit3,
    Drumkit4,
    Drumkit5,
};
