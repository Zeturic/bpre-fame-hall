#pragma once
#include "types.h"

// #define HALL_OF_FAME_MAX_TEAMS 50
#define HALL_OF_FAME_MAX_TEAMS 40

#define POKEMON_NAME_LENGTH 10
#define PARTY_SIZE 6

#include "constants/pokemon.h"
#include "constants/string-conversion-modes.h"
#include "constants/pokemon-data.h"
#include "constants/characters.h"
#include "constants/gender.h"

#include "structs.h"
#include "locations.h"
#include "functions.h"

#define tDontSaveData       data[0]
#define tDisplayedMonId     data[1]
#define tMonNumber          data[2]
#define tFrameCount         data[3]
#define tPlayerSpriteID     data[4]
#define tMonSpriteId(i)     data[i + 5]

#define tDestinationX  data[1]
#define tDestinationY  data[2]
#define tSpecies       data[7]

#define tCurrTeamNo     data[0]
#define tCurrPageNo     data[1]
#define tCurrMonId      data[2]
#define tMonNo          data[4]
// #define tMonSpriteId(i) data[i + 5]

#define RGB(r, g, b) ((r) | ((g) << 5) | ((b) << 10))

#define CpuCopy16(src, dest, size) CPU_COPY(src, dest, size, 16)
#define CPU_COPY(src, dest, size, bit) CpuSet(src, dest, CPU_SET_##bit##BIT | ((size)/(bit/8) & 0x1FFFFF))
#define CPU_SET_16BIT     0x00000000

#define GAME_STAT_ENTERED_HOF               10

#define unused __attribute__((unused))

_Static_assert(sizeof(struct HallofFameTeam) * HALL_OF_FAME_MAX_TEAMS <= 0x1770, "");