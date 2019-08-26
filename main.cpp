#include <iostream>
#include "chip8.h"

int main(int argc, char **argv) {

    unsigned short x = 11101110u & 1111u;

    //test vari

    unsigned short opcode = 0x82F3;
    unsigned short test_test = opcode & 0x0F00;
    test_test = test_test >> 8;
    unsigned short test = opcode & 0xF000;

    switch (test) {
        case 0x0000:
            test = opcode & 0x000F;
            switch (test) {
                case 0x0000: // 0x00E0: Clears the screen
                    // Execute opcode
                    break;

                case 0x000E: // 0x00EE: Returns from subroutine
                    // Execute opcode
                    std::cout << opcode;

                    break;

                default:
                    printf("Unknown opcode [0x0000]: 0x%X\n", opcode);
            }
            break;
    }
}