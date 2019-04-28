#ifndef _TREE_H_
#define _TREE_H_

void Stem(glm::vec3 _cen, glm::vec3 _pos, int _r, int _h){
	glPushMatrix();
		glTranslatef(
			_cen.x + _pos.x,
			_cen.y + _pos.y,
			_cen.z + _pos.z
		);
		
		GLUquadricObj *qobj;
		qobj = gluNewQuadric();

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		gluCylinder(qobj, (_r/2)-1, _r/2, _h, 8, 8);
	glPopMatrix();	
}

void Sphere(glm::vec3 _cen, glm::vec3 _pos, int _r){
	glPushMatrix();
		glTranslatef(
				_cen.x + _pos.x,
				_cen.y + _pos.y,
				_cen.z + _pos.z
			);		
		glutSolidSphere(_r,15,15);
	glPopMatrix();
}

#endif