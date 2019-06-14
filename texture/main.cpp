#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "src/TextureManager.h"
#include "../utils/camera.h"
#include "src/scene.h"

#define RED   	0
#define GREEN 	0
#define BLUE  	0
#define ALPHA 	1
#define KEY_ESC 27

float wsize = 600;
float hsize = 600;

int textures_id[4] = {0,0,0,0};

TCamera *camera;

glm::vec3 etime(0,0,0);
glm::vec2 mouse(0,0);
glm::vec2 delta(0,0);
glm::vec3 center(0,-20,0);
glm::vec3 home(-10,0,0);

float hwidth = 6;
float hheight = 8;
float hlong = 10;
float fsize = 40;

TLight light = {
	glm::vec4(5.0f, 7.5f, 10.0f, 0.0f),
	glm::vec4(0.2f, 0.2f, 0.2f , 1.0f),
	glm::vec4(0.5f, 0.5f, 0.5f , 1.0f),
	glm::vec4(1.0f, 1.0f, 1.0f , 1.0f)
};

int choose = 1;

void Draw(){
	etime[2] = glutGet(GLUT_ELAPSED_TIME);		// time
	etime[0] = (etime[2] - etime[1])/1000.0f;	// delta time
	etime[1] = etime[2];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective( camera->m_perspective[0], camera->m_perspective[1],
					camera->m_perspective[2], camera->m_perspective[3]);

	glTranslatef(0,0,-75);
	glRotatef(delta.x, 0.0, 1.0, 0.0);
	glRotatef(delta.y, 1.0, 0.0, 0.0);

	switch(choose){
		case 1:
			Normal(center, home);
			break;
		case 2:
			Material(center, home);
			break;
		case 3:
			Texture(center, home);
			break;
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
	// gluPerspective( camera->m_perspective[0], camera->m_perspective[1], \
					camera->m_perspective[2], camera->m_perspective[3]);

	glMatrixMode(GL_MODELVIEW);
}

void Idle(){
	glutPostRedisplay();
}

void Init(void){		
	/*
	glEnable(GL_DEPTH_TEST);
	glClearColor(RED, GREEN, BLUE, ALPHA);
	*/
	
	glShadeModel(GL_SMOOTH);
	// glShadeModel(GL_FLAT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(RED, GREEN, BLUE, ALPHA);
	
}

void EnableLight(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(light.m_ambient));

	glLightfv(GL_LIGHT0, GL_AMBIENT , glm::value_ptr(light.m_ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE , glm::value_ptr(light.m_diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(light.m_specular));
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(light.m_position));
}

void DisableLight(){
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

void EnableTexture(){
	glEnable(GL_TEXTURE_2D);
	// glEnable(GL_BLEND);
}

void DisableTexture(){
	glDisable(GL_TEXTURE_2D);
	// glDisable(GL_BLEND);
}

void InitScene(){
}

void WKey(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:
            exit(0);
            break;
		case '1':{
			choose = 1;
			DisableLight();
			DisableTexture();
			break;
        }
		case '2':{
			choose = 2;
			EnableLight();
			DisableTexture();
            break;
        }
		case '3':{
			choose = 3;
			EnableLight();
			EnableTexture();
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

// g++ main.cpp TextureManager.cpp -lglut -lGL -lGLU -lfreeimage -o main.out
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(wsize, hsize);
	glutInitWindowPosition(50,10);
	glutCreateWindow("Textures");
    
    Init();
    InitScene();

	camera = new TCamera(45, wsize/hsize, 0.01f, 500);
	textures_id[0] = TextureManager::Inst()->LoadTexture("data/grass.jpg", GL_BGR_EXT, GL_RGB);
	textures_id[1] = TextureManager::Inst()->LoadTexture("data/wall.jpg", GL_BGR_EXT, GL_RGB);
	textures_id[2] = TextureManager::Inst()->LoadTexture("data/tile.jpg", GL_BGR_EXT, GL_RGB);
	textures_id[3] = TextureManager::Inst()->LoadTexture("data/door.jpg", GL_BGR_EXT, GL_RGBA);

    glutDisplayFunc(&Draw);
    glutReshapeFunc(&WRedraw);

    glutMouseFunc(&Mouse);
	glutMotionFunc(&MouseMotion);

    glutKeyboardFunc(&WKey);
    glutIdleFunc(&Idle);

    glutMainLoop();

    delete camera;
    return 0;
}