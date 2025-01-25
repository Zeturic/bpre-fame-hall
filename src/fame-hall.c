#include "global.h"
#include "credits.h"
#include "data.h"
#include "decompress.h"
#include "hall_of_fame.c.h"
#include "quest_log.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "pokemon.h"
#include "save.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "trainer_pokemon_sprites.h"
#include "window.h"
#include "constants/species.h"

void CB2_DoHallOfFameScreen(void)
{
    u8 taskId;
    if (!InitHallOfFameScreen())
    {
        taskId = CreateTask(Task_Hof_InitMonData, 0);
        gTasks[taskId].data[0] = FALSE;
        sHofMonPtr = AllocZeroed(sizeof(struct HallofFameTeam));
    }
}

void Task_Hof_InitTeamSaveData(u8 taskId)
{
    u16 i;
    struct HallofFameTeam* lastSavedTeam = (struct HallofFameTeam *)(gDecompressionBuffer);

    SaveQuestLogData();
    if (!gHasHallOfFameRecords)
    {
        memset(gDecompressionBuffer, 0, 0x2000);
    }
    else
    {
        if (LoadGameSave(SAVE_HALL_OF_FAME) != TRUE)
            memset(gDecompressionBuffer, 0, 0x2000);
    }

    for (i = 0; i < HALL_OF_FAME_MAX_TEAMS; i++, lastSavedTeam++)
    {
        if (lastSavedTeam[0].mon[0].species == SPECIES_NONE)
            break;
    }
    if (i >= HALL_OF_FAME_MAX_TEAMS)
    {
        struct HallofFameTeam *afterTeam = (struct HallofFameTeam*)(gDecompressionBuffer);
        struct HallofFameTeam *beforeTeam = (struct HallofFameTeam*)(gDecompressionBuffer);
        afterTeam++;
        for (i = 0; i < HALL_OF_FAME_MAX_TEAMS - 1; i++, beforeTeam++, afterTeam++)
        {
            *beforeTeam = *afterTeam;
        }
        lastSavedTeam--;
    }
    *lastSavedTeam = *sHofMonPtr;

    DrawDialogueFrame(0, 0);
    AddTextPrinterParameterized2(0, 2, gText_SavingDontTurnOffThePower2, 0, NULL, 2, 1, 3);
    CopyWindowToVram(0, 3);
    gTasks[taskId].func = Task_Hof_TrySaveData;
}

void Task_Hof_DisplayMon(u8 taskId)
{
    u8 spriteId;
    s16 srcX;
    s16 srcY;
    s16 dstX;
    s16 dstY;

    u16 currMonId = gTasks[taskId].data[1];
    struct HallofFameMon* currMon = &sHofMonPtr[0].mon[currMonId];


    if (gTasks[taskId].data[2] > 3)
    {
        srcX = sHallOfFame_MonFullTeamPositions[currMonId][0];
        srcY = sHallOfFame_MonFullTeamPositions[currMonId][1];
        dstX = sHallOfFame_MonFullTeamPositions[currMonId][2];
        dstY = sHallOfFame_MonFullTeamPositions[currMonId][3];
    }
    else
    {
        srcX = sHallOfFame_MonHalfTeamPositions[currMonId][0];
        srcY = sHallOfFame_MonHalfTeamPositions[currMonId][1];
        dstX = sHallOfFame_MonHalfTeamPositions[currMonId][2];
        dstY = sHallOfFame_MonHalfTeamPositions[currMonId][3];
    }

    spriteId = CreateMonPicSprite_HandleDeoxys(currMon->species, currMon->tid, currMon->personality, 1, srcX, srcY, currMonId, 0xFFFF);
    gSprites[spriteId].data[1] = dstX;
    gSprites[spriteId].data[2] = dstY;
    gSprites[spriteId].data[0] = 0;
    gSprites[spriteId].callback = SpriteCB_GetOnScreen;
    gTasks[taskId].data[5 + currMonId] = spriteId;
    ClearDialogWindowAndFrame(0, TRUE);
    gTasks[taskId].func = Task_Hof_PlayMonCryAndPrintInfo;
}

