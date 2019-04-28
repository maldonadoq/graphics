#ifndef _HOUSE_H_
#define _HOUSE_H_

void Walls(glm::vec3 _cen, int _width, int _height, int _long){		
	// Wall
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height, _cen.z - _long);
		glVertex3f(_cen.x + _width, _cen.y + _height, _cen.z + _long);
		glVertex3f(_cen.x + _width, _cen.y, _cen.z + _long);
		glVertex3f(_cen.x + _width, _cen.y, _cen.z - _long);				
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height, _cen.z + _long);
		glVertex3f(_cen.x - _width, _cen.y + _height, _cen.z - _long);
		glVertex3f(_cen.x - _width, _cen.y, _cen.z - _long);
		glVertex3f(_cen.x - _width, _cen.y, _cen.z + _long);				
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height, _cen.z +_long);
		glVertex3f(_cen.x - _width, _cen.y + _height, _cen.z +_long);
		glVertex3f(_cen.x - _width, _cen.y, _cen.z +_long);
		glVertex3f(_cen.x + _width, _cen.y, _cen.z +_long);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height, _cen.z -_long);
		glVertex3f(_cen.x + _width, _cen.y + _height, _cen.z -_long);		
		glVertex3f(_cen.x + _width, _cen.y, _cen.z -_long);
		glVertex3f(_cen.x - _width, _cen.y, _cen.z -_long);
	glEnd();
	
	// Triangles
	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(_cen.x         , _cen.y + (_height*1.5),_cen.z + _long);
		glVertex3f(_cen.x - _width, _cen.y + _height      ,_cen.z + _long);
		glVertex3f(_cen.x + _width, _cen.y + _height      ,_cen.z + _long);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(_cen.x         , _cen.y + (_height*1.5),_cen.z - _long);
		glVertex3f(_cen.x + _width, _cen.y + _height      ,_cen.z - _long);
		glVertex3f(_cen.x - _width, _cen.y + _height      ,_cen.z - _long);
	glEnd();
}

void Roof(glm::vec3 _cen, int _width, int _height, int _long){
	// Roof	
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 1.0f, 0.0f);
		glVertex3f(_cen.x		  , _cen.y + (_height*1.5), _cen.z - _long);
		glVertex3f(_cen.x		  , _cen.y + (_height*1.5), _cen.z + _long);
		glVertex3f(_cen.x + _width, _cen.y + _height	  , _cen.z + _long);
		glVertex3f(_cen.x + _width, _cen.y + _height	  , _cen.z - _long);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(_cen.x		  , _cen.y + (_height*1.5), _cen.z + _long);
		glVertex3f(_cen.x		  , _cen.y + (_height*1.5), _cen.z - _long);		
		glVertex3f(_cen.x - _width, _cen.y + _height	  , _cen.z - _long);
		glVertex3f(_cen.x - _width, _cen.y + _height	  , _cen.z + _long);
	glEnd();
}

void TWalls(glm::vec3 _cen, int _width, int _height, int _long){		
	// Wall
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height, _cen.z - _long);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height, _cen.z + _long);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y, _cen.z + _long);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y, _cen.z - _long);				
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height, _cen.z + _long);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height, _cen.z - _long);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y, _cen.z - _long);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y, _cen.z + _long);				
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height, _cen.z +_long);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height, _cen.z +_long);		

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y, _cen.z +_long);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y, _cen.z +_long);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height, _cen.z -_long);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height, _cen.z -_long);		

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y, _cen.z -_long);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y, _cen.z -_long);
	glEnd();
	
	// Triangles
	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
				
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(_cen.x         , _cen.y + (_height*1.5),_cen.z + _long);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height      ,_cen.z + _long);
				
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height      ,_cen.z + _long);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, -1.0f);
				
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(_cen.x         , _cen.y + (_height*1.5),_cen.z - _long);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height      ,_cen.z - _long);
				
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height      ,_cen.z - _long);
	glEnd();
}

void TRoof(glm::vec3 _cen, int _width, int _height, int _long/*, float _n*/){
	// Roof	
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 1.0f, 0.0f);
		
		glTexCoord2f(1.0f, 1.0f);
		// glTexCoord2f(_n, _n);
		glVertex3f(_cen.x		  , _cen.y + (_height*1.5), _cen.z - _long);

		glTexCoord2f(0.0f, 1.0f);
		// glTexCoord2f(0.0f, _n);
		glVertex3f(_cen.x		  , _cen.y + (_height*1.5), _cen.z + _long);		
		
		glTexCoord2f(0.0f, 0.0f);
		// glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height	  , _cen.z + _long);
				
		glTexCoord2f(1.0f, 0.0f);
		// glTexCoord2f(_n, 0.0f);
		glVertex3f(_cen.x + _width, _cen.y + _height	  , _cen.z - _long);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 1.0f, 0.0f);
		
		glTexCoord2f(1.0f, 1.0f);
		// glTexCoord2f(_n, _n);
		glVertex3f(_cen.x		  , _cen.y + (_height*1.5), _cen.z + _long);

		glTexCoord2f(0.0f, 1.0f);
		// glTexCoord2f(0.0f, _n);
		glVertex3f(_cen.x		  , _cen.y + (_height*1.5), _cen.z - _long);		
		
		glTexCoord2f(0.0f, 0.0f);
		// glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height	  , _cen.z - _long);
				
		glTexCoord2f(1.0f, 0.0f);
		// glTexCoord2f(_n, 0.0f);
		glVertex3f(_cen.x - _width, _cen.y + _height	  , _cen.z + _long);
	glEnd();
}

void Door(glm::vec3 _cen, int _width, int _height, int _long){
	// Door
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(_cen.x + _width/2, _cen.y + _height, _cen.z +_long);
		glVertex3f(_cen.x - _width/2, _cen.y + _height, _cen.z +_long);
		glVertex3f(_cen.x - _width/2, _cen.y, _cen.z +_long);
		glVertex3f(_cen.x + _width/2, _cen.y, _cen.z +_long);
	glEnd();
}

void TDoor(glm::vec3 _cen, int _width, int _height, int _long){
	// Door
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(_cen.x + _width/2, _cen.y + _height, _cen.z +_long);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(_cen.x - _width/2, _cen.y + _height, _cen.z +_long);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(_cen.x - _width/2, _cen.y, _cen.z +_long);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(_cen.x + _width/2, _cen.y, _cen.z +_long);
	glEnd();
}

#endif