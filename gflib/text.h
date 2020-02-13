#pragma once

#define CHAR_SPACE          0x00
#define CHAR_0              0xA1
#define CHAR_QUESTION_MARK  0xAC
#define CHAR_MALE           0xB5
#define CHAR_FEMALE         0xB6
#define CHAR_SLASH          0xBA
#define EOS                 0xFF // end of string

#define FONTATTR_LETTER_SPACING 2

struct TextPrinterTemplate;

s32 GetStringWidth(u8 fontId, const u8 *str, s16 letterSpacing);
u8 GetFontAttribute(u8 fontId, u8 attributeId);
