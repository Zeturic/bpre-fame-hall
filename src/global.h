#pragma once
#include "types.h"

#define HALL_OF_FAME_MAX_TEAMS 50

#define POKEMON_NAME_LENGTH 10
#define PARTY_SIZE 6

#include "constants/pokemon.h"

#include "structs.h"
#include "locations.h"
#include "functions.h"

#define tDontSaveData       data[0]
#define tDisplayedMonId     data[1]
#define tMonNumber          data[2]
#define tFrameCount         data[3]
#define tPlayerSpriteID     data[4]
#define tMonSpriteId(i)     data[i + 5]