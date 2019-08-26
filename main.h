#ifndef CHIP8_2_MAIN_H
#define CHIP8_2_MAIN_H

#include <GL/gl.h>
#include "chip8.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define MODIFIER 10
//Stuff for display sizes
int display_width = SCREEN_WIDTH * MODIFIER;
int display_height = SCREEN_HEIGHT * MODIFIER;
chip8 c8;

//Inits
void init_graphics(int argc, char **argv);
void init_input();

static void draw_graphics();
static void update_quads();
static void draw_pixel(int x, int y);

static void reshape_window(GLsizei w, GLsizei h);

static void keyboard_up(unsigned char key, int x, int y);

static void keyboard_down(unsigned char key, int x, int y);


;
#endif //CHIP8_2_MAIN_H
