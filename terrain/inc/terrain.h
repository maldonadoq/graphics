#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <GL/glut.h>

void DrawGrid(float _dim)
{
    _dim /= 2.0f;
    glBegin(GL_LINES);
    for(float i=-_dim;i<=_dim;i+=0.5)
    {
        glVertex3f(i,0,-_dim);
        glVertex3f(i,0,_dim);

        glVertex3f(-_dim,0,i);
        glVertex3f(_dim,0,i);
    }
    glEnd();
}

#endif