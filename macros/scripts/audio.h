/*channel_count: MACRO
    assert 0 < (\1) && (\1) <= NUM_MUSIC_CHANS, \
        "channel_count must be 1-{d:NUM_MUSIC_CHANS}"
_num_channels = \1 - 1
ENDM*/

/*channel: MACRO
    assert 0 < (\1) && (\1) <= NUM_CHANNELS, \
        "channel id must be 1-{d:NUM_CHANNELS}"
    dn (_num_channels << 2), \1 - 1 // channel id
    dw \2 // address
_num_channels = 0
ENDM*/

/*note: MACRO
    dn (\1), (\2) - 1 // pitch, length
ENDM*/

/*drum_note: MACRO
    note \1, \2 // drum instrument, length
ENDM*/

/*rest: MACRO
    note 0, \1 // length
ENDM*/

/*square_note: MACRO
    db \1 // length
    if \3 < 0
        dn \2, 0b1000 | (\3 * -1) // volume envelope
    else
        dn \2, \3 // volume envelope
    endc
    dw \4 // frequency
ENDM*/

#define noise_note(len, vol, fade, freq) len, (vol << 4) | (fade < 0 ? (8 | (fade * -1)) : fade), freq
/*noise_note: MACRO
    db \1 // length
    if \3 < 0
        dn \2, 0b1000 | (\3 * -1) // volume envelope
    else
        dn \2, \3 // volume envelope
    endc
    db \4 // frequency
ENDM*/

// MusicCommands indexes (see audio/engine.asm)
#define FIRST_MUSIC_CMD octave_cmd

#define octave_cmd 0xd0
/*octave: MACRO
    assert 1 <= (\1) && (\1) <= 8, "octave must be 1-8"
    db octave_cmd + 8 - (\1) // octave
ENDM*/

#define note_type_cmd 0xd8
/*note_type: MACRO
    db note_type_cmd
    db \1 // note length
    if _NARG >= 2
        if \3 < 0
            dn \2, 0b1000 | (\3 * -1) // volume envelope
        else
            dn \2, \3 // volume envelope
        endc
    endc
ENDM*/

// only valid on the noise channel
/*drum_speed: MACRO
    note_type \1 // note length
ENDM*/

#define transpose_cmd 0xd9
/*transpose: MACRO
    db transpose_cmd
    dn \1, \2 // num octaves, num pitches
ENDM*/

#define tempo_cmd 0xda
/*tempo: MACRO
    db tempo_cmd
    bigdw \1 // tempo
ENDM*/

#define duty_cycle_cmd 0xdb
/*duty_cycle: MACRO
    db duty_cycle_cmd
    db \1 // duty cycle
ENDM*/

#define volume_envelope_cmd 0xdc
/*volume_envelope: MACRO
    db volume_envelope_cmd
    if \2 < 0
        dn \1, 0b1000 | (\2 * -1) // volume envelope
    else
        dn \1, \2 // volume envelope
    endc
ENDM*/

#define pitch_sweep_cmd 0xdd
/*pitch_sweep: MACRO
    db pitch_sweep_cmd
    if \2 < 0
        dn \1, 0b1000 | (\2 * -1) // pitch sweep
    else
        dn \1, \2 // pitch sweep
    endc
ENDM*/

#define duty_cycle_pattern_cmd 0xde
/*duty_cycle_pattern: MACRO
    db duty_cycle_pattern_cmd
    db (\1 << 6) | (\2 << 4) | (\3 << 2) | (\4 << 0) // duty cycle pattern
ENDM*/

#define toggle_sfx_cmd 0xdf
/*toggle_sfx: MACRO
    db toggle_sfx_cmd
ENDM*/

#define pitch_slide_cmd 0xe0
/*pitch_slide: MACRO
    db pitch_slide_cmd
    db \1 - 1 // duration
    dn 8 - \2, \3 0b 12 // octave, pitch
ENDM*/

#define vibrato_cmd 0xe1
/*vibrato: MACRO
    db vibrato_cmd
    db \1 // delay
    if _NARG > 2
        dn \2, \3 // extent, rate
    else
        db \2 // LEGACY: Support for 1-arg extent
    endc
ENDM*/

#define unknownmusic0xe2_cmd 0xe2
/*unknownmusic0xe2: MACRO
    db unknownmusic0xe2_cmd
    db \1 // unknown
ENDM*/

#define toggle_noise_cmd 0xe3
/*toggle_noise: MACRO
    db toggle_noise_cmd
    if _NARG > 0
        db \1 // drum kit
    endc
ENDM*/

