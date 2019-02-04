#pragma once
#include "types.h"

#define packed __attribute__((packed))
#define aligned(x) __attribute__((aligned(x)))

// struct packed HallofFameMon {
//     u32 tid;
//     u32 personality;
//     u16 species : 9;
//     u16 lvl : 7;
//     u8 nick[POKEMON_NAME_LENGTH];
// };

struct packed aligned(4) HallofFameMon {
    u32 tid;
    u32 personality;
    u16 species;
    u8 lvl;
    u8 nick[POKEMON_NAME_LENGTH];
};

struct packed HallofFameTeam {
    struct HallofFameMon mon[PARTY_SIZE];
};

struct packed Task {
    void (*func)(u8 taskId);
    bool8 isActive;
    u8 prev;
    u8 next;
    u8 priority;
    s16 data[16];
};

struct packed OamData {
    /*0x00*/ u32 y : 8;
    /*0x01*/ u32 affineMode : 2;  // 0x1, 0x2 = 0x3
    u32 objMode : 2;              // 0x4, 0x8 = 0xC
    u32 mosaic : 1;               // 0x10
    u32 bpp : 1;                  // 0x20
    u32 shape : 2;                // 0x40, 0x80

    /*0x02*/ u32 x : 9;
    u32 matrixNum : 5;  // bits 3/4 are h-flip/v-flip if not in affine mode
    u32 size : 2;

    /*0x04*/ u16 tileNum : 10;
    u16 priority : 2;
    u16 paletteNum : 4;
    /*0x06*/ u16 affineParam;
};

struct packed Sprite {
    struct OamData oam;
    u8 filler_8[0x14];
    void (*callback)(struct Sprite *);
    u8 filler_20[0xE];
    // general purpose data fields
    s16 data[8];
    u8 filler_3E[0x6];
};

struct packed Pokemon {
    u8 filler_0[100];
};

struct TextPrinterTemplate;

// _Static_assert(sizeof(struct Task) == 0x28, "");
// _Static_assert(sizeof(struct Sprite) == 0x44, "");
// _Static_assert(sizeof(struct OamData) == 0x8, "");