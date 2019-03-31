#ifndef _TRACKBALL_H_
#define _TRACKBALL_H_

void TAxis(float _x, float _y, float _z, float _size,
	float _anx, float _any, float _anz){
	
	glRotatef(_anx,1,0,0);
	glRotatef(_any,0,1,0);
	glRotatef(_anz,0,0,1);

	glBegin(GL_LINES);
		// x
		glColor3f(1,0,0);
		glVertex3f(_x,_y,_z);
		glVertex3f(_x+_size,_y,_z);

		// y
		glColor3f(0,1,0);
		glVertex3f(_x,_y,_z);
		glVertex3f(_x,_y+_size,_z);

		// z
		glColor3f(0,0,1);
		glVertex3f(_x,_y,_z);
		glVertex3f(_x,_y,_z+_size);
	glEnd();
}

#endif