void Task_Hof_PlayMonCryAndPrintInfo(u8 taskId)
{
    u16 currMonId = gTasks[taskId].data[1];
    struct HallofFameMon* currMon = &sHofMonPtr[0].mon[currMonId];
    if (gSprites[gTasks[taskId].data[5 + currMonId]].data[0])
    {
        if (currMon->species != SPECIES_EGG)
            PlayCry_Normal(currMon->species, 0);
        HallOfFame_PrintMonInfo(currMon, 0, 14);
        gTasks[taskId].data[3] = 120;
        gTasks[taskId].func = Task_Hof_TryDisplayAnotherMon;
    }
}

void Task_Hof_TryDisplayAnotherMon(u8 taskId)
{
    u16 currPokeId = gTasks[taskId].data[1];
    struct HallofFameMon* currMon = &sHofMonPtr[0].mon[currPokeId];

    if (gTasks[taskId].data[3] != 0)
    {
        gTasks[taskId].data[3]--;
    }
    else
    {
        sSelectedPaletteIndices |= (0x10000 << gSprites[gTasks[taskId].data[5 + currPokeId]].oam.paletteNum);
        if (gTasks[taskId].data[1] < PARTY_SIZE - 1 && currMon[1].species != SPECIES_NONE) // there is another pokemon to display
        {
            gTasks[taskId].data[1]++;
            BeginNormalPaletteFade(sSelectedPaletteIndices, 0, 12, 12, HALL_OF_FAME_BG_PAL);
            gSprites[gTasks[taskId].data[5 + currPokeId]].oam.priority = 1;
            gTasks[taskId].func = Task_Hof_DisplayMon;
        }
        else
        {
            gTasks[taskId].func = Task_Hof_PaletteFadeAndPrintWelcomeText;
        }
    }
}

void Task_HofPC_CopySaveData(u8 taskId)
{
    u16 i;
    struct HallofFameTeam* savedTeams;

    CreateTopBarWindowLoadPalette(0, 30, 0, 0x0C, 0x226);
    if (LoadGameSave(SAVE_HALL_OF_FAME) != SAVE_STATUS_OK)
    {
        gTasks[taskId].func = Task_HofPC_PrintDataIsCorrupted;
    }
    else
    {
        CpuCopy16(gDecompressionBuffer, sHofMonPtr, 0x2000);
        savedTeams = sHofMonPtr;
        for (i = 0; i < HALL_OF_FAME_MAX_TEAMS; i++, savedTeams++)
        {
            if (savedTeams->mon[0].species == SPECIES_NONE)
                break;
        }

        if (i < HALL_OF_FAME_MAX_TEAMS)
            gTasks[taskId].data[0] = i - 1;
        else
            gTasks[taskId].data[0] = HALL_OF_FAME_MAX_TEAMS - 1;

        gTasks[taskId].data[1] = GetGameStat(GAME_STAT_ENTERED_HOF);

        gTasks[taskId].func = Task_HofPC_DrawSpritesPrintText;
    }
}

