#ifndef _SOLID_H_
#define _SOLID_H_

void TDrawCube(float _x, float _y, float _z, float _size){
	glTranslatef(_x,_y,_z);
	glutSolidCube(_size);
}

#endif