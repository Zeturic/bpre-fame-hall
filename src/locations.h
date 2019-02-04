#pragma once
#include "types.h"
#include "structs.h"

extern const u8 gText_SavingDontTurnOffPower[];
extern const u8 gText_HOFNumber[];
extern const u8 gText_PickCancel[];
extern const u8 gText_PickNextCancel[];
extern const u8 gText_IDNumber[];
extern const u8 gText_Level[];
extern const u8 gText_Number[];

extern u8 gDecompressionBuffer[];
extern bool8 gHasHallOfFameRecords;

extern struct HallofFameTeam *sHofMonPtr;

extern struct Task gTasks[];

extern const s16 sHallOfFame_MonFullTeamPositions[6][4];
extern const s16 sHallOfFame_MonHalfTeamPositions[3][4];

extern struct Sprite gSprites[];

extern u32 sHofFadingRelated;

extern u8 gStringVar1[];
extern u8 gStringVar4[];

extern struct Pokemon gPlayerParty[PARTY_SIZE];

extern const u8 sUnknown_0840C23C[];

extern const u8 gSpeciesNames[][POKEMON_NAME_LENGTH + 1];