#define force_stereo_panning_cmd 0xe4
/*force_stereo_panning: MACRO
    db force_stereo_panning_cmd
    dn 0b1111 * (1 && \1), 0b1111 * (1 && \2) // left enable, right enable
ENDM*/

#define volume_cmd 0xe5
/*volume: MACRO
    db volume_cmd
    if _NARG > 1
        dn \1, \2 // left volume, right volume
    else
        db \1 // LEGACY: Support for 1-arg volume
    endc
ENDM*/

#define pitch_offset_cmd 0xe6
/*pitch_offset: MACRO
    db pitch_offset_cmd
    bigdw \1 // pitch offset
ENDM*/

#define unknownmusic0xe7_cmd 0xe7
/*unknownmusic0xe7: MACRO
    db unknownmusic0xe7_cmd
    db \1 // unknown
ENDM*/

#define unknownmusic0xe8_cmd 0xe8
/*unknownmusic0xe8: MACRO
    db unknownmusic0xe8_cmd
    db \1 // unknown
ENDM*/

#define tempo_relative_cmd 0xe9
/*tempo_relative: MACRO
    db tempo_relative_cmd
    bigdw \1 // tempo adjustment
ENDM*/

#define restart_channel_cmd 0xea
/*restart_channel: MACRO
    db restart_channel_cmd
    dw \1 // address
ENDM*/

#define new_song_cmd 0xeb
/*new_song: MACRO
    db new_song_cmd
    bigdw \1 // id
ENDM*/

#define sfx_priority_on_cmd 0xec
/*sfx_priority_on: MACRO
    db sfx_priority_on_cmd
ENDM*/

#define sfx_priority_off_cmd 0xed
/*sfx_priority_off: MACRO
    db sfx_priority_off_cmd
ENDM*/

#define unknownmusic0xee_cmd 0xee
/*unknownmusic0xee: MACRO
    db unknownmusic0xee_cmd
    dw \1 // address
ENDM*/

#define stereo_panning_cmd 0xef
/*stereo_panning: MACRO
    db stereo_panning_cmd
    dn 0b1111 * (1 && \1), 0b1111 * (1 && \2) // left enable, right enable
ENDM*/

#define sfx_toggle_noise_cmd 0xf0
/*sfx_toggle_noise: MACRO
    db sfx_toggle_noise_cmd
    if _NARG > 0
        db \1 // drum kit
    endc
ENDM*/

#define music0xf1_cmd 0xf1
/*music0xf1: MACRO
    db music0xf1_cmd
ENDM*/

#define music0xf2_cmd 0xf2
/*music0xf2: MACRO
    db music0xf2_cmd
ENDM*/

#define music0xf3_cmd 0xf3
/*music0xf3: MACRO
    db music0xf3_cmd
ENDM*/

#define music0xf4_cmd 0xf4
/*music0xf4: MACRO
    db music0xf4_cmd
ENDM*/

#define music0xf5_cmd 0xf5
/*music0xf5: MACRO
    db music0xf5_cmd
ENDM*/

#define music0xf6_cmd 0xf6
/*music0xf6: MACRO
    db music0xf6_cmd
ENDM*/

#define music0xf7_cmd 0xf7
/*music0xf7: MACRO
    db music0xf7_cmd
ENDM*/

#define music0xf8_cmd 0xf8
/*music0xf8: MACRO
    db music0xf8_cmd
ENDM*/

#define unknownmusic0xf9_cmd 0xf9
/*unknownmusic0xf9: MACRO
    db unknownmusic0xf9_cmd
ENDM*/

#define set_condition_cmd 0xfa
/*set_condition: MACRO
    db set_condition_cmd
    db \1 // condition
ENDM*/

#define sound_jump_if_cmd 0xfb
/*sound_jump_if: MACRO
    db sound_jump_if_cmd
    db \1 // condition
    dw \2 // address
ENDM*/

#define sound_jump_cmd 0xfc
/*sound_jump: MACRO
    db sound_jump_cmd
    dw \1 // address
ENDM*/

#define sound_loop_cmd 0xfd
/*sound_loop: MACRO
    db sound_loop_cmd
    db \1 // count
    dw \2 // address
ENDM*/

#define sound_call_cmd 0xfe
/*sound_call: MACRO
    db sound_call_cmd
    dw \1 // address
ENDM*/

#define sound_ret_cmd 0xff
#define sound_ret 0xff
/*sound_ret: MACRO
    db sound_ret_cmd
ENDM*/
