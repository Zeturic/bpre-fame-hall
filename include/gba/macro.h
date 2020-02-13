#pragma once

#define CpuCopy16(src, dest, size) CPU_COPY(src, dest, size, 16)
#define CPU_COPY(src, dest, size, bit) CpuSet(src, dest, CPU_SET_##bit##BIT | ((size)/(bit/8) & 0x1FFFFF))
