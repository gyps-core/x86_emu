#include <stdint.h>
#include <string.h>

#include "instruction.h"
#include "emulator.h"
#include "emulator_function.h"

instruction_func_t* instructions[256];

// 特定の32bit レジスタに特定の値(即値)　を設定する。
void mov_r32_imm32(Emulator* emu){
  uint8_t reg = get_code8(emu, 0) - 0xB8;//対象のレジスタのインデックス
  uint32_t value = get_code32(emu, 1);
  emu->registers[reg] = value;
  emu->eip +=5;//オペコードのサイズ＋値のサイズ
}

void short_jump(Emulator* emu){
  int8_t diff = get_sign_code8(emu, 1);
  emu->eip += (diff+2);//オペコード+1で2バイトのオフセット
}

void near_jump(Emulator* emu){
  int32_t diff = get_sign_code32(emu, 1);
  emu->eip += (diff+5);
}


void init_instruction(void){
  int i;
  memset(instructions, 0, sizeof(instructions));
  //movを汎用レジスタ分設置する。
  for (i=0; i<8; i++){
    instructions[0xB8 + i] = mov_r32_imm32;
  }
  instructions[0xE9] = near_jump;
  instructions[0xEB] = short_jump;

}