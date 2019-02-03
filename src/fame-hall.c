#include "global.h"

void Task_Hof_InitTeamSaveData(u8 taskId) {
    u16 i;
    struct HallofFameTeam *lastSavedTeam = (struct HallofFameTeam *)(gDecompressionBuffer);

    sub_8112450();

    if (!gHasHallOfFameRecords) {
        memset(gDecompressionBuffer, 0, 0x2000);
    } else {
        if (Save_LoadGameData(3) != TRUE)
            memset(gDecompressionBuffer, 0, 0x2000);
    }

    for (i = 0; i < HALL_OF_FAME_MAX_TEAMS; i++, lastSavedTeam++) {
        if (lastSavedTeam->mon[0].species == SPECIES_NONE)
            break;
    }
    if (i >= HALL_OF_FAME_MAX_TEAMS) {
        struct HallofFameTeam *afterTeam = (struct HallofFameTeam *)(gDecompressionBuffer);
        struct HallofFameTeam *beforeTeam = (struct HallofFameTeam *)(gDecompressionBuffer);
        afterTeam++;
        for (i = 0; i < HALL_OF_FAME_MAX_TEAMS - 1; i++, beforeTeam++, afterTeam++) {
            *beforeTeam = *afterTeam;
        }
        lastSavedTeam--;
    }
    *lastSavedTeam = *sHofMonPtr;

    NewMenuHelpers_DrawDialogueFrame(0, 0);
    AddTextPrinterParameterized2(0, 1, gText_SavingDontTurnOffPower, 0, NULL, 2, 1, 3);
    CopyWindowToVram(0, 3);
    gTasks[taskId].func = Task_Hof_TrySaveData;
}