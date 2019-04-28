#ifndef _FLOOR_H_
#define _FLOOR_H_

void SquareFloor(glm::vec3 _center, int _size){

	/*
		1-------4
		|		|
		|		|
		2-------3
	*/

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(_center.x + _size, _center.y, _center.z + _size);
		glVertex3f(_center.x + _size, _center.y, _center.z - _size);
		glVertex3f(_center.x - _size, _center.y, _center.z - _size);
		glVertex3f(_center.x - _size, _center.y, _center.z + _size);
	glEnd();
}

void TSquareFloor(glm::vec3 _center, int _size){
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(_center.x + _size, _center.y, _center.z + _size);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(_center.x + _size, _center.y, _center.z - _size);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_center.x - _size, _center.y, _center.z - _size);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(_center.x - _size, _center.y, _center.z + _size);
	glEnd();
}

#endif