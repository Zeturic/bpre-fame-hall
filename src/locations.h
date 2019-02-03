#pragma once
#include "types.h"
#include "structs.h"

extern const u8 gText_SavingDontTurnOffPower[];

extern u8 gDecompressionBuffer[];
extern bool8 gHasHallOfFameRecords;

extern struct HallofFameTeam *sHofMonPtr;

extern struct Task gTasks[];

extern const s16 sHallOfFame_MonFullTeamPositions[6][4];
extern const s16 sHallOfFame_MonHalfTeamPositions[3][4];

extern struct Sprite gSprites[];

extern u32 sHofFadingRelated;