void Task_HofPC_DrawSpritesPrintText(u8 taskId)
{
    struct HallofFameTeam *savedTeams = sHofMonPtr;
    struct HallofFameMon *currMon;
    u16 i;

    for (i = 0; i < gTasks[taskId].data[0]; i++)
        savedTeams++;

    currMon = &savedTeams->mon[0];
    sSelectedPaletteIndices = 0;
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].data[4] = 0;

    for (i = 0; i < PARTY_SIZE; i++, currMon++)
    {
        if (currMon->species != SPECIES_NONE)
            gTasks[taskId].data[4]++;
    }

    currMon = &savedTeams->mon[0];

    for (i = 0; i < PARTY_SIZE; i++, currMon++)
    {
        if (currMon->species != SPECIES_NONE)
        {
            u16 spriteId;
            s16 posX, posY;

            if (gTasks[taskId].data[4] > 3)
            {
                posX = sHallOfFame_MonFullTeamPositions[i][2];
                posY = sHallOfFame_MonFullTeamPositions[i][3];
            }
            else
            {
                posX = sHallOfFame_MonHalfTeamPositions[i][2];
                posY = sHallOfFame_MonHalfTeamPositions[i][3];
            }

            spriteId = CreateMonPicSprite_HandleDeoxys(currMon->species, currMon->tid, currMon->personality, TRUE, posX,
                                                       posY, i, 0xFFFF);
            gSprites[spriteId].oam.priority = 1;
            gTasks[taskId].data[5 + i] = spriteId;
        }
        else
        {
            gTasks[taskId].data[5 + i] = 0xFF;
        }
    }

    BlendPalettes(0xFFFF0000, 0xC, HALL_OF_FAME_BG_PAL);

    ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].data[1], STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_HOFNumber);

    if (gTasks[taskId].data[0] <= 0)
        TopBarWindowPrintTwoStrings(gStringVar4, gText_UPDOWNPick_ABUTTONBBUTTONCancel, 0, 0, TRUE);
    else
        TopBarWindowPrintTwoStrings(gStringVar4, gText_UPDOWNPick_ABUTTONNext_BBUTTONBack, 0, 0, TRUE);

    gTasks[taskId].func = Task_HofPC_PrintMonInfo;
}

void Task_HofPC_PrintMonInfo(u8 taskId)
{
    struct HallofFameTeam* savedTeams = sHofMonPtr;
    struct HallofFameMon* currMon;
    u16 i;
    u16 currMonId;

    for (i = 0; i < gTasks[taskId].data[0]; i++)
        savedTeams++;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u16 spriteId = gTasks[taskId].data[5 + i];
        if (spriteId != 0xFF)
            gSprites[spriteId].oam.priority = 1;
    }

    currMonId = gTasks[taskId].data[5 + gTasks[taskId].data[2]];
    gSprites[currMonId].oam.priority = 0;
    sSelectedPaletteIndices = (0x10000 << gSprites[currMonId].oam.paletteNum) ^ 0xFFFF0000;
    BlendPalettesUnfaded(sSelectedPaletteIndices, 0xC, HALL_OF_FAME_BG_PAL);

    currMon = &savedTeams->mon[gTasks[taskId].data[2]];
    if (currMon->species != SPECIES_EGG)
    {
        StopCryAndClearCrySongs();
        PlayCry_Normal(currMon->species, 0);
    }
    HallOfFame_PrintMonInfo(currMon, 0, 14);

    gTasks[taskId].func = Task_HofPC_HandleInput;
}

void Task_Hof_InitMonData(u8 taskId)
{
    u16 i;
    u16 j;
    u8 nick[11];

    gTasks[taskId].data[2] = 0;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE)
        {
            sHofMonPtr[0].mon[i].species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2);
            sHofMonPtr[0].mon[i].tid = GetMonData(&gPlayerParty[i], MON_DATA_OT_ID);
            sHofMonPtr[0].mon[i].personality = GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY);
            sHofMonPtr[0].mon[i].lvl = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
            GetMonData(&gPlayerParty[i], MON_DATA_NICKNAME, nick);
            for (j = 0; j < 10; j++)
                sHofMonPtr[0].mon[i].nick[j] = nick[j];
            gTasks[taskId].data[2]++;
        }
        else
        {
            sHofMonPtr[0].mon[i].species = SPECIES_NONE;
            sHofMonPtr[0].mon[i].tid = 0;
            sHofMonPtr[0].mon[i].personality = 0;
            sHofMonPtr[0].mon[i].lvl = 0;
            sHofMonPtr[0].mon[i].nick[0] = EOS;
        }
    }
    sSelectedPaletteIndices = 0;
    gTasks[taskId].data[1] = 0;
    gTasks[taskId].data[4] = 0xFF;
    for (i = 0; i < 6; i++)
        gTasks[taskId].data[i + 5] = 0xFF;
    if (gTasks[taskId].data[0])
        gTasks[taskId].func = Task_Hof_StartDisplayingMons;
    else
        gTasks[taskId].func = Task_Hof_InitTeamSaveData;
}

