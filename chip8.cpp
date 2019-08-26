#include <iostream>
#include "chip8.h"

chip8::chip8() {

    initialize();
}

chip8::~chip8() {

}


void chip8::initialize() {
    //Initialize registers and memory once


    //Registers and stuff
    PC = 0x200;           //The system expects that the application will be loaded at mem location 0x200
    opcode = 0;        //Reset current opcode
    I = 0;             //Reset index register
    sp = 0;            //Reset stack pointer

    for (unsigned char &i : screen)             //Reset Display, 64*32
        i = 0;

    for (unsigned short &i : stack)              //Reset stack
        i = 0;

    for (unsigned char &i : V)             //Reset registers V0-VF
        i = 0;

    for (unsigned char &i : mem)           //Reset memory
        i = 0;

    //Fontset
    for (int i = 0; i < 0x50; ++i) {
        mem[i] = chip8_fontset[i];         //loads the fontset into memory
    }


    //Timers
}

void chip8::emulate_cycle() {

    //Fetch Opcode
    opcode = mem[PC] << 8u |
             mem[PC + 1];        //First we shift it 8 bits to the left, then we merge PC with PC+1 opcodes with an OR

    switch (opcode & 0xF000u) {     //if opcode has something at the first left bit



        case 0x1000:
        case 0xA000:     ///Annn: Sets I to nnn

            I = opcode & 0x0FFFu;
            PC += 2;
            break;  //todo not sure

        case 0x2000:    ///Calls subroutine at address NNNN
            stack[sp] = PC;     //save old address
            ++sp;       //we added an element to the stack, we must decrement it then when we want to retrieve the old PC
            PC = opcode & 0x0FFFu;   //bingox
            break;

        case 0x3000:    ///Skip next instruction if Vx=kk

            if ((opcode & 0x00FFu) == V[opcode & 0x0F00u])
                PC += 2;
            break;

        case 0x4000:  ///Skip next instruction if Vx != kk
            if ((opcode & 0x00FFu) != V[opcode & 0x0F00u])
                PC += 2;
            break;

        case 0x5000:    ///Skip next instruction if Vx=Vy
            if (V[opcode & 0x0F00u] == V[opcode & 0x00F0u])
                PC += 2;
            break;

        case 0x6000:      ///Set Vx = kk

            V[opcode & 0x0F00u] = opcode & 0x00FFu;
            PC += 2;
            break;

        case 0x7000:        ///Set Vx = Vx + kk

            V[opcode & 0x0F00u] += opcode & 0x00FFu;
            PC += 2;
            break;

        case 0x8000:   ///Multiple cases

            switch (opcode & 0x000Fu) {

                case 0x0000:        ///Set Vx = Vy
                    V[(opcode & 0x0F00u) >> 8u] = V[(opcode & 0x00F0u) >> 4u];
                    PC += 2;
                    break;

                case 0x0001:        ///Set Vx = Vx | Vy
                    V[(opcode & 0x0F00u) >> 8u] = V[(opcode & 0x0F00u) >> 8u] | V[(opcode & 0x00F0u) >> 4u];
                    PC += 2;
                    break;

                case 0x0002:        ///Set Vx = Vx AND Vy
                    V[(opcode & 0x0F00u) >> 8u] = V[(opcode & 0x0F00u) >> 8u] & V[(opcode & 0x00F0u) >> 4u];
                    PC += 2;
                    break;
                case 0x0003:        ///Set Vx = Vx XOR Vy
                    V[(opcode & 0x0F00u) >> 8u] = V[(opcode & 0x0F00u) >> 8u] ^ V[(opcode & 0x00F0u) >> 4u];
                    PC += 2;
                    break;
                case 0x0004:        ///Set Vx = Vx + Vy, set Vf = carry if overflow

                    if (V[(opcode & 0x0F00u) >> 8u] + V[(opcode & 0x00F0u) >> 4u] > 255)
                        V[0xF] = 1;
                    else
                        V[0xF] = 0;

                    V[(opcode & 0x0F00u) >> 8u] += V[(opcode & 0x00F0u) >> 4u];

                    PC += 2;
                    break;
                case 0x0005:        ///Set Vx = Vx - Vy, set Vf = NOT BORROW if underflow

                    if (V[(opcode & 0x0F00u) >> 8u] > V[(opcode & 0x00F0u) >> 4u])
                        V[0xF] = 1;
                    else
                        V[0xF] = 0;

                    V[(opcode & 0x0F00u) >> 8u] -= V[(opcode & 0x00F0u) >> 4u];

                    PC += 2;
                    break;
                case 0x0006:        ///Set Vx = Vx SHR 1

                    if ((V[(opcode & 0x0F00u) >> 8u] & 0x000Fu) == 1)
                        V[0xF] = 1;
                    else
                        V[0xF] = 0;

                    V[(opcode & 0x0F00u) >> 8u] /= 2;  //divided by 2

                    PC += 2;
                    break;

                case 0x0007:        ///Set Vx = Vy - Vx and set Vf = not borrow if underflow


                    if (V[(opcode & 0x0F00u) >> 8u] < V[(opcode & 0x00F0u) >> 4u])
                        V[0xF] = 1;     //dont borrow
                    else
                        V[0xF] = 0;

                    //Vx = Vy-Vx
                    V[(opcode & 0x0F00u) >> 8u] = V[(opcode & 0x00F0u) >> 4u] - V[(opcode & 0x0F00u) >> 8u];

                    PC += 2;
                    break;
                case 0x0008:        ///Set Vx = Vx SHL 1

                    if ((V[(opcode & 0x0F00u) >> 8u]) & (0xF000u) == 1)       //todo something isnt right
                        V[0xF] = 1;
                    else
                        V[0xF] = 0;

                    V[(opcode & 0x0F00u) >> 8u] *= 2;  //multiplied by 2

                    PC += 2;
                    break;

            }

        case 0x9000:        ///Skip if Vx != Vy
            if (V[opcode & 0x0F00u] != V[opcode & 0x00F0u])
                PC += 2;
            break;

        case 0xB000:        ///JP to nnn + V0
            PC = ((opcode & 0x0FFFu) << 4u) + V[0x0];
            break;
        case 0xC000:        ///RND byte AND kk

            V[(opcode & 0x0F00u) >> 8u] =  rand()%256 + ((opcode & 0x00FFu) << 8u);
            PC += 2;
            break;

        case 0xD000:        ///Drawing crap
        {
            unsigned short x = V[(opcode & 0x0F00u) >> 8u];
            unsigned short y = V[(opcode & 0x0F00u) >> 4u];
            unsigned short height = opcode & 0x000Fu;
            unsigned short pixel;

            V[0xF] = 0; //Reset register

            for (int y_line = 0; y_line < height; y_line++) {   //loop for every row
                pixel = mem[I + y_line];                        //fetch pixel values for every row
                for (int x_line = 0; x_line < 8; x_line++) {
                    if ((pixel & (0x80 >> x_line)) != 0 &&
                        screen[x + x_line + (y + y_line) * 64] == 1) //needs to be printed
                        V[0xF] = 1;
                    screen[x + x_line + ((y + y_line) * 64)] ^= 1;          //set screen value via XOR
                }
            }

            draw_flag = true;           //Signals that the screen has to be updated
            PC += 2;
        }
            break;

        case 0xE000:
            switch (opcode & 0x00FFu) {
                case 0x009E:
                    if (key[V[(opcode & 0x0F00u) >> 8u]] != 0)
                        PC += 4;
                    else
                        PC += 2;
            }

        case 0x0000:                //it was something like 0x00F0, so it returned 0

            switch (opcode & 0xF000u) {
                //Jump code
                case 0x0000:
                    printf("This is useless");
            }
            switch (opcode & 0x000Fu) {

                case 0x0000:    ///Clean the screen
                    for (unsigned char &i : screen)
                        i = 0x0;

                    draw_flag = true;
                    PC += 2;
                    break;
                case 0x000E:    ///Returns from subroutine

                    //subroutine is stored somewhere in the stack
                    --sp;           //prevent overflow, max 16
                    PC = stack[sp];     //restore PC
                    PC += 2;        //always increment this thingy

                    break;

                case 0x0004:    ///Adds value of VY to VX
                    if (V[(opcode & 0x00F0u) >> 4u] > (0xFF - V[(opcode & 0x0F00u) >> 8u]))
                        V[0xF] = 1; //set VF to 1
                    else
                        V[0xF] = 0;  //set VF to 0
                    V[(opcode & 0x0F00u) >> 8u] += V[(opcode & 0x00F0u) >> 4u];
                    PC += 2;
                    break;
                default:
                    std::cout << "Error: unknow opcode [0x0000]" << std::endl;
            }


            //todo where do I put this?
        case 0x0033:    ///Stores binary coded decimal rappresentation of VX at the addresses I, I+1 and I+2
            mem[I] = V[opcode & 0x0F00u >> 8u] / 100;
            mem[I + 1] = (V[opcode & 0x0F00u >> 8u] / 10) % 10;
            mem[I + 2] = (V[opcode & 0x0F00u >> 8u] % 100) % 10;
            PC += 2;


        default:
            std::cout << "Error: unknown opcode" << std::endl;
    }
    //at the end update timers

    if (delay_timer > 0) {
        --delay_timer;
    }

    if (sound_timer > 0 && sound_timer == 1) {
        --sound_timer;
        std::cout << "Beep" << std::endl;
    }

}