#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <GL/glut.h>

void TDrawFloor(float _x, float _y, float _z){	
	glBegin(GL_QUADS);
		glVertex3f(-_x, _y, -_z);
		glVertex3f(-_x, _y,  _z);
		glVertex3f( _x, _y,  _z);
		glVertex3f( _x, _y, -_z);
	glEnd();
}

#endif