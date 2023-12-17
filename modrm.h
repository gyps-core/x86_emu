#ifndef MODRM_H_
#define MODRM_H_


#include "emulator.h"


// ModR/Mを表す構造体
typedef struct {
    //mod
    uint8_t mod;
    //reg_index
    union {
        uint8_t opecode;
        uint8_t reg_index;
    };
    //
    uint8_t rm;

// mod/rmの組み合わせによって変わるためSIBの一緒に作成
    uint8_t sib;

    union {
        int8_t disp8;
        uint32_t disp32;
    };
}ModRM;



void parse_modrm(Emulator* emu, ModRM* modrm);

uint32_t calc_memory_address(Emulator* emu, ModRM* modrm);

void set_rm32(Emulator* emu, ModRM* modrm, uint32_t value);

uint32_t get_rm32(Emulator* emu, ModRM* modrm);

void set_r32(Emulator* emu, ModRM* modrm, uint32_t value);

uint32_t get_r32(Emulator* emu, ModRM* modrm);

#endif