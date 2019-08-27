#ifndef CHIP8_2_CHIP8_H
#define CHIP8_2_CHIP8_H

#include <time.h>

class chip8 {

public:

    chip8();
    ~chip8();

    void initialize();
    bool load_game(const char* name);
    void emulate_cycle();

    bool draw_flag;
    unsigned char screen[64 * 32];        //screen dimensions
    unsigned char key[16];



private:

    unsigned char chip8_fontset[80] =
            {
                    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                    0x20, 0x60, 0x20, 0x20, 0x70, // 1
                    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
            };

    unsigned short opcode;          //single opcode
    unsigned char mem[4096];        //memory
    unsigned char V[16];          //registers

    unsigned short I;       //value between tra 0x000 e 0xfff
    unsigned short PC;      //same as I

    unsigned short stack[16];        // Stack (16 levels)
    unsigned short sp;                // Stack pointer


    unsigned char delay_timer;        // Delay timer
    unsigned char sound_timer;        // Sound timer

};

#endif