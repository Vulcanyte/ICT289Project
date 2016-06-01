
#include "MakeRoom.h"
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat s; // scale of the cube (room)

void getCubeScale(GLfloat scale)
{
    if(scale > 0.0)
    {
        s = scale;
    }
    else
    {
        s = 1.0;
    }
}

void cubeSideOne()
{
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0);
    glVertex3f(-s, -s, -s);

    glTexCoord2f(0.0,1.0);
    glVertex3f(s, -s, -s);

    glTexCoord2f(1.0,1.0);
    glVertex3f(s, -s, s);

    glTexCoord2f(1.0,0.0);
    glVertex3f(-s, -s, s);
}

void cubeSideTwo()
{
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0);
    glVertex3f(-s, s, -s);

    glTexCoord2f(0.0,1.0);
    glVertex3f(s, s, -s);

    glTexCoord2f(1.0,1.0);
    glVertex3f(s, s, s);

    glTexCoord2f(1.0,0.0);
    glVertex3f(-s, s, s);
}

void cubeSideThree()
{
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-s, -s/2, s);

    glTexCoord2f(0.0,1.0);
    glVertex3f(s, -s/2, s);

    glTexCoord2f(1.0,1.0);
    glVertex3f(s, s, s);

    glTexCoord2f(1.0,0.0);
    glVertex3f(-s, s, s);
}

void cubeSideFour()
{
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-s, -s, -s);

    glTexCoord2f(0.0,1.0);
    glVertex3f(s, -s, -s);

    glTexCoord2f(1.0,1.0);
    glVertex3f(s, s, -s);

    glTexCoord2f(1.0,0.0);
    glVertex3f(-s, s, -s);
}

void cubeSideFive()
{
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(s, s, s);

    glTexCoord2f(0.0,1.0);
    glVertex3f(s, -s, s);

    glTexCoord2f(0.0,1.0);
    glVertex3f(s, -s, -s);

    glTexCoord2f(1.0,0.0);
    glVertex3f(s, s, -s);
}

void cubeSideSix()
{
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-s, s, s);

    glTexCoord2f(0.0,1.0);
    glVertex3f(-s, -s, s);

    glTexCoord2f(1.0,1.0);
    glVertex3f(-s, -s, -s);

    glTexCoord2f(1.0,0.0);
    glVertex3f(-s, s, -s);
}

void makeCube()
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    cubeSideOne();

    glPushMatrix();
    cubeSideTwo();

    glPushMatrix();
    cubeSideThree();

    glPopMatrix();
    cubeSideFour();

    glPushMatrix();
    cubeSideFive();

    glPopMatrix();
    cubeSideSix();

    glEnd();


    glPopMatrix();

    glFlush();
}
