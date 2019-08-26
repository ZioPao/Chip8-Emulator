#include <iostream>
#include <time.h>
#include <windows.h>
#include <GL/glut.h>
#include "chip8.h"
#include "main.h"


int main(int argc, char **argv) {

    //Init
    init_graphics(argc, argv);
    init_input();

    c8.initialize();      //emu initialization

    if (c8.load_game("pong")){
        while(1){

            c8.emulate_cycle();       //One cycle

            if (c8.draw_flag)
                draw_graphics();

            c8.set_keys();        //Press and relase buttons
        }
    }


    return 0;
}

void init_graphics(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(display_width, display_height);
    glutInitWindowPosition(320,320);
    glutCreateWindow("Emulator");

    glutDisplayFunc(draw_graphics);
    glutIdleFunc(draw_graphics);

}

void init_input() {
    //todo stuff
}

void draw_graphics() {

    glClear(GL_COLOR_BUFFER_BIT);   //Clear framebuffer

#ifdef DRAWWITHTEXTURE
    updateTexture(myChip8);
#else
    update_quads();
#endif

    // Swap buffers!
    glutSwapBuffers();

    // Processed frame
    c8.draw_flag = false;
}
void update_quads() {

    //Draw quads

    for (int y = 0; y < SCREEN_HEIGHT; ++y)
        for (int x = 0; x < SCREEN_WIDTH; ++x) {

            if (c8.screen[(y * 64) + x] == 0)
                glColor3f(0.0f, 0.0f, 0.0f);
            else
                glColor3f(1.0f, 1.0f, 1.0f);

            draw_pixel(x, y);
        }
}
void draw_pixel(int x, int y) {

    //We're making quads, so it makes sense that we have 4 vertices
    glBegin(GL_QUADS);

    glVertex3f((x * MODIFIER) + 0.0f, (y * MODIFIER) + 0.0f, 0.0f);
    glVertex3f((x * MODIFIER) + 0.0f, (y * MODIFIER) + MODIFIER, 0.0f);
    glVertex3f((x * MODIFIER) + MODIFIER, (y * MODIFIER) + MODIFIER, 0.0f);
    glVertex3f((x * MODIFIER) + MODIFIER, (y * MODIFIER) + 0.0f, 0.0f);

    glEnd();

}