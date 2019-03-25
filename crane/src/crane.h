#ifndef _CRANE_H_
#define _CRANE_H_

#define PI 3.14159265

// draw rectangle to move the crane!!!
// good rectangle!!
void TDrawRectangle(float _x, float _y, float _width, float _height){
	float _h = _height/2;
	glBegin(GL_QUADS);		
		glVertex2f(_x     , -_h +_y);
		glVertex2f(_width+_x, -_h +_y);
		glVertex2f(_width+_x, _h +_y);
		glVertex2f(_x     , _h +_y);
	glEnd();
}

// function to draw crane
void TDrawCrane(float _width, float _height,
	float _anglea, float _widtha, float _heighta,
	float _angleb, float _widthb, float _heightb,
	float _widthl, float _widthc){

	// draw base rectangle!!
	glColor3f(1,0,0);
	TDrawRectangle(-_width/2, -_height/2, _width, _height);	

	// draw first arm!!
	glPushMatrix();
		// angle a!!
		glRotatef(_anglea,0,0,1);
		glColor3f(0,1,0);
		TDrawRectangle(0, 0, _widtha, _heighta);
	glPopMatrix();	

	float atmp  = (_anglea*PI)/180;
	float xtmp = _widtha*cos(atmp);
	float ytmp = _widtha*sin(atmp);

	// second arm!
	glPushMatrix();
		// angle b
		glTranslatef(xtmp,ytmp,0);
		glRotatef(_angleb,0,0,1);
		glColor3f(0,0,1);		
		TDrawRectangle(0, 0, _widthb, _heightb);		
	glPopMatrix();

	float btmp  = (_angleb*PI)/180;
	xtmp += _widthb*cos(btmp);
	ytmp += _widthb*sin(btmp);	

	// line!!
	glColor3f(1,1,1);
	glBegin(GL_LINES);		
		glVertex2f(xtmp,ytmp);
		glVertex2f(xtmp,ytmp-_widthl);
	glEnd();

	// cube!!
	glTranslatef(xtmp,ytmp-_widthl,0);
	glColor3f(0.5,0,0.5);
	glutSolidCube(_widthc);	
}

#endif