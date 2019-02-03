#pragma once
#include "types.h"
#include "structs.h"

#define short_call __attribute__((short_call))

void* memset(void* ptr, u8 value, u32 num);
u8 Save_LoadGameData(u8 a1);
void NewMenuHelpers_DrawDialogueFrame(u8, u8);
u16 AddTextPrinterParameterized2(u8 windowId, u8 fontId, const u8 *str, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16), u8 fgColor, u8 bgColor, u8 shadowColor);
void CopyWindowToVram(u8 windowId, u8 mode);
void Task_Hof_TrySaveData(u8 taskId);
void sub_8112450(void);
void Task_Hof_InitMonData(u8 taskId);
void *AllocZeroed(u32 size);
bool8 InitHallOfFameScreen(void);
u8 CreateTask(void (*func)(u8 taskId), u8 priority);
void SpriteCB_GetOnScreenAndAnimate(struct Sprite *sprite);
u16 CreatePicSprite2(u16 species, u32 otId, u32 personality, u8 flags, s16 x, s16 y, u8 paletteSlot, u16 paletteTag);
void DeleteWindow(u8 windowId, bool8 copyToVram);
void PlayCry1(u16 species, s8 pan);
void HallOfFame_PrintMonInfo(struct HallofFameMon* currMon, u8 unused1, u8 unused2);
void Task_Hof_PaletteFadeAndPrintWelcomeText(u8 taskId);
bool8 BeginNormalPaletteFade(u32, s8, u8, u8, u16);
void Task_HofPC_PrintDataIsCorrupted(u8 taskId);
void CpuSet(const void *src, void *dest, u32 control);
u32 GetGameStat(u8 index);
u8 HofPC_CreateWindow(u8 bg, u8 xPos, u8 yPos, u8 palette, u16 baseTile);
void Task_HofPC_PrintMonInfo(u8 taskId);
void BlendPalettes(u32 selectedPalettes, u8 coeff, u16 color);
u8 *StringExpandPlaceholders(u8 *dest, const u8 *src);
u8 *ConvertIntToDecimalStringN(u8 *dest, s32 value, u8 mode, u8 n);
void HofPC_PutText(const u8 *string, const u8 *string2, u8 a3, u8 a4, bool8 copyToVram);

void short_call CB2_DoHallOfFameScreen(void);
void short_call Task_Hof_InitTeamSaveData(u8 taskId);
void short_call Task_Hof_DisplayMon(u8 taskId);
void short_call Task_Hof_PrintMonInfoAfterAnimating(u8 taskId);
void short_call Task_Hof_TryDisplayAnotherMon(u8 taskId);
void short_call Task_HofPC_CopySaveData(u8 taskId);
void short_call Task_HofPC_DrawSpritesPrintText(u8 taskId);