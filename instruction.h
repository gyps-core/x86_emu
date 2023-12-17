#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "emulator.h"
#include "modrm.h"

void init_instruction(void);
//関数ポインタ
typedef void instruction_func_t(Emulator*);
extern instruction_func_t* instructions[256];

void mov_r32_imm32(Emulator* emu);

void mov_rm32_imm32(Emulator* emu);

static void mov_r32_rm32(Emulator* emu);

static void mov_rm32_r32(Emulator* emu);

void short_jump(Emulator* emu);

void near_jump(Emulator* emu);

static void add_rm32_r32(Emulator* emu);

static void sub_rm32_imm8(Emulator* emu, ModRM* modrm);

static void code_83(Emulator* emu);

static void inc_rm32(Emulator* emu, ModRM* modrm);

static void code_ff(Emulator* emu);


#endif
