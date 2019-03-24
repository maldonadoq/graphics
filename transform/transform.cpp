#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#include "src/transformation.h"

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define KEY_ESC 27

float wsize = 50;
float msize = wsize/2;

float teapot_angle  	= 0;
float teapot_speed 		= 3;
float teapot_translate  = 10;

float circle_direct 	= 1;
float circle_xpos     	= 0;
float circle_ypos     	= 0;
float circle_radius    	= 1.5;
float circle_translate	= 10;
float circle_direction	= 1;
float circle_speed		= 0.1;

float cube_angle  		= 0;
float cube_speed 		= 5;
float cube_translate  	= 10;

float torus_angle  		= 0;
float torus_speed 		= 3*teapot_speed;
float torus_translate  	= 5;
float torus_inner		= 0.3;

void TPaint(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
	glOrtho(-msize,msize,-msize,msize, -25.0f, 25.0f);


	// glutSolidTeapot(10);
	// TTranslate(teapot_angle, teapot_translate);
	// TTranslateIdaVuelta(teapot_angle, teapot_translate,
	//		circle_direction, circle_xpos, circle_radius);
	TTranslateComplex(teapot_angle, teapot_translate, \
		circle_direction, circle_xpos, circle_radius, \
		cube_angle, cube_translate, \
		torus_angle, torus_translate, torus_inner);


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
	glOrtho(-msize,msize,-msize,msize, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}

void TInitScene(){
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

    if(abs(circle_xpos) > circle_translate){
		circle_direction = -1*circle_direction;
	}

	circle_xpos  += circle_direction*circle_speed;
	teapot_angle += teapot_speed;
	cube_angle   += cube_speed;
	torus_angle  += torus_speed;
}

// g++ figure.cpp -o figure.out -lglut -lGL
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Transformations");
    
    TInit();
    TInitScene();

    glutDisplayFunc(&TPaint);
    glutReshapeFunc(&TWRedraw);
    glutKeyboardFunc(&TWKey);

    glutIdleFunc(&TIdle);
    glutTimerFunc(0, TTimer, 0);

    glutMainLoop();

    return 0;
}