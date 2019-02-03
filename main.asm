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

.org 0x080F2114
.area 0x2C, 0xFE
    ldr r3, =Task_Hof_InitTeamSaveData |1
    bx r3
    .pool
.endarea

.close