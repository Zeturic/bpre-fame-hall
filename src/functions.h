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

void short_call Task_Hof_InitTeamSaveData(u8 taskId);
void short_call CB2_DoHallOfFameScreen(void);