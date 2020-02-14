#pragma once

// extern const u8 gSpeciesNames[][POKEMON_NAME_LENGTH + 1];
typedef const u8 gSpeciesNamesType[][POKEMON_NAME_LENGTH + 1];
extern const gSpeciesNamesType * const gSpeciesNamesPtr;
#define gSpeciesNames (*gSpeciesNamesPtr)
