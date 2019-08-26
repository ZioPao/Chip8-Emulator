#include <iostream>
#include <time.h>
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "chip8.h"
#include "main.h"


int main(int argc, char **argv) {

    //Init
    init_graphics(argc, argv);
    init_input();

    c8.initialize();      //emu initialization

    if (!c8.load_game("pong"))
        exit(1);

    glutMainLoop();     //todo
    return 0;
}

void init_graphics(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(display_width, display_height);
    glutInitWindowPosition(320,320);
    int id = glutCreateWindow("Emulator");

    if (id < 1)
        exit(1);

    glutDisplayFunc(draw_graphics);
    glutIdleFunc(draw_graphics);
    glutReshapeFunc(reshape_window);
    glutKeyboardFunc(keyboard_down);
    glutKeyboardFunc(keyboard_up);
}

void init_input() {
    //todo stuff
}

void draw_graphics() {
    c8.emulate_cycle();       //One cycle

    if(c8.draw_flag){
        glClear(GL_COLOR_BUFFER_BIT);   //Clear framebuffer
        update_quads();

        // Swap buffers!
        glutSwapBuffers();

        // Processed frame
        c8.draw_flag = false;
    }



    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
    glVertex3f(-0.5,0,0.0);
    glVertex3f(0.0, 0.0, 0.0);

    glVertex3f(0.0, 0.5, 0);
    glVertex3f(-0.5, 0.5, 0);

    glEnd();

    glutSwapBuffers();
*/


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
void reshape_window(GLsizei w, GLsizei h){
    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);

    // Resize quad
    display_width = w;
    display_height = h;
}

void keyboard_down(unsigned char key, int x, int y){

        if(key == 27)    // esc
            exit(0);

        if(key == '1')		c8.key[0x1] = 1;
        else if(key == '2')	c8.key[0x2] = 1;
        else if(key == '3')	c8.key[0x3] = 1;
        else if(key == '4')	c8.key[0xC] = 1;

        else if(key == 'q')	c8.key[0x4] = 1;
        else if(key == 'w')	c8.key[0x5] = 1;
        else if(key == 'e')	c8.key[0x6] = 1;
        else if(key == 'r')	c8.key[0xD] = 1;

        else if(key == 'a')	c8.key[0x7] = 1;
        else if(key == 's')	c8.key[0x8] = 1;
        else if(key == 'd')	c8.key[0x9] = 1;
        else if(key == 'f')	c8.key[0xE] = 1;

        else if(key == 'z')	c8.key[0xA] = 1;
        else if(key == 'x')	c8.key[0x0] = 1;
        else if(key == 'c')	c8.key[0xB] = 1;
        else if(key == 'v')	c8.key[0xF] = 1;
}

void keyboard_up(unsigned char key, int x, int y){

    if(key == '1')		c8.key[0x1] = 0;
    else if(key == '2')	c8.key[0x2] = 0;
    else if(key == '3')	c8.key[0x3] = 0;
    else if(key == '4')	c8.key[0xC] = 0;

    else if(key == 'q')	c8.key[0x4] = 0;
    else if(key == 'w')	c8.key[0x5] = 0;
    else if(key == 'e')	c8.key[0x6] = 0;
    else if(key == 'r')	c8.key[0xD] = 0;

    else if(key == 'a')	c8.key[0x7] = 0;
    else if(key == 's')	c8.key[0x8] = 0;
    else if(key == 'd')	c8.key[0x9] = 0;
    else if(key == 'f')	c8.key[0xE] = 0;

    else if(key == 'z')	c8.key[0xA] = 0;
    else if(key == 'x')	c8.key[0x0] = 0;
    else if(key == 'c')	c8.key[0xB] = 0;
    else if(key == 'v')	c8.key[0xF] = 0;
}