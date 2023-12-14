#include <stdint.h>

typedef struct{
  // 汎用レジスタ
  uint32_t registers[REGISTERS_COUNT];
  // EFlAGS レジスタ
  uint32_t eflags;
  // メモリ
  uint8_t* memory;
  // プログラムカウンタ
  uint32_t eip;
}Emulator;



