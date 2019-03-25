#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

// header crane!!
#include "src/crane.h"

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

// keys!!
#define KEY_ESC 27
#define KEY_Q 'q'
#define KEY_W 'w'
#define KEY_O 'o'
#define KEY_P 'p'
#define KEY_1 '1'
#define KEY_2 '2'
#define KEY_3 '3'
#define KEY_8 '8'
#define KEY_9 '9'
#define KEY_0 '0'

// size window!!
float wxsize = 800;
float wysize = 500;

float mxsize = wxsize/2;
float mysize = wysize/2;

float zaxis = 50;

float xmove = 300;
float ymove = 200;

// crane's variables !!
float base_width	= 100;
float base_height	= 20;

float a_angle 		= 60;
float a_width		= 400;
float a_height		= 15;

float b_angle		= a_angle-90;
float b_width 		= 250;
float b_height 		= 13;

float l_width		= 200;
float c_width		= 30;

float angle_speed	= 2;
float width_speed	= 2;

void TPaint(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-mxsize+xmove,mxsize+xmove,-mysize+ymove,mysize+ymove, -zaxis, zaxis);
	
	// function to draw the crane!!
	TDrawCrane(base_width, base_height, \
		a_angle, a_width, a_height, \
		b_angle, b_width, b_height, \
		l_width, c_width);

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
	glOrtho(-mxsize+xmove,mxsize+xmove,-mysize+ymove,mysize+ymove, -zaxis, zaxis);

	glMatrixMode(GL_MODELVIEW);
}

void TInitScene(){
}

void TWKey(unsigned char key, int x, int y) {
	// kes detected!!
    switch (key) {
        case KEY_ESC:
            exit(0);
            break;
        case KEY_Q:
        	if(a_angle<90)
        		a_angle += angle_speed;
        	break;
        case KEY_W:
        	if(a_angle>0)
        		a_angle -= angle_speed;
        	break;
        case KEY_O:
        	if(b_angle<a_angle)
        		b_angle += angle_speed;
        	break;
        case KEY_P:{
        	if(b_angle>(-180+a_angle))
        		b_angle -= angle_speed;
        	break;
        }
        case KEY_1:
        	a_width += width_speed;
        	break;
        case KEY_8:
        	a_width -= width_speed;
        	break;
        case KEY_2:
        	b_width += width_speed;
        	break;
        case KEY_9:
        	b_width -= width_speed;
        	break;
        case KEY_3:
        	l_width += width_speed;
        	break;
        case KEY_0:
        	l_width -= width_speed;
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
}

// g++ figure.cpp -o figure.out -lglut -lGL
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(wxsize, wysize);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Transformations");
    
    TInit();
    TInitScene();

    glutDisplayFunc(&TPaint);
    glutReshapeFunc(&TWRedraw);
    glutKeyboardFunc(&TWKey);

    glutIdleFunc(&TIdle);
    // glutTimerFunc(0, TTimer, 0);

    glutMainLoop();

    return 0;
}