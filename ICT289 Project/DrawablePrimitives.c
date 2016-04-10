
#include "DrawablePrimitives.h"
#include "CustomDataTypes.h"
#include <gl/freeglut.h>

void DrawHouse(int DrawType)
{
    /* define coordinates for a rectangle - the main "building block"*/
    point3 vertices[8]= {{000.0, 000.0, 0.0},{000.0, 200.0, 0.0},
                        {300.0, 200.0, 0.0},{300.0, 000.0, 0.0},
                        {000.0, 000.0, -300.0},{000.0, 200.0, -300.0},
                        {300.0, 200.0, -300.0},{300.0, 000.0, -300.0}};

    /* plot primitives to draw the house*/
    glBegin(DrawType);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(vertices[0]);
        glVertex3fv(vertices[1]);
        glVertex3fv(vertices[2]);
        glVertex3fv(vertices[3]);
    glEnd();

    glBegin(DrawType);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(vertices[3]);
        glVertex3fv(vertices[7]);
        glVertex3fv(vertices[6]);
        glVertex3fv(vertices[2]);
    glEnd();

    glBegin(DrawType);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(vertices[0]);
        glVertex3fv(vertices[4]);
        glVertex3fv(vertices[5]);
        glVertex3fv(vertices[1]);
    glEnd();

    glBegin(DrawType);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(vertices[4]);
        glVertex3fv(vertices[5]);
        glVertex3fv(vertices[6]);
        glVertex3fv(vertices[7]);
    glEnd();

    /*glBegin(DrawType);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(vertices[1]);
        glVertex3fv(vertices[2]);
        glVertex3fv(vertices[6]);
        glVertex3fv(vertices[5]);
    glEnd();*/

    glBegin(DrawType);
    glColor3f(1.0f, 0.5f, 0.5f);
        glVertex3fv(vertices[4]);
        glVertex3fv(vertices[0]);
        glVertex3fv(vertices[3]);
        glVertex3fv(vertices[7]);
    glEnd();

    glBegin(DrawType);
    glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3fv(vertices[1]);
        glVertex3f(150.0,350.0, 0.0);
        glVertex3fv(vertices[2]);
    glEnd();

    glBegin(DrawType);
    glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3fv(vertices[5]);
        glVertex3fv(vertices[6]);
        glVertex3f(150.0,350.0, -300.0);

    glEnd();

    glBegin(DrawType);
    glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3fv(vertices[5]);
        glVertex3fv(vertices[1]);
        glVertex3f(150.0,350.0, 0.0);
        glVertex3f(150.0,350.0, -300.0);
    glEnd();

    glBegin(DrawType);
    glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3fv(vertices[6]);
        glVertex3fv(vertices[2]);
        glVertex3f(150.0,350.0, 0.0);
        glVertex3f(150.0,350.0, -300.0);
    glEnd();

    glBegin(DrawType);
    glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(120.0,00.0, 0.5f);
        glVertex3f(120.0,120.0, 0.5f);
        glVertex3f(180.0,120.0, 0.5f);
        glVertex3f(180.0,00.0, 0.5f);
    glEnd();
}
