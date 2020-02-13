#pragma once

#define PIXEL_FILL(num) ((num) | ((num) << 4))

void CopyWindowToVram(u8 windowId, u8 mode);
void FillWindowPixelBuffer(u8 windowId, u8 fillValue);
void PutWindowTilemap(u8 windowId);
