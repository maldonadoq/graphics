#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#include "src/poly.h"

#define KEY_ESC 27

float size   = 600;             // windows size
float msize  = size/2;          // middle size
float tmove  = 150;             // translate camera
float pradio = 300;             // length line

float mtime = 0;                // time init
float speed = 0.05;             // time's speed
float angle = 0;                // angle

float init[3]   = {0,0,0};      // (x,y,z) init
float center[3] = {0,-250,0};   // (x,y,z) circle's center
float r         = 50;           // circle's radius

void TPaint(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();   
    glOrtho(-msize,msize,-msize-tmove,msize-tmove, -1.0f, 1.0f);

    float tangle = cos(mtime);

    center[0] = -pradio*sin(tangle);
    center[1] = -pradio*cos(tangle);

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex2f(init[0],   init[1]);
        glVertex2f(center[0], center[1]);
    glEnd();

    TDrawCircle(center[0],center[1],r,10);

    glutSwapBuffers();
}

void TIdle(){
    glutPostRedisplay();
}

void TInit(void) {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void TWRedraw(GLsizei _w, GLsizei _h){
    glViewport(0, 0, _w, _h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-msize,msize,-msize-tmove,msize-tmove, -1.0f, 1.0f);
}

void TWKey(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:
            exit(0);
            break;
        default:
            break;
    }
}

/*
    Timer Function
    1s -> 6 call
*/
void TTimer(int _t){
    glutPostRedisplay();
    glutTimerFunc(1000/60, TTimer, 0);

    mtime += speed;
}

// g++ animation.cpp -o animation.out -lglut -lGL
int main(int argc, char *argv[]){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(size, size);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("OpenGL");
    TInit();

    glutDisplayFunc(TPaint);

    glutReshapeFunc(&TWRedraw);
    glutKeyboardFunc(&TWKey);
    glutIdleFunc(&TIdle);
    glutTimerFunc(0, TTimer, 0);

    glutMainLoop();

    return 0;
}