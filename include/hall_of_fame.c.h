#pragma once

#include "hall_of_fame.h"
#include "sprite.h"

// #define HALL_OF_FAME_MAX_TEAMS 50
#define HALL_OF_FAME_MAX_TEAMS 40

#define HALL_OF_FAME_BG_PAL    (RGB(22, 24, 29))

// struct HallofFameMon
// {
//     u32 tid;
//     u32 personality;
//     u16 species:9;
//     u16 lvl:7;
//     u8 nick[10];
// };

struct HallofFameMon
{
    u32 tid;
    u32 personality;
    u16 species;
    u8 lvl;
    u8 nick[10];
};

struct HallofFameTeam
{
    struct HallofFameMon mon[PARTY_SIZE];
};

_Static_assert(sizeof(struct HallofFameTeam) * HALL_OF_FAME_MAX_TEAMS <= 0x1770, "");

extern struct HallofFameTeam * sHofMonPtr;

extern const s16 sHallOfFame_MonFullTeamPositions[6][4];
extern const s16 sHallOfFame_MonHalfTeamPositions[3][4];

extern u32 sSelectedPaletteIndices;

extern const u8 sTextColors[][4];

bool8 InitHallOfFameScreen(void);
void Task_Hof_InitMonData(u8 taskId);
void Task_Hof_TrySaveData(u8 taskId);
void SpriteCB_GetOnScreen(struct Sprite * sprite);
void Task_Hof_PlayMonCryAndPrintInfo(u8 taskId);
void HallOfFame_PrintMonInfo(struct HallofFameMon* currMon, u8 unused1, u8 unused2);
void Task_Hof_TryDisplayAnotherMon(u8 taskId);
void Task_Hof_PaletteFadeAndPrintWelcomeText(u8 taskId);
void Task_HofPC_DrawSpritesPrintText(u8 taskId);
void Task_HofPC_PrintDataIsCorrupted(u8 taskId);
void Task_HofPC_PrintMonInfo(u8 taskId);
void Task_HofPC_HandleInput(u8 taskId);
void Task_Hof_StartDisplayingMons(u8 taskId);
