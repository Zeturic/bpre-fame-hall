#pragma once
#include "types.h"

#define packed __attribute__((packed))

struct packed HallofFameMon {
    u32 tid;
    u32 personality;
    u16 species:9;
    u16 lvl:7;
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

struct TextPrinterTemplate;

// _Static_assert(sizeof(struct Task) == 0x28, "");