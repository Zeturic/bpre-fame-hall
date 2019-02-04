#include "global.h"

void CB2_DoHallOfFameScreen(void) {
    if (!InitHallOfFameScreen()) {
        u8 taskId = CreateTask(Task_Hof_InitMonData, 0);
        gTasks[taskId].tDontSaveData = FALSE;
        sHofMonPtr = AllocZeroed(sizeof(*sHofMonPtr));
    }
}

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

void Task_Hof_DisplayMon(u8 taskId) {
    u8 spriteId;
    s16 xPos, yPos, field4, field6;

    u16 currMonId = gTasks[taskId].tDisplayedMonId;
    struct HallofFameMon *currMon = &sHofMonPtr->mon[currMonId];

    if (gTasks[taskId].tMonNumber > 3) {
        xPos = sHallOfFame_MonFullTeamPositions[currMonId][0];
        yPos = sHallOfFame_MonFullTeamPositions[currMonId][1];
        field4 = sHallOfFame_MonFullTeamPositions[currMonId][2];
        field6 = sHallOfFame_MonFullTeamPositions[currMonId][3];
    } else {
        xPos = sHallOfFame_MonHalfTeamPositions[currMonId][0];
        yPos = sHallOfFame_MonHalfTeamPositions[currMonId][1];
        field4 = sHallOfFame_MonHalfTeamPositions[currMonId][2];
        field6 = sHallOfFame_MonHalfTeamPositions[currMonId][3];
    }

    // if (currMon->species == SPECIES_EGG)
    //     field6 += 10;

    spriteId = CreatePicSprite2(currMon->species, currMon->tid, currMon->personality, 1, xPos, yPos, currMonId, 0xFFFF);
    gSprites[spriteId].tDestinationX = field4;
    gSprites[spriteId].tDestinationY = field6;
    gSprites[spriteId].data[0] = 0;
    // gSprites[spriteId].tSpecies = currMon->species;
    gSprites[spriteId].callback = SpriteCB_GetOnScreenAndAnimate;
    gTasks[taskId].tMonSpriteId(currMonId) = spriteId;
    DeleteWindow(0, TRUE);
    gTasks[taskId].func = Task_Hof_PrintMonInfoAfterAnimating;
}

void Task_Hof_PrintMonInfoAfterAnimating(u8 taskId) {
    u16 currMonId = gTasks[taskId].tDisplayedMonId;
    struct HallofFameMon *currMon = &sHofMonPtr->mon[currMonId];
    struct Sprite *monSprite = &gSprites[gTasks[taskId].tMonSpriteId(currMonId)];

    if (monSprite->data[0]) {
        if (currMon->species != SPECIES_EGG)
            PlayCry1(currMon->species, 0);

        HallOfFame_PrintMonInfo(currMon, 0, 14);
        gTasks[taskId].tFrameCount = 120;
        gTasks[taskId].func = Task_Hof_TryDisplayAnotherMon;
    }
}

void Task_Hof_TryDisplayAnotherMon(u8 taskId) {
    u16 currPokeID = gTasks[taskId].tDisplayedMonId;
    struct HallofFameMon *currMon = &sHofMonPtr->mon[currPokeID];

    if (gTasks[taskId].tFrameCount != 0) {
        gTasks[taskId].tFrameCount--;
    } else {
        sHofFadingRelated |= (0x10000 << gSprites[gTasks[taskId].tMonSpriteId(currPokeID)].oam.paletteNum);
        if (gTasks[taskId].tDisplayedMonId <= 4 && currMon[1].species != SPECIES_NONE)  // there is another pokemon to display
        {
            gTasks[taskId].tDisplayedMonId++;
            BeginNormalPaletteFade(sHofFadingRelated, 0, 12, 12, RGB(22, 24, 29));
            gSprites[gTasks[taskId].tMonSpriteId(currPokeID)].oam.priority = 1;
            gTasks[taskId].func = Task_Hof_DisplayMon;
        } else {
            gTasks[taskId].func = Task_Hof_PaletteFadeAndPrintWelcomeText;
        }
    }
}