void HallOfFame_PrintMonInfo(struct HallofFameMon* currMon, UNUSED u8 unused1, UNUSED u8 unused2)
{
    u8 text[16];
    u8 text2[24];
    u16 i;
    u8 *stringPtr;
    u16 dexNumber;
    u8 gender;
    s32 width;
    s32 x;

    FillWindowPixelBuffer(0, PIXEL_FILL(0));
    PutWindowTilemap(0);

    // dex number
    if (currMon->species != SPECIES_EGG)
    {
        StringCopy(text2, gText_Number);
        dexNumber = SpeciesToPokedexNum(currMon->species);
        if (dexNumber != 0xFFFF)
        {
            text[0] = (dexNumber / 100) + CHAR_0;
            text[1] = ((dexNumber %= 100) / 10) + CHAR_0;
            text[2] = (dexNumber % 10) + CHAR_0;
        }
        else
        {
            text[0] = text[1] = text[2] = CHAR_QUESTION_MARK;
        }
        text[3] = EOS;
        StringAppend(text2, text);
        AddTextPrinterParameterized3(0, 2, 0x10, 1, sTextColors[0], 0, text2);
    }

    // nick, species names, gender and lvl
    i = 0;
    if (currMon->nick[0] != EOS)
    {
        for (i = 0; i < 10 && currMon->nick[i] != EOS; i++)
        {
            text[i] = currMon->nick[i];
        }
    }
    text[i] = EOS;
    width = GetStringWidth(2, text, GetFontAttribute(2, FONTATTR_LETTER_SPACING));
    if (currMon->species == SPECIES_EGG)
        x = 0x80 - width / 2;
    else
        x = 0x80 - width;
    AddTextPrinterParameterized3(0, 2, x, 1, sTextColors[0], 0, text);
    if (currMon->species != SPECIES_EGG)
    {
        text[0] = CHAR_SLASH;
        stringPtr = StringCopy(text + 1, gSpeciesNames[currMon->species]);

        if (currMon->species == SPECIES_NIDORAN_M || currMon->species == SPECIES_NIDORAN_F)
            gender = MON_GENDERLESS;
        else
            gender = GetGenderFromSpeciesAndPersonality(currMon->species, currMon->personality);
        switch (gender)
        {
        case MON_MALE:
            *stringPtr++ = CHAR_MALE;
            break;
        case MON_FEMALE:
            *stringPtr++ = CHAR_FEMALE;
            break;
        default:
            *stringPtr++ = CHAR_SPACE;
            break;
        }
        *stringPtr = EOS;

        AddTextPrinterParameterized3(0, 2, 0x80, 1, sTextColors[0], 0, text);

        stringPtr = StringCopy(text, gText_Level);
        ConvertIntToDecimalStringN(stringPtr, currMon->lvl, STR_CONV_MODE_LEFT_ALIGN, 3);
        AddTextPrinterParameterized3(0, 2, 0x20, 0x11, sTextColors[0], 0, text);

        stringPtr = StringCopy(text, gText_IDNumber);
        ConvertIntToDecimalStringN(stringPtr, (u16)(currMon->tid), STR_CONV_MODE_LEADING_ZEROS, 5);
        AddTextPrinterParameterized3(0, 2, 0x60, 0x11, sTextColors[0], 0, text);

    }
    CopyWindowToVram(0, 3);
}
