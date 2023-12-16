// x86 realmode emurator
#include <stdio.h>
#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"

// 1MBのメモリサイズ
#define MEMORY_SIZE (1024 * 1024)

char* registers_name[] = {
    "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};


/* 汎用レジスタとプログラムカウンタの値を標準出力に出力する */
static void dump_registers(Emulator* emu){
    int i;
    for (i = 0; i < REGISTERS_COUNT; i++) {
        printf("%s = %08x\n", registers_name[i], emu->registers[i]);
    }
    printf("EIP = %08x\n", emu->eip);
}


int main(int argc, char* argv[]){
  FILE* binary;
  Emulator* emu;
  if(argc!=2){
    printf("usage: px86 filename\n");
    return 1;
  }

  emu = create_emu(MEMORY_SIZE, 0x7c00, 0x7c00);

  binary = fopen(argv[1], "rb");
  if(binary == NULL){
    printf("%sファイルが開けません\n", argv[1]);
    return 1;
  }

// 機械語ファイルを読み込む(最大512Byte)
  fread(emu->memory + 0x7c00, 1, 0x200, binary);
  fclose(binary);

  init_instruction();
  while(emu->eip < MEMORY_SIZE){
    uint8_t code = get_code8(emu, 0);
    printf("EIP = %X, Code = %02X\n", emu->eip, code);
    if(instructions[code]==NULL){
      printf("\n\nNot Implemeted: %x\n",code);
      break;
    }
    //命令の実行
    instructions[code](emu);

    //eipがゼロになったらプログラムを終了
    if(emu->eip == 0x00){
      printf("\n\nend of program.\n\n");
      break;
    }
  }

  dump_registers(emu);
  destroy_emu(emu);  
  return 0;
}