void Task_HofPC_CopySaveData(u8 taskId) {
    HofPC_CreateWindow(0, 0x1E, 0, 0xC, 0x226);
    if (Save_LoadGameData(3) != 1) {
        gTasks[taskId].func = Task_HofPC_PrintDataIsCorrupted;
    } else {
        u16 i;
        struct HallofFameTeam *savedTeams;

        CpuCopy16(gDecompressionBuffer, sHofMonPtr, 0x2000);
        savedTeams = sHofMonPtr;
        for (i = 0; i < HALL_OF_FAME_MAX_TEAMS; i++, savedTeams++) {
            if (savedTeams->mon[0].species == SPECIES_NONE)
                break;
        }

        if (i < HALL_OF_FAME_MAX_TEAMS)
            gTasks[taskId].tCurrTeamNo = i - 1;
        else
            gTasks[taskId].tCurrTeamNo = HALL_OF_FAME_MAX_TEAMS - 1;

        gTasks[taskId].tCurrPageNo = GetGameStat(GAME_STAT_ENTERED_HOF);

        gTasks[taskId].func = Task_HofPC_DrawSpritesPrintText;
    }
}

void Task_HofPC_DrawSpritesPrintText(u8 taskId) {
    struct HallofFameTeam *savedTeams = sHofMonPtr;
    struct HallofFameMon *currMon;
    u16 i;

    for (i = 0; i < gTasks[taskId].tCurrTeamNo; i++)
        savedTeams++;

    currMon = &savedTeams->mon[0];
    sHofFadingRelated = 0;
    gTasks[taskId].tCurrMonId = 0;
    gTasks[taskId].tMonNo = 0;

    for (i = 0; i < PARTY_SIZE; i++, currMon++) {
        if (currMon->species != 0)
            gTasks[taskId].tMonNo++;
    }

    currMon = &savedTeams->mon[0];

    for (i = 0; i < PARTY_SIZE; i++, currMon++) {
        if (currMon->species != 0) {
            u16 spriteId;
            s16 posX, posY;

            if (gTasks[taskId].tMonNo > 3) {
                posX = sHallOfFame_MonFullTeamPositions[i][2];
                posY = sHallOfFame_MonFullTeamPositions[i][3];
            } else {
                posX = sHallOfFame_MonHalfTeamPositions[i][2];
                posY = sHallOfFame_MonHalfTeamPositions[i][3];
            }

            if (currMon->species == SPECIES_EGG)
                posY += 10;

            spriteId = CreatePicSprite2(currMon->species, currMon->tid, currMon->personality, 1, posX, posY, i, 0xFFFF);
            gSprites[spriteId].oam.priority = 1;
            gTasks[taskId].tMonSpriteId(i) = spriteId;
        } else {
            gTasks[taskId].tMonSpriteId(i) = 0xFF;
        }
    }

    BlendPalettes(0xFFFF0000, 0xC, RGB(22, 24, 29));

    ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tCurrPageNo, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_HOFNumber);

    if (gTasks[taskId].tCurrTeamNo <= 0)
        HofPC_PutText(gStringVar4, gText_PickCancel, 0, 0, TRUE);
    else
        HofPC_PutText(gStringVar4, gText_PickNextCancel, 0, 0, TRUE);

    gTasks[taskId].func = Task_HofPC_PrintMonInfo;
}

void Task_HofPC_PrintMonInfo(u8 taskId) {
    struct HallofFameTeam *savedTeams = sHofMonPtr;
    struct HallofFameMon *currMon;
    u16 i;
    u16 currMonID;

    for (i = 0; i < gTasks[taskId].tCurrTeamNo; i++)
        savedTeams++;

    for (i = 0; i < PARTY_SIZE; i++) {
        u16 spriteId = gTasks[taskId].tMonSpriteId(i);
        if (spriteId != 0xFF)
            gSprites[spriteId].oam.priority = 1;
    }

    currMonID = gTasks[taskId].tMonSpriteId(gTasks[taskId].tCurrMonId);
    gSprites[currMonID].oam.priority = 0;
    sHofFadingRelated = (0x10000 << gSprites[currMonID].oam.paletteNum) ^ 0xFFFF0000;
    BlendPalettesUnfaded(sHofFadingRelated, 0xC, RGB(22, 24, 29));

    currMon = &savedTeams->mon[gTasks[taskId].tCurrMonId];
    if (currMon->species != SPECIES_EGG) {
        StopCryAndClearCrySongs();
        PlayCry1(currMon->species, 0);
    }
    HallOfFame_PrintMonInfo(currMon, 0, 14);

    gTasks[taskId].func = Task_HofPC_HandleInput;
}