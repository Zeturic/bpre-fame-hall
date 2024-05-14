.gba
.thumb

.open "rom.gba", "test.gba", 0x08000000

// -----------------------------------------------------------------------------

.org allocation
.area allocation_size
    .importobj "build/linked.o"
.endarea

// -----------------------------------------------------------------------------
// CB2_DoHallOfFameScreen

.org 0x080F1EFC
.area 0x080F1F32 - 0x080F1EFC, 0xFE
    ldr r3, =CB2_DoHallOfFameScreen |1
    bx r3
    .pool
.endarea

// -----------------------------------------------------------------------------
// Task_Hof_InitTeamSaveData

.org 0x080F2114
.area 0x080F2140 - 0x080F2114, 0xFE
    ldr r3, =Task_Hof_InitTeamSaveData |1
    bx r3
    .pool
.endarea

.org 0x080F2148 :: .fill 0x080F2206 - 0x080F2148, 0xFE

// -----------------------------------------------------------------------------
// Task_Hof_DisplayMon

.org 0x080F22B0
.area 0x080F22E2 - 0x080F22B0, 0xFE
    ldr r3, =Task_Hof_DisplayMon |1
    bx r3
    .pool
.endarea

.org 0x080F22F0 :: .fill 0x080F2388 - 0x080F22F0, 0xFE

// -----------------------------------------------------------------------------
// Task_Hof_PlayMonCryAndPrintInfo

.org 0x080F23A0
.area 0x080F240E - 0x080F23A0, 0xFE
    ldr r3, =Task_Hof_PlayMonCryAndPrintInfo |1
    bx r3
    .pool
.endarea

// -----------------------------------------------------------------------------
// Task_Hof_TryDisplayAnotherMon

.org 0x080F2424
.area 0x080F245E - 0x080F2424, 0xFE
    ldr r3, =Task_Hof_TryDisplayAnotherMon |1
    bx r3
    .pool
.endarea

.org 0x080F2468 :: .fill 0x080F24E0 - 0x080F2468, 0xFE
.org 0x080F24F4 :: .fill 0x080F250E - 0x080F24F4, 0xFE

// -----------------------------------------------------------------------------
// Task_HofPC_CopySaveData

.org 0x080F2AA4
.area 0x080F2AD8 - 0x080F2AA4, 0xFE
    ldr r3, =Task_HofPC_CopySaveData |1
    bx r3
    .pool
.endarea

.org 0x080F2AE4 :: .fill 0x080F2B2A - 0x080F2AE4, 0xFE
.org 0x080F2B3C :: .fill 0x080F2B64 - 0x080F2B3C, 0xFE

// -----------------------------------------------------------------------------
// Task_HofPC_DrawSpritesPrintText

.org 0x080F2B6C
.area 0x080F2C22 - 0x080F2B6C, 0xFE
    ldr r3, =Task_HofPC_DrawSpritesPrintText |1
    bx r3
    .pool
.endarea

.org 0x080F2C3C :: .fill 0x080F2C9A - 0x080F2C3C, 0xFE
.org 0x080F2CA8 :: .fill 0x080F2D06 - 0x080F2CA8, 0xFE
.org 0x080F2D24 :: .fill 0x080F2D52 - 0x080F2D24, 0xFE

// -----------------------------------------------------------------------------
// Task_HofPC_PrintMonInfo

.org 0x080F2D60
.area 0x080F2E66 - 0x080F2D60, 0xFE
    ldr r3, =Task_HofPC_PrintMonInfo |1
    bx r3
    .pool
.endarea

// -----------------------------------------------------------------------------
// Task_Hof_InitMonData

.org 0x080F1F74
.area 0x080F204E - 0x080F1F74, 0xFE
    ldr r3, =Task_Hof_InitMonData |1
    bx r3
    .pool
.endarea

.org 0x080F2064 :: .fill 0x080F20EA - 0x080F2064, 0xFE
.org 0x080F20FC :: .fill 0x080F210E - 0x080F20FC, 0xFE

// -----------------------------------------------------------------------------
// HallOfFame_PrintMonInfo

.org 0x080F3194
.area 0x080F3214 - 0x080F3194, 0xFE
    ldr r3, =HallOfFame_PrintMonInfo |1
    bx r3
    .pool
.endarea

.org 0x080F3220 :: .fill 0x080F32B8 - 0x080F3220, 0xFE
.org 0x080F32C0 :: .fill 0x080F331C - 0x080F32C0, 0xFE
.org 0x080F3328 :: .fill 0x080F33CE - 0x080F3328, 0xFE

// -----------------------------------------------------------------------------

.close
