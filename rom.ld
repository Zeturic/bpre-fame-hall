AllocZeroed                                 = 0x08002BB0 |1;
CopyWindowToVram                            = 0x08003F20 |1;
PutWindowTilemap                            = 0x08003FA0 |1;
FillWindowPixelBuffer                       = 0x0800445C |1;
GetStringWidth                              = 0x08005ED4 |1;
StringCopy                                  = 0x08008D84 |1;
StringAppend                                = 0x08008DA4 |1;
ConvertIntToDecimalStringN                  = 0x08008E78 |1;
StringExpandPlaceholders                    = 0x08008FCC |1;
GetGenderFromSpeciesAndPersonality          = 0x0803F78C |1;
GetMonData                                  = 0x0803FBE8 |1;
SpeciesToPokedexNum                         = 0x08043F90 |1;
GetGameStat                                 = 0x08054EC4 |1;
BeginNormalPaletteFade                      = 0x08070588 |1;
BlendPalettes                               = 0x080714D4 |1;
BlendPalettesUnfaded                        = 0x08071510 |1;
PlayCry1                                    = 0x08071DF0 |1;
StopCryAndClearCrySongs                     = 0x080721C4 |1;
CreateTask                                  = 0x0807741C |1;
Save_LoadGameData                           = 0x080DA4FC |1;
InitHallOfFameScreen                        = 0x080F1DDC |1;
Task_Hof_TrySaveData                        = 0x080F2220 |1;
Task_Hof_StartDisplayingMons                = 0x080F2294 |1;
Task_Hof_PaletteFadeAndPrintWelcomeText     = 0x080F2514 |1;
Task_HofPC_HandleInput                      = 0x080F2E8C |1;
Task_HofPC_PrintDataIsCorrupted             = 0x080F30A4 |1;
SpriteCB_GetOnScreen                        = 0x080F3870 |1;
AddTextPrinterParameterized2                = 0x080F6CD0 |1;
DrawDialogueFrame                           = 0x080F6EE4 |1;
ClearDialogWindowAndFrame                   = 0x080F6F54 |1;
GetFontAttribute                            = 0x080F79D8 |1;
CreateMonPicSprite_HandleDeoxys             = 0x0810C1CC |1;
CreateTopBarWindowLoadPalette               = 0x0810F558 |1;
TopBarWindowPrintTwoStrings                 = 0x0810F650 |1;
sub_8112450                                 = 0x08112450 |1;
AddTextPrinterParameterized3                = 0x0812E51C |1;
CpuSet                                      = 0x081E3B64 |1;
__udivsi3                                   = 0x081E460C |1;
__umodsi3                                   = 0x081E4684 |1;
memcpy                                      = 0x081E5E78 |1;
memset                                      = 0x081E5ED8 |1;


/* -------------------------------------------------------------------------- */

gDecompressionBuffer                        = 0x0201C000;
gSprites                                    = 0x0202063C;
gStringVar1                                 = 0x02021CD0;
gStringVar4                                 = 0x02021D18;
gPlayerParty                                = 0x02024284;
sSelectedPaletteIndices                     = 0x0203AB34;
sHofMonPtr                                  = 0x0203AB38;
gHasHallOfFameRecords                       = 0x0203AB44;

gTasks                                      = 0x03005090;

gSpeciesNames                               = 0x08245EE0;
sTextColors                                 = 0x0840C23C;
sHallOfFame_MonFullTeamPositions            = 0x0840C268;
sHallOfFame_MonHalfTeamPositions            = 0x0840C298;
gText_UPDOWNPick_ABUTTONNext_BBUTTONBack    = 0x08415D60;
gText_UPDOWNPick_ABUTTONBBUTTONCancel       = 0x08415D78;
gText_HOFNumber                             = 0x084160B4;
gText_Number                                = 0x084160EC;
gText_Level                                 = 0x084160F4;
gText_IDNumber                              = 0x08416104;
gText_SavingDontTurnOffThePower2            = 0x08419F54;
