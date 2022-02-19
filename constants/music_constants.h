

// song ids
// Music indexes (see audio/music_pointers.asm)
enum {
    MUSIC_NONE = 0,
    MUSIC_TITLE,                         // 01
    MUSIC_ROUTE_1,                       // 02
    MUSIC_ROUTE_3,                       // 03
    MUSIC_ROUTE_12,                      // 04
    MUSIC_MAGNET_TRAIN,                  // 05
    MUSIC_KANTO_GYM_LEADER_BATTLE,       // 06
    MUSIC_KANTO_TRAINER_BATTLE,          // 07
    MUSIC_KANTO_WILD_BATTLE,             // 08
    MUSIC_POKEMON_CENTER,                // 09
    MUSIC_HIKER_ENCOUNTER,               // 0a
    MUSIC_LASS_ENCOUNTER,                // 0b
    MUSIC_OFFICER_ENCOUNTER,             // 0c
    MUSIC_HEAL,                          // 0d
    MUSIC_LAVENDER_TOWN,                 // 0e
    MUSIC_ROUTE_2,                       // 0f
    MUSIC_MT_MOON,                       // 10
    MUSIC_SHOW_ME_AROUND,                // 11
    MUSIC_GAME_CORNER,                   // 12
    MUSIC_BICYCLE,                       // 13
    MUSIC_HALL_OF_FAME,                  // 14
    MUSIC_VIRIDIAN_CITY,                 // 15
    MUSIC_CELADON_CITY,                  // 16
    MUSIC_TRAINER_VICTORY,               // 17
    MUSIC_WILD_VICTORY,                  // 18
    MUSIC_GYM_VICTORY,                   // 19
    MUSIC_MT_MOON_SQUARE,                // 1a
    MUSIC_GYM,                           // 1b
    MUSIC_PALLET_TOWN,                   // 1c
    MUSIC_POKEMON_TALK,                  // 1d
    MUSIC_PROF_OAK,                      // 1e
    MUSIC_RIVAL_ENCOUNTER,               // 1f
    MUSIC_RIVAL_AFTER,                   // 20
    MUSIC_SURF,                          // 21
    MUSIC_EVOLUTION,                     // 22
    MUSIC_NATIONAL_PARK,                 // 23
    MUSIC_CREDITS,                       // 24
    MUSIC_AZALEA_TOWN,                   // 25
    MUSIC_CHERRYGROVE_CITY,              // 26
    MUSIC_KIMONO_ENCOUNTER,              // 27
    MUSIC_UNION_CAVE,                    // 28
    MUSIC_JOHTO_WILD_BATTLE,             // 29
    MUSIC_JOHTO_TRAINER_BATTLE,          // 2a
    MUSIC_ROUTE_30,                      // 2b
    MUSIC_ECRUTEAK_CITY,                 // 2c
    MUSIC_VIOLET_CITY,                   // 2d
    MUSIC_JOHTO_GYM_LEADER_BATTLE,       // 2e
    MUSIC_CHAMPION_BATTLE,               // 2f
    MUSIC_RIVAL_BATTLE,                  // 30
    MUSIC_ROCKET_BATTLE,                 // 31
    MUSIC_PROF_ELM,                      // 32
    MUSIC_DARK_CAVE,                     // 33
    MUSIC_ROUTE_29,                      // 34
    MUSIC_ROUTE_36,                      // 35
    MUSIC_SS_AQUA,                       // 36
    MUSIC_YOUNGSTER_ENCOUNTER,           // 37
    MUSIC_BEAUTY_ENCOUNTER,              // 38
    MUSIC_ROCKET_ENCOUNTER,              // 39
    MUSIC_POKEMANIAC_ENCOUNTER,          // 3a
    MUSIC_SAGE_ENCOUNTER,                // 3b
    MUSIC_NEW_BARK_TOWN,                 // 3c
    MUSIC_GOLDENROD_CITY,                // 3d
    MUSIC_VERMILION_CITY,                // 3e
    MUSIC_POKEMON_CHANNEL,               // 3f
    MUSIC_POKE_FLUTE_CHANNEL,            // 40
    MUSIC_TIN_TOWER,                     // 41
    MUSIC_SPROUT_TOWER,                  // 42
    MUSIC_BURNED_TOWER,                  // 43
    MUSIC_LIGHTHOUSE,                    // 44
    MUSIC_LAKE_OF_RAGE,                  // 45
    MUSIC_INDIGO_PLATEAU,                // 46
    MUSIC_ROUTE_37,                      // 47
    MUSIC_ROCKET_HIDEOUT,                // 48
    MUSIC_DRAGONS_DEN,                   // 49
    MUSIC_JOHTO_WILD_BATTLE_NIGHT,       // 4a
    MUSIC_RUINS_OF_ALPH_RADIO,           // 4b
    MUSIC_CAPTURE,                       // 4c
    MUSIC_ROUTE_26,                      // 4d
    MUSIC_MOM,                           // 4e
    MUSIC_VICTORY_ROAD,                  // 4f
    MUSIC_POKEMON_LULLABY,               // 50
    MUSIC_POKEMON_MARCH,                 // 51
    MUSIC_GS_OPENING,                    // 52
    MUSIC_GS_OPENING_2,                  // 53
    MUSIC_MAIN_MENU,                     // 54
    MUSIC_RUINS_OF_ALPH_INTERIOR,        // 55
    MUSIC_ROCKET_OVERTURE,               // 56
    MUSIC_DANCING_HALL,                  // 57
    MUSIC_BUG_CATCHING_CONTEST_RANKING,  // 58
    MUSIC_BUG_CATCHING_CONTEST,          // 59
    MUSIC_LAKE_OF_RAGE_ROCKET_RADIO,     // 5a
    MUSIC_PRINTER,                       // 5b
    MUSIC_POST_CREDITS,                  // 5c
                                         // new to Crystal
    MUSIC_CLAIR,                         // 5d
    MUSIC_MOBILE_ADAPTER_MENU,           // 5e
    MUSIC_MOBILE_ADAPTER,                // 5f
    MUSIC_BUENAS_PASSWORD,               // 60
    MUSIC_MYSTICALMAN_ENCOUNTER,         // 61
    MUSIC_CRYSTAL_OPENING,               // 62
    MUSIC_BATTLE_TOWER_THEME,            // 63
    MUSIC_SUICUNE_BATTLE,                // 64
    MUSIC_BATTLE_TOWER_LOBBY,            // 65
    MUSIC_MOBILE_CENTER,                 // 66
    NUM_MUSIC_SONGS,
};

// GetMapMusic picks music for this value (see home/map.asm)
#define MUSIC_MAHOGANY_MART 0x64

// ExitPokegearRadio_HandleMusic uses these values
#define RESTART_MAP_MUSIC 0xfe
#define ENTER_MAP_MUSIC 0xff

// GetMapMusic picks music for this bit flag
#define RADIO_TOWER_MUSIC_F 7
#define RADIO_TOWER_MUSIC (1 << RADIO_TOWER_MUSIC_F)
