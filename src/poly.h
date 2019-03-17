#ifndef _FIGURES_H_
#define _FIGURES_H_

#include <GL/glut.h>

#define PI 3.14159265

/*
	Draw Square
	_x    center x
	_y    center y
	_size edge size
*/
void TDrawSquare(float _x, float _y, float _size){
	float tmp = _size/2;
	glBegin(GL_LINE_LOOP);
		glColor3f(0,0.5,0);

		glVertex2f(_x-tmp, _y+tmp);
		glVertex2f(_x+tmp, _y+tmp);
		glVertex2f(_x+tmp, _y-tmp);
		glVertex2f(_x-tmp, _y-tmp);

	glEnd();
}

void TDrawCircle(float _x, float _y, float _r, int _segm) {
    glBegin(GL_LINE_LOOP);    
		glColor3d(0,0.5,0);
		float x, y, theta;    		
		for(int i = 0; i < _segm; i++){
		    theta = (float)(2*PI*i)/_segm;
		    x = _r*cos(theta);
		    y = _r*sin(theta);
		    glVertex2d(x+_x, y+_y);
		}
    glEnd();
}

void TDrawCircles(double _x, double _y, double _rad, unsigned _circles, double _reduction){
	double tx = _x;
	double ty = _y;

	double rad = _rad;
	int segm = 50;
	double trad;

	for(unsigned i=0; i<_circles; i++){
		TDrawCircle(tx,ty,rad,segm);

		trad = rad-(rad*_reduction/100);
		tx = tx-(rad-trad);
		rad = trad;
	}
}

void TDrawAdjacentCircle(double _x, double _y, double _rad, unsigned _circles, double _reduction){
	double tx = _x;
	double ty = _y;

	double rad = _rad;
	int segm = 50;

	double trad;	

	for(unsigned i=0; i<_circles; i++){
		TDrawCircle(tx,ty,rad,segm);
		trad = rad-(rad*_reduction/100);
		tx = tx+rad+trad;
		rad = trad;
	}
}

void TDrawAdjacentCircleAngle(double _x, double _y, double _rad, unsigned _circles, double _reduction, double _angle){
	double tx = _x;
	double ty = _y;

	double rad = _rad;
	int segm = 50;

	double trad;
	double radian = _angle*PI/180;

	for(unsigned i=0; i<_circles; i++){
		TDrawCircle(tx,ty,rad,segm);
		trad = rad-(rad*_reduction/100);
		tx = tx + ((rad+trad)*cos(radian));
		ty = ty + ((rad+trad)*sin(radian));
		rad = trad;
	}
}

#endif