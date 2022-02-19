// collision permissions (see data/collision/collision_permissions.asm)
#define LAND_TILE 0x00
#define WATER_TILE 0x01
#define WALL_TILE 0x0f
#define TALK 0x10

// collision data types (see data/tilesets/*_collision.asm)
// TileCollisionTable indexes (see data/collision/collision_permissions.asm)
#define COLL_FLOOR 0x00
#define COLL_01 0x01  // garbage
#define COLL_03 0x03  // garbage
#define COLL_04 0x04  // garbage
#define COLL_WALL 0x07
#define COLL_CUT_08 0x08         // unused
#define COLL_TALL_GRASS_10 0x10  // unused
#define COLL_CUT_TREE 0x12
#define COLL_LONG_GRASS 0x14
#define COLL_HEADBUTT_TREE 0x15
#define COLL_TALL_GRASS 0x18
#define COLL_CUT_TREE_1A 0x1a       // unused
#define COLL_LONG_GRASS_1C 0x1c     // unused
#define COLL_HEADBUTT_TREE_1D 0x1d  // unused
#define COLL_WATER_21 0x21          // unused
#define COLL_ICE 0x23
#define COLL_WHIRLPOOL 0x24
#define COLL_BUOY 0x27
#define COLL_CUT_28 0x28  // garbage
#define COLL_WATER 0x29
#define COLL_ICE_2B 0x2b           // unused
#define COLL_WHIRLPOOL_2C 0x2c     // unused
#define COLL_WATERFALL_RIGHT 0x30  // unused
#define COLL_WATERFALL_LEFT 0x31   // unused
#define COLL_WATERFALL_UP 0x32     // unused
#define COLL_WATERFALL 0x33
#define COLL_CURRENT_RIGHT 0x38   // unused
#define COLL_CURRENT_LEFT 0x39    // unused
#define COLL_CURRENT_UP 0x3a      // unused
#define COLL_CURRENT_DOWN 0x3b    // unused
#define COLL_BRAKE 0x40           // unused
#define COLL_WALK_RIGHT 0x41      // unused
#define COLL_WALK_LEFT 0x42       // unused
#define COLL_WALK_UP 0x43         // unused
#define COLL_WALK_DOWN 0x44       // unused
#define COLL_BRAKE_45 0x45        // garbage
#define COLL_BRAKE_46 0x46        // unused
#define COLL_BRAKE_47 0x47        // unused
#define COLL_GRASS_48 0x48        // unused
#define COLL_GRASS_49 0x49        // unused
#define COLL_GRASS_4A 0x4a        // garbage
#define COLL_GRASS_4B 0x4b        // garbage
#define COLL_GRASS_4C 0x4c        // unused
#define COLL_WALK_RIGHT_ALT 0x50  // unused
#define COLL_WALK_LEFT_ALT 0x51   // unused
#define COLL_WALK_UP_ALT 0x52     // unused
#define COLL_WALK_DOWN_ALT 0x53   // unused
#define COLL_BRAKE_ALT 0x54       // unused
#define COLL_BRAKE_55 0x55        // unused
#define COLL_BRAKE_56 0x56        // unused
#define COLL_BRAKE_57 0x57        // unused
#define COLL_5B 0x5b              // garbage
#define COLL_PIT 0x60
#define COLL_VIRTUAL_BOY 0x61  // garbage
#define COLL_64 0x64           // garbage
#define COLL_65 0x65           // garbage
#define COLL_PIT_68 0x68       // unused
#define COLL_WARP_CARPET_DOWN 0x70
#define COLL_DOOR 0x71
#define COLL_LADDER 0x72
#define COLL_STAIRCASE_73 0x73  // unused
#define COLL_CAVE_74 0x74       // unused
#define COLL_DOOR_75 0x75       // unused
#define COLL_WARP_CARPET_LEFT 0x76
#define COLL_WARP_77 0x77  // unused
#define COLL_WARP_CARPET_UP 0x78
#define COLL_DOOR_79 0x79  // unused
#define COLL_STAIRCASE 0x7a
#define COLL_CAVE 0x7b
#define COLL_WARP_PANEL 0x7c
#define COLL_DOOR_7D 0x7d  // unused
#define COLL_WARP_CARPET_RIGHT 0x7e
#define COLL_WARP_7F 0x7f  // unused
#define COLL_COUNTER 0x90
#define COLL_BOOKSHELF 0x91
#define COLL_PC 0x93
#define COLL_RADIO 0x94
#define COLL_TOWN_MAP 0x95
#define COLL_MART_SHELF 0x96
#define COLL_TV 0x97
#define COLL_COUNTER_98 0x98  // unused
#define COLL_9C 0x9c          // garbage
#define COLL_WINDOW 0x9d
#define COLL_INCENSE_BURNER 0x9f
#define COLL_HOP_RIGHT 0xa0
#define COLL_HOP_LEFT 0xa1
#define COLL_HOP_UP 0xa2  // unused
#define COLL_HOP_DOWN 0xa3
#define COLL_HOP_DOWN_RIGHT 0xa4
#define COLL_HOP_DOWN_LEFT 0xa5
#define COLL_HOP_UP_RIGHT 0xa6  // unused
#define COLL_HOP_UP_LEFT 0xa7   // unused
#define COLL_RIGHT_WALL 0xb0
#define COLL_LEFT_WALL 0xb1
#define COLL_UP_WALL 0xb2
#define COLL_DOWN_WALL 0xb3        // unused
#define COLL_DOWN_RIGHT_WALL 0xb4  // unused
#define COLL_DOWN_LEFT_WALL 0xb5   // unused
#define COLL_UP_RIGHT_WALL 0xb6    // unused
#define COLL_UP_LEFT_WALL 0xb7     // unused
#define COLL_RIGHT_BUOY 0xc0       // unused
#define COLL_LEFT_BUOY 0xc1        // unused
#define COLL_UP_BUOY 0xc2          // unused
#define COLL_DOWN_BUOY 0xc3        // unused
#define COLL_DOWN_RIGHT_BUOY 0xc4  // unused
#define COLL_DOWN_LEFT_BUOY 0xc5   // unused
#define COLL_UP_RIGHT_BUOY 0xc6    // unused
#define COLL_UP_LEFT_BUOY 0xc7     // unused
#define COLL_FF 0xff               // garbage

// collision data type nybbles
#define LO_NYBBLE_GRASS 0x07
#define HI_NYBBLE_TALL_GRASS 0x10
#define HI_NYBBLE_WATER 0x20
#define HI_NYBBLE_CURRENT 0x30
#define HI_NYBBLE_WALK 0x40
#define HI_NYBBLE_WALK_ALT 0x50
#define HI_NYBBLE_WARPS 0x70
#define HI_NYBBLE_LEDGES 0xa0
#define HI_NYBBLE_SIDE_WALLS 0xb0
#define HI_NYBBLE_SIDE_BUOYS 0xc0
