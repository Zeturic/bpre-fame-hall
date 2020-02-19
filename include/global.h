#pragma once

#include "gba/gba.h"
#include "constants/global.h"
#include "constants/game_stat.h"

#include "std/string.h"

#define UNUSED __attribute__((unused))

struct Pokemon;

struct Coords16
{
    s16 x;
    s16 y;
};
