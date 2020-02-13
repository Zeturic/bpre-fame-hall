#pragma once

#include "constants/pokemon.h"

struct Pokemon
{
    u8 _[100];
};

extern struct Pokemon gPlayerParty[];

u32 GetMonData();
u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality);
u16 SpeciesToPokedexNum(u16 species);
