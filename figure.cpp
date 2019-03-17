#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#include "src/poly.h"

#define KEY_ESC 27

float size = 600;
float msize = size/2;

void TPaint(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();   
    glOrtho(-msize,msize,-msize,msize, -1.0f, 1.0f);

    TDrawSquare(-200,220,80);
    TDrawCircle(-100,220,40,50);
    TDrawCircles(0,220,40,10,25);
    TDrawAdjacentCircle(-200,100,60,10,25);
    TDrawAdjacentCircleAngle(-200,-100,60,10,25,10);

    glutSwapBuffers();
}

void TIdle(){   glutPostRedisplay();    }

void TInit(void) {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void TWRedraw(GLsizei _w, GLsizei _h){
    glViewport(0, 0, _w, _h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-msize,msize,-msize,msize, -1.0f, 1.0f);
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

    glutMainLoop();

    return 0;
}