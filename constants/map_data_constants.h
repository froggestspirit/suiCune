#define MAPGROUP_N_A -1
#define GROUP_N_A -1
#define MAP_N_A -1
#define MAPGROUP_NONE 0
#define GROUP_NONE 0
#define MAP_NONE 0

// map struct members (see data/maps/maps.asm)
enum {
    MAP_MAPATTRIBUTES_BANK,  // 0
    MAP_TILESET,             // 1
    MAP_ENVIRONMENT,         // 2
    MAP_MAPATTRIBUTES,       // 3
    MAP_LOCATION = 5,        // 5
    MAP_MUSIC,               // 6
    MAP_PALETTE,             // 7
    MAP_FISHGROUP,           // 8
    MAP_LENGTH,
};

// map environments (wEnvironment)
// EnvironmentColorsPointers indexes (see data/maps/environment_colors.asm)
enum {
    TOWN = 1,
    ROUTE,
    INDOOR,
    CAVE,
    ENVIRONMENT_5,
    GATE,
    DUNGEON,
};
#define NUM_ENVIRONMENTS DUNGEON

// map palettes (wEnvironment)
enum {
    PALETTE_AUTO,
    PALETTE_DAY,
    PALETTE_NITE,
    PALETTE_MORN,
    PALETTE_DARK,
    NUM_MAP_PALETTES,
};

// FishGroups indexes (see data/wild/fish.asm)
enum {
    FISHGROUP_NONE,
    FISHGROUP_SHORE,
    FISHGROUP_OCEAN,
    FISHGROUP_LAKE,
    FISHGROUP_POND,
    FISHGROUP_DRATINI,
    FISHGROUP_QWILFISH_SWARM,
    FISHGROUP_REMORAID_SWARM,
    FISHGROUP_GYARADOS,
    FISHGROUP_DRATINI_2,
    FISHGROUP_WHIRL_ISLANDS,
    FISHGROUP_QWILFISH,
    FISHGROUP_REMORAID,
    FISHGROUP_QWILFISH_NO_SWARM,
};

#define NUM_FISHGROUPS FISHGROUP_QWILFISH_NO_SWARM

// connection directions (see data/maps/data.asm)
enum {
    EAST_F,
    WEST_F,
    SOUTH_F,
    NORTH_F,
};

// wMapConnections
enum {
    EAST = 1,
    WEST = 2,
    SOUTH = 4,
    NORTH = 8,
};

// SpawnPoints indexes (see data/maps/spawn_points.asm)
enum {
    SPAWN_HOME,
    SPAWN_DEBUG,
    // kanto
    SPAWN_PALLET,
    SPAWN_VIRIDIAN,
    SPAWN_PEWTER,
    SPAWN_CERULEAN,
    SPAWN_ROCK_TUNNEL,
    SPAWN_VERMILION,
    SPAWN_LAVENDER,
    SPAWN_SAFFRON,
    SPAWN_CELADON,
    SPAWN_FUCHSIA,
    SPAWN_CINNABAR,
    SPAWN_INDIGO,
    // johto
    SPAWN_NEW_BARK,
    SPAWN_CHERRYGROVE,
    SPAWN_VIOLET,
    SPAWN_UNION_CAVE,
    SPAWN_AZALEA,
    SPAWN_CIANWOOD,
    SPAWN_GOLDENROD,
    SPAWN_OLIVINE,
    SPAWN_ECRUTEAK,
    SPAWN_MAHOGANY,
    SPAWN_LAKE_OF_RAGE,
    SPAWN_BLACKTHORN,
    SPAWN_MT_SILVER,
    SPAWN_FAST_SHIP,
    NUM_SPAWNS,
};

#define SPAWN_N_A -1

// Flypoints indexes (see data/maps/flypoints.asm)
enum {
    // johto
    FLY_NEW_BARK,
    FLY_CHERRYGROVE,
    FLY_VIOLET,
    FLY_AZALEA,
    FLY_GOLDENROD,
    FLY_ECRUTEAK,
    FLY_OLIVINE,
    FLY_CIANWOOD,
    FLY_MAHOGANY,
    FLY_LAKE_OF_RAGE,
    FLY_BLACKTHORN,
    FLY_MT_SILVER,
    // kanto
    FLY_PALLET,
    FLY_VIRIDIAN,
    FLY_PEWTER,
    FLY_CERULEAN,
    FLY_VERMILION,
    FLY_ROCK_TUNNEL,
    FLY_LAVENDER,
    FLY_CELADON,
    FLY_SAFFRON,
    FLY_FUCHSIA,
    FLY_CINNABAR,
    FLY_INDIGO,
    NUM_FLYPOINTS,
};

#define JOHTO_FLYPOINT FLY_NEW_BARK
#define KANTO_FLYPOINT FLY_PALLET

#define MAX_OUTDOOR_SPRITES 23  // see engine/overworld/overworld.asm
