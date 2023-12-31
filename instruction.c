#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "instruction.h"
#include "emulator.h"
#include "emulator_function.h"


instruction_func_t* instructions[256];

// 特定の32bit レジスタに特定の値(即値)　を設定する。

//即値を32bitレジスタへ格納
void mov_r32_imm32(Emulator* emu){
  uint8_t reg = get_code8(emu, 0) - 0xB8;//対象のレジスタのインデックス
  uint32_t value = get_code32(emu, 1);
  set_register32(emu, reg, value);
  emu->eip +=5;//オペコードのサイズ＋値のサイズ
}

//即値をレジスタまたはアドレスに格納
void mov_rm32_imm32(Emulator* emu){
    emu->eip +=1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t value = get_code32(emu, 0);
    emu->eip +=4;
    set_rm32(emu, &modrm, value);
}

//レジスタまたはメモリアドレスをレジスタに格納
static void mov_r32_rm32(Emulator* emu){
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t rm32 = get_rm32(emu, &modrm);
    set_r32(emu, &modrm, rm32);
}

//レジスタの値をメモリアドレス、またはレジスタに格納
static void mov_rm32_r32(Emulator* emu){
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t r32 = get_r32(emu, &modrm);
    set_rm32(emu, &modrm, r32);
}

//add
static void add_rm32_r32(Emulator* emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t r32 = get_r32(emu, &modrm);
    uint32_t rm32 = get_rm32(emu, &modrm);
    set_rm32(emu, &modrm, rm32 + r32);
}

static void sub_rm32_imm8(Emulator* emu, ModRM* modrm)
{
    uint32_t rm32 = get_rm32(emu, modrm);
    uint32_t imm8 = (int32_t)get_sign_code8(emu, 0);
    emu->eip += 1;
    set_rm32(emu, modrm, rm32 - imm8);
}

static void code_83(Emulator* emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);

    switch (modrm.opecode) {
    case 5:
        sub_rm32_imm8(emu, &modrm);
        break;
    default:
        printf("not implemented: 83 /%d\n", modrm.opecode);
        exit(1);
    }
}


static void inc_rm32(Emulator* emu, ModRM* modrm)
{
    uint32_t value = get_rm32(emu, modrm);
    set_rm32(emu, modrm, value + 1);
}

static void code_ff(Emulator* emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);

    switch (modrm.opecode) {
    case 0:
        inc_rm32(emu, &modrm);
        break;
    default:
        printf("not implemented: FF /%d\n", modrm.opecode);
        exit(1);
    }
}





void short_jump(Emulator* emu){
  int8_t diff = get_sign_code8(emu, 1);
  emu->eip += (diff+2);//オペコード+1で2バイトのオフセット
}

void near_jump(Emulator* emu){
  int32_t diff = get_sign_code32(emu, 1);
  emu->eip += (diff+5);
}


/*
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
*/

void init_instruction(void)
{
    int i;
    memset(instructions, 0, sizeof(instructions));
    instructions[0x01] = add_rm32_r32;
    instructions[0x83] = code_83;
    instructions[0x89] = mov_rm32_r32;
    instructions[0x8B] = mov_r32_rm32;
    for (i = 0; i < 8; i++) {
        instructions[0xB8 + i] = mov_r32_imm32;
    }
    instructions[0xC7] = mov_rm32_imm32;
    instructions[0xE9] = near_jump;
    instructions[0xEB] = short_jump;
    instructions[0xFF] = code_ff;
}