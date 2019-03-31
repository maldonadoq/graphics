#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#include "src/trackball.h"

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define KEY_ESC 27

float wsize = 600;
float msize = wsize/2;

float size = 5;
float ax, ay, az = 0;
float zfar = 40;

float anx = 0;
float any = 0;
float anz = 0;

float speed = 10;

void TPaint(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(0,wsize,0,wsize, -25.0f, 25.0f);

	gluPerspective(45, 1, 1, 100);
	glTranslatef(0,0,-zfar);
	TAxis(ax,ay,az,size, anx, any, anz);

	glutSwapBuffers();
	glFlush();
}

void TIdle(){   glutPostRedisplay();    }

void TInit(void){
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}

void TWRedraw(GLsizei _w, GLsizei _h){
	glViewport(0, 0, _w, _h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(0,wsize,0,wsize, -25.0f, 25.0f);
	gluPerspective(45, 1, 1, 100);

	glMatrixMode(GL_MODELVIEW);
}

void TInitScene(){
}

void TKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:
            exit(0);
            break;            		
        default:
            break;
    }
}

void TCallbackKeyboard(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			anx += speed;
			// std::cout << "up\n";
			break;
		case GLUT_KEY_DOWN:
			anx -= speed;
			// std::cout << "down\n";
			break;
		case GLUT_KEY_LEFT:
			any-= speed;
			// std::cout << "left\n";
			break;
		case GLUT_KEY_RIGHT:
			any += speed;
			// std::cout << "right\n";
			break;
	}
}

void TCallbackMouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		// std::cout << "[" << x << "," << y << "]\t";
		ax = x;
		ay = wsize-y;
	}
}

void TCallbackMotion(int x, int y){
	glutPostRedisplay();						
}

void TTimer(int _t){
    glutPostRedisplay();
    glutTimerFunc(1000/60, TTimer, 0);
}

// g++ figure.cpp -o figure.out -lglut -lGL
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(wsize, wsize);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Trackball");
    
    TInit();
    TInitScene();

    glutDisplayFunc(&TPaint);
    glutReshapeFunc(&TWRedraw);
    glutKeyboardFunc(&TKeyboard);

    glutIdleFunc(&TIdle);
    glutTimerFunc(0, TTimer, 0);

    glutSpecialFunc(&TCallbackKeyboard);
	glutMouseFunc(&TCallbackMouse);
	glutMotionFunc(&TCallbackMotion);

    glutMainLoop();

    return 0;
}