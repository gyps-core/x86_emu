#ifndef EMULATOR_H_ 
#define EMULATOR_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

enum Register { EAX,//算術の結果を格納される
                ECX,//ループの反復回数を数えるのに用いられる
                EDX,//除算ではあまり、IO操作にも用いられる
                EBX,//ベースアドレスを指定するのに用いられる
                ESP,//スタックの先頭を指す
                EBP,//スタック上の何等かのデータを指す
                ESI,//文字列や配列操作:入力データ
                EDI,//文字列や配列操作:出力データ
                REGISTERS_COUNT 
                };


typedef struct{
  // 汎用レジスタ
  uint32_t registers[REGISTERS_COUNT];
  // EFlAGS レジスタ
  uint32_t eflags;//演算結果やCPUの状態を表す
  // メモリ
  uint8_t* memory;
  // プログラムカウンタ
  uint32_t eip;//現在実行中の命令の番地を記憶する
}Emulator;

#endif