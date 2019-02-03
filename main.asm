.gba

.arm
.include "locations.s"

.thumb
.include "functions.s"

.open "rom.gba", "test.gba", 0x08000000

.org allocation
.area allocation_size
    .importobj "obj/relocatable.o"
.endarea

.org 0x080F1EFC     // CB2_DoHallOfFameScreen
.area 0x38, 0xFE
    ldr r3, =CB2_DoHallOfFameScreen |1
    bx r3
    .pool
.endarea

.org 0x080F2114     // Task_Hof_InitTeamSaveData
.area 0x2C, 0xFE
    ldr r3, =Task_Hof_InitTeamSaveData |1
    bx r3
    .pool
.endarea

.org 0x080F22B0     // Task_Hof_DisplayMon
.area 0x34, 0xFE
    ldr r3, =Task_Hof_DisplayMon |1
    bx r3
    .pool
.endarea

.org 0x080F23A0     // Task_Hof_PrintMonInfoAfterAnimating
.area 0x70, 0xFE
    ldr r3, =Task_Hof_PrintMonInfoAfterAnimating |1
    bx r3
    .pool
.endarea

.org 0x080F2424     // Task_Hof_TryDisplayAnotherMon
.area 0x3C, 0xFE
    ldr r3, =Task_Hof_TryDisplayAnotherMon |1
    bx r3
    .pool
.endarea

.org 0x080F2AA4     // Task_HofPC_CopySaveData
.area 0x34, 0xFE
    ldr r3, =Task_HofPC_CopySaveData |1
    bx r3
    .pool
.endarea

.org 0x080F2B6C     // Task_HofPC_DrawSpritesPrintText
.area 0xB8, 0xFE
    ldr r3, =Task_HofPC_DrawSpritesPrintText |1
    bx r3
    .pool
.endarea

.close