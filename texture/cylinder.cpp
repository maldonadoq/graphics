#include <iostream>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "src/camera.h"

#define RED     0
#define GREEN   0
#define BLUE    0
#define ALPHA   1
#define KEY_ESC 27

float wsize = 600;
float hsize = 600;

TCamera *camera;

glm::vec3 etime(0,0,0);
glm::vec2 mouse(0,0);
glm::vec2 delta(0,0);

int choose = 1;

void Draw(){
    etime[2] = glutGet(GLUT_ELAPSED_TIME);      // time
    etime[0] = (etime[2] - etime[1])/1000.0f;   // delta time
    etime[1] = etime[2];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective( camera->m_perspective[0], camera->m_perspective[1],
                    camera->m_perspective[2], camera->m_perspective[3]);

    glTranslatef(0,0,-200);
    glRotatef(delta.x, 0.0, 1.0, 0.0);
    glRotatef(delta.y, 1.0, 0.0, 0.0);



    glColor3f(0.64f,0.16f,0.10f);
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();

    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluCylinder(qobj, 7, 10, 24, 8, 8);

    
    glutSwapBuffers();
    glFlush();
}

void WRedraw(GLsizei _w, GLsizei _h){
    glViewport(0, 0, _w, _h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( camera->m_perspective[0], camera->m_perspective[1],
                    camera->m_perspective[2], camera->m_perspective[3]);

    glMatrixMode(GL_MODELVIEW);
}

void Idle(){
    // engine->Update(etime[0]);
    glutPostRedisplay();
}

void Init(void){    
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

void InitScene(){
}

void WKey(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:
            exit(0);
            break;
        case '1':
            choose = 1;
            break;
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

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);  
    glutInitWindowSize(wsize, hsize);
    glutInitWindowPosition(50,10);
    glutCreateWindow("Textures");
    
    Init();
    InitScene();

    camera = new TCamera(45, wsize/hsize, 0.01f, 500);

    glutDisplayFunc(&Draw);
    glutReshapeFunc(&WRedraw);
    glutMouseFunc(&Mouse);
    glutMotionFunc(&MouseMotion);
    glutKeyboardFunc(&WKey);

    glutMainLoop();

    delete camera;
    return 0;
}