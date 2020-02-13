#pragma once

#include "gba/gba.h"
#include "constants/global.h"
#include "constants/game_stat.h"

#include "std/string.h"

#define PACKED __attribute__((packed))
#define ALIGNED(x) __attribute__((aligned(x)))
#define UNUSED __attribute__((unused))

struct Pokemon;

struct Coords16
{
    s16 x;
    s16 y;
};
