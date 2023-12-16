#ifndef EMULATOR_FUNCTION_H_
#define EMULATOR_FUNCTION_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "emulator.h"

uint32_t get_code8(Emulator* emu, int index);

int32_t get_sign_code8(Emulator* emu, int index);

//リトルエンディアン
uint32_t get_code32(Emulator* emu, int index);

int32_t get_sign_code32(Emulator* emu, int index);

Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp);

void destroy_emu(Emulator* emu);

#endif