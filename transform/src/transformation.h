#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

#include <GL/glut.h>

void TTranslate(float _angle, float _move){
	glRotatef(_angle,0,0,1);
	glTranslatef(_move,0,0);

	glutSolidTeapot(1);
}

void TTranslateIdaVuelta(float _teapot_angle, float _teapot_translate,
		float _circle_direction, float _circle_xpos, float _circle_radius){

	glTranslatef(_circle_xpos,0,0);
	glColor3f(0,1,0);
    glutSolidSphere(_circle_radius,20,20);

	glPushMatrix();
		glRotatef(_teapot_angle,0,0,1);
		glTranslatef(_teapot_translate,0,0);
		glColor3f(0,0,1);
		glutSolidTeapot(1);
	glPopMatrix();
}

void TTranslateComplex(float _teapot_angle, float _teapot_translate,
		float _circle_direction, float _circle_xpos, float _circle_radius,
		float _cube_angle, float _cube_translate,
		float _torus_angle, float _torus_translate, float _torus_inner){

	glTranslatef(_circle_xpos,0,0);
	glColor3f(0,1,0);
    glutSolidSphere(_circle_radius,20,20);

	glPushMatrix();
		glRotatef(_teapot_angle,0,0,1);
		glTranslatef(_teapot_translate,0,0);
		glColor3f(0,0,1);
		glutSolidTeapot(1.3);

		glTranslatef(_torus_translate*sin(_torus_angle), 0.0, _torus_translate*cos(_teapot_angle));
	    glColor3f(1,1,0);
	    glutSolidTorus(_torus_inner,_torus_inner+0.2,20,20);
	glPopMatrix();

	glPushMatrix();
		glRotatef(_cube_angle,1,0,0);
		glTranslatef(0,_cube_translate,0);
		glColor3f(1,0,0);
		glutSolidCube(2.5);
	glPopMatrix();
}

#endif