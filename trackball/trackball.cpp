#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <pthread.h>

#include "src/trackball.h"
#include "src/floor.h"
#include "src/solid.h"

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define KEY_ESC 27
#define PI 3.14159265

float wsize = 600;
float msize = wsize/2;

float zfar = 100;
float time_base = 0;
float time_current = 0;

float angles[2];
float position[4];
float eyes[3];
float center[3];
float axis[3];
float up[3];

float delta_xangle = 0;
float delta_yangle = 0;

float move = 0;
int initx = -1;
int inity = -1;

float floor_size = 100;
float axis_size = 20;

float delta = 0.5;

void TPaint(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	
	gluLookAt(eyes[0], eyes[1], eyes[2],
		eyes[0]+center[0], eyes[1]+center[1], eyes[2]+center[2],
		0,1,0);

	glColor3f(1, 0, 0);
	TDrawFloor(floor_size, 0, floor_size);
	glColor3f(0, 0, 1);
	TDrawCube(0,0.75,-5,1);
	// TAxis(axis[0],axis[1],axis[2],axis_size);

	time_base = time_current;
	glutSwapBuffers();
	glFlush();
}

void TIdle(){   glutPostRedisplay();    }

void TInit(void){
	eyes[0]   = 0;	eyes[1]   = 1;	eyes[2]   = 0;
	axis[0]   = 0;	axis[1]   = 0;	axis[2]   = 0;
	center[0] = 0;	center[1] = 0;	center[2] = -1;	

	angles[0] = 0;	angles[1] = 0;
	glClearColor(RED, GREEN, BLUE, ALPHA);
}

void TWRedraw(GLsizei _w, GLsizei _h){	
	if(_h == 0)	_h = 1;

	float ratio = _w/_h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, _w, _h);
	gluPerspective(45, ratio, 1, zfar);

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
		case GLUT_KEY_UP:{			
			// eyes[0] += delta*center[0];
			eyes[2] += delta;//*center[2];
			break;
		}
		case GLUT_KEY_DOWN:{
			// eyes[0] += delta*center[0];
			eyes[2] -= delta;//*center[2];
			break;
		}
		case GLUT_KEY_LEFT:{
			eyes[0] -= delta;//*center[0];
			// eyes[2] += delta*center[2];
			break;
		}
		case GLUT_KEY_RIGHT:{
			eyes[0] += delta;//*center[0];
			// eyes[2] = delta*center[2];
			break;
		}
	}
}

void TMoveCamera(float _delta){
	eyes[0] = _delta*center[0];
	eyes[1] = _delta*center[1];
	eyes[2] = _delta*center[2];
}

void TCallbackMouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON){
		// when the button is released
        if (state == GLUT_UP) {
            angles[0] += delta_xangle;
            angles[1] += delta_yangle;

            initx = -1;
            inity = -1;
        }
        else{
            initx = x;
            inity = y;
        }
	}
}

void TCallbackMotion(int x, int y){
	if (initx >= 0 and inity >= 0) {

        delta_xangle = (x-initx) * 0.001f;
        delta_yangle = (y-inity) * 0.001f;
                
        center[0] = sin(angles[1] + delta_yangle)*sin(angles[0] + delta_xangle);
        center[2] = sin(angles[1] + delta_yangle)*cos(angles[0] + delta_xangle);
        center[1] = cos(angles[1] + delta_yangle);
    }
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