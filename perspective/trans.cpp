#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define KEY_ESC 27

float wsize = 50;
float msize = wsize/2;

void TPaint(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-msize,msize,-msize,msize, -25.0f, 25.0f);


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

void TTimer(int _t){
    glutPostRedisplay();
    glutTimerFunc(1000/60, TTimer, 0);
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