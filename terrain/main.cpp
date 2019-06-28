#include <iostream>
#include <GL/glut.h>
#include <glm/glm.hpp>

#include "../utils/camera.h"
#include "inc/terrain.h"

#define RED   	0
#define GREEN 	0
#define BLUE  	0
#define ALPHA 	1
#define KEY_ESC 27

float wsize = 500;
float hsize = 500;

int type = 1;

string filename = "data/fontvieille.txt";
string texture  = "data/fontvieille.tga";

TTerrain *terrain;
TCamera *camera;

// dt init-time time
glm::vec3 etime(0,0,0);
glm::vec2 mouse(0,0);
glm::vec2 delta(0,0);
glm::vec3 center(0,0,0);
glm::vec3 move(-2500,-1500,-4000);

void Draw(){
	etime[2] = glutGet(GLUT_ELAPSED_TIME);		// time
	etime[0] = (etime[2] - etime[1])/1000.0f;	// delta time
	etime[1] = etime[2];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective( camera->m_perspective[0], camera->m_perspective[1],
					camera->m_perspective[2], camera->m_perspective[3]);

	glTranslatef(move.x,move.y,move.z);
	glRotatef(delta.x, 0.0, 1.0, 0.0);
	glRotatef(delta.y, 1.0, 0.0, 0.0);
	
	switch(type){
		case 1:{
			terrain->draw_vertex();
			break;
		}
		case 2:{
			terrain->draw_triangles();
			break;
		}
		case 3:{
			terrain->draw();
			break;
		}
		default:
			break;
	}
	
	glutSwapBuffers();
	glFlush();
}

void WRedraw(GLsizei _w, GLsizei _h){
	glViewport(0, 0, _w, _h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void Init(void){	
	GLfloat position[] = { -2500.0f, -1500.0f, 2500.0f, 1.0f };

	glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
	glClearColor(RED, GREEN, BLUE, ALPHA);

    float LightA[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float LightD[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float LightS[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT,  LightA);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightD);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightS);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	terrain->init(filename, texture);
}

void Keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:{
            exit(0);
            break;
		}
		case 'Q':
		case 'q':{
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            break;
        }
        case 'W':
		case 'w':{
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            break;
        }
        case '1':{
            type = 1;
            break;
        }
        case '2':{
            type = 2;
            break;
        }
        case '3':{
            type = 3;
            break;
        }
        default:
            break;
    }
}

void Mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		mouse.x = x;
		mouse.y = y;
	}
}


void MouseMotion(int x, int y){
	delta.x += (x - mouse.x)/10;
	delta.y += (y - mouse.y)/10;
	
	mouse.x = x;
	mouse.y = y;
	glutPostRedisplay();
}

void KeyboardDown(int c, int x, int y){
	switch(c){
		case GLUT_KEY_UP:
			move.z += 25.0f;
			break;
		case GLUT_KEY_DOWN:
			move.z -= 25.0f;
			break;
		case GLUT_KEY_LEFT:
			move.x += 25.0f;
			break;
		case GLUT_KEY_RIGHT:
			move.x -= 25.0f;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void Idle(){
    glutPostRedisplay();
}

// build: g++ main.cpp -o main.out -lGL -lglut -lGLU -lfreeimage
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(wsize, hsize);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Map");

	camera = new TCamera(45, wsize/hsize, 0.01f, 10000);
	terrain = new TTerrain(50, -50, 101, 101);

	Init();

    glutDisplayFunc(&Draw);
    glutReshapeFunc(&WRedraw);

    glutMouseFunc(&Mouse);
	glutMotionFunc(&MouseMotion);

    glutKeyboardFunc(&Keyboard);
    glutSpecialFunc(&KeyboardDown);

    glutIdleFunc(&Idle);

    glutMainLoop();

    delete camera;
    return 0;
}