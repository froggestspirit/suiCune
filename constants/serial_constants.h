// wLinkMode
enum {
    LINK_NULL,         // 0
    LINK_TIMECAPSULE,  // 1
    LINK_TRADECENTER,  // 2
    LINK_COLOSSEUM,    // 3
    LINK_MOBILE,       // 4
};

// hSerialReceive high nybbles
#define SERIAL_TIMECAPSULE 0x60
#define SERIAL_TRADECENTER 0x70
#define SERIAL_BATTLE 0x80

#define ESTABLISH_CONNECTION_WITH_INTERNAL_CLOCK 0x01
#define ESTABLISH_CONNECTION_WITH_EXTERNAL_CLOCK 0x02

#define START_TRANSFER_EXTERNAL_CLOCK 0x80  // 1 << rSC_ON
#define START_TRANSFER_INTERNAL_CLOCK 0x81  // (1 << rSC_ON) | 1

// hSerialConnectionStatus
#define USING_EXTERNAL_CLOCK 0x01
#define USING_INTERNAL_CLOCK 0x02
#define CONNECTION_NOT_ESTABLISHED 0xff

// length of a patch list (less than any of the signal bytes)
#define SERIAL_PATCH_LIST_LENGTH 0xfc
// signals the start of an array of bytes transferred over the link cable
#define SERIAL_PREAMBLE_BYTE 0xfd
// this byte is used when there is no data to send
#define SERIAL_NO_DATA_BYTE 0xfe
// signals the end of one part of a patch list (there are two parts) for player/enemy party data
#define SERIAL_PATCH_LIST_PART_TERMINATOR 0xff
// used to replace SERIAL_NO_DATA_BYTE
#define SERIAL_PATCH_REPLACEMENT_BYTE 0xff

#define SERIAL_PREAMBLE_LENGTH 6
#define SERIAL_RN_PREAMBLE_LENGTH 7
#define SERIAL_RNS_LENGTH 10

#define SERIAL_MAIL_PREAMBLE_BYTE 0x20
#define SERIAL_MAIL_REPLACEMENT_BYTE 0x21
#define SERIAL_MAIL_PREAMBLE_LENGTH 5

// timeout duration after exchanging a byte
#define SERIAL_LINK_BYTE_TIMEOUT 0x5000

#define MAX_MYSTERY_GIFT_PARTNERS 5
