#ifndef _CRANE_H_
#define _CRANE_H_

#define PI 3.14159265

void TDrawRectangle(float _x, float _y, float _weight, float _height){
	float _h = _height/2;
	glBegin(GL_QUADS);		
		glVertex2f(_x     , -_h +_y);
		glVertex2f(_weight+_x, -_h +_y);
		glVertex2f(_weight+_x, _h +_y);
		glVertex2f(_x     , _h +_y);
	glEnd();
}

void TDrawCrane(float _weight, float _height,
	float _anglea, float _weighta, float _heighta,
	float _angleb, float _weightb, float _heightb,
	float _weightl, float _weightc){

	glColor3f(1,0,0);
	TDrawRectangle(-_weight/2, -_height/2, _weight, _height);	

	glPushMatrix();
		glRotatef(_anglea,0,0,1);
		glColor3f(0,1,0);
		TDrawRectangle(0, 0, _weighta, _heighta);
	glPopMatrix();	

	float atmp  = (_anglea*PI)/180;
	float xtmp = _weighta*cos(atmp);
	float ytmp = _weighta*sin(atmp);

	glPushMatrix();		
		glTranslatef(xtmp,ytmp,0);
		glRotatef(_angleb,0,0,1);
		glColor3f(0,0,1);		
		TDrawRectangle(0, 0, _weightb, _heightb);		
	glPopMatrix();

	float btmp  = (_angleb*PI)/180;
	xtmp += _weightb*cos(btmp);
	ytmp += _weightb*sin(btmp);	

	glColor3f(1,1,1);
	glBegin(GL_LINES);		
		glVertex2f(xtmp,ytmp);
		glVertex2f(xtmp,ytmp-_weightl);
	glEnd();

	glTranslatef(xtmp,ytmp-_weightl,0);
	glColor3f(0.5,0,0.5);
	glutSolidCube(_weightc);	
}

#endif