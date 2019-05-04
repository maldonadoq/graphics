#ifndef _TRACKBALL_H_
#define _TRACKBALL_H_

#include <glm/glm.hpp>

class TCamera{
private:	
public:	
	glm::vec4 m_perspective;	// fovy,ratio,znear,zfar

	TCamera(float _fovy, float _ratio,
		float _znear, float _zfar){
		this->m_perspective = glm::vec4(_fovy, _ratio, _znear, _zfar);
	}

	TCamera(){
		this->m_perspective = glm::vec4(0,0,0,0);
	}

	~TCamera(){	};
};

void TAxis(float _x, float _y, float _z, float _size){
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