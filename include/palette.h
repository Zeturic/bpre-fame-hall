#pragma once

bool8 BeginNormalPaletteFade(u32, s8, u8, u8, u16);
void BlendPalettes(u32 selectedPalettes, u8 coeff, u16 color);
void BlendPalettesUnfaded(u32, u8, u16);
