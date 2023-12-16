#include "emulator_function.h"
#include "emulator.h"

uint32_t get_code8(Emulator* emu, int index){
    return emu->memory[emu->eip + index];
}

int32_t get_sign_code8(Emulator* emu, int index){
    return (int8_t)emu->memory[emu->eip + index];
}


//リトルエンディアン
uint32_t get_code32(Emulator* emu, int index){
    int i;
    uint32_t ret = 0;

    for (i = 0; i < 4; i++) {
        ret |= get_code8(emu, index + i) << (i * 8);
    }

    return ret;
}

int32_t get_sign_code32(Emulator* emu, int index)
{
    return (int32_t)get_code32(emu, index);
}


Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp)
{
  Emulator* emu = malloc(sizeof(Emulator));
  emu->memory = malloc(size);

  memset(emu->registers, 0, sizeof(emu->registers));
  emu->eip = eip;
  emu->registers[ESP] = esp;

  return emu;
}


void destroy_emu(Emulator* emu){
  free(emu->memory);
  free(emu);
}