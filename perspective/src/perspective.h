#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_

#include <GL/glut.h>

extern float segm;

#define PI 3.14159265

void TTranslate(float _angle, float _translate){	
	float _a = (float)_angle*PI/180;
	glTranslatef(_translate*cos(_a),_translate*sin(_a),0);

	glutSolidTeapot(2);
}

void TSolarSystem(float _sun_angle, float _sun_radius,
	float _earth_anglec, float _earth_anglet, float _earth_radius, float _earth_translate,
	float _moon_anglec, float _moon_anglet, float _moon_radius, float _moon_translate,
	float _mars_anglec, float _mars_anglet, float _mars_radius, float _mars_translate){	

	float xe = _earth_translate*sin(_earth_anglet);
	float ye = 0;
	float ze = _earth_translate*cos(_earth_anglet);

	gluLookAt(-20,-20,-20,xe,ye,ze,0,1,0);

	glPushMatrix();
		// Sun
		glColor3f(1,1,0);
		glRotatef(_sun_angle,0,1,0);
		glutSolidSphere(_sun_radius,segm,segm);
	glPopMatrix();

	glPushMatrix();
		// Earth
		glTranslatef(xe,ye,ze);
		glRotatef(_earth_anglec,0,1,0);
		glColor3f(0,0,1);		
		glutSolidSphere(_earth_radius,segm,segm);

		// Moon
		glTranslatef(_moon_translate*sin(_moon_anglet),0,_moon_translate*cos(_moon_anglet));
		glRotatef(_moon_anglec,0,1,0);
		glColor3f(1,1,1);
		glutSolidSphere(_moon_radius,segm,segm);
	glPopMatrix();

	glPushMatrix();
		// Mars
		glTranslatef(_mars_translate*sin(_earth_anglet), 0, _mars_translate*cos(_earth_anglet));
		glRotatef(_mars_anglec,0,1,0);
		glColor3f(0,1,0);
		glutSolidSphere(_mars_radius,segm,segm);	
	glPopMatrix();
}

#endif