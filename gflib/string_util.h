#pragma once

#define STR_CONV_MODE_LEFT_ALIGN    0
#define STR_CONV_MODE_LEADING_ZEROS 2

extern u8 gStringVar1[];
extern u8 gStringVar4[];

u8 *ConvertIntToDecimalStringN(u8 *dest, s32 value, u32 mode, u8 n);
u8 *StringExpandPlaceholders(u8 *dest, const u8 *src);
u8 *StringCopy(u8 *dest, const u8 *src);
u8 *StringAppend(u8 *dest, const u8 *src);
