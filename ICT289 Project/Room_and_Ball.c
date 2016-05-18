
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Room_and_Ball.h"

/**************** Create Enviroment ***************/

// note using temp colours to be able to identify different sections of the room and ball until textures are added

void drawRoom(GLfloat s)
{
    /**************** Main Room ****************/
    
    glBegin(GL_QUADS);
    
    // floor of main room
    glColor3f(0.0f, 0.0f, 0.0f); // black

    glVertex3f(-s, -s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, -s, s);
    glVertex3f(-s, -s, s);
    
    // roof of main room
    glColor3f(1.0f, 0.5f, 0.5f); // orange
    
    glVertex3f(-s, s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, s, s);
    glVertex3f(-s, s, s);
    
    // wall of room
    glColor3f(1.0f, 0.0f, 0.0f); // red
    
    glVertex3f(-s, -s/2, s);
    glVertex3f(s, -s/2, s);
    glVertex3f(s, s, s);
    glVertex3f(-s, s, s);
    
    
    
    // wall of room
    glColor3f(0.0f, 1.0f, 0.0f); // green
    
    glVertex3f(-s, -s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(-s, s, -s);
    
    // wall of room
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    
    glVertex3f(s, s, s);
    glVertex3f(s, -s, s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, s, -s);
    
    // wall of room
    glColor3f(1.0f, 1.0f, 1.0f); // white
    
    glVertex3f(-s, s, s);
    glVertex3f(-s, -s, s);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, s, -s);
    
    
    
    /**************** Goal Cube ****************/
    
    glColor3f(0.5f, 0.0f, 0.5f); // purple
    
    // back face
    glVertex3f(s/2, -s, s * 1.5); // bottom left vertex
    glVertex3f(-s/2, -s, s * 1.5); // bottom right vertex
    glVertex3f(-s/2, s/4, s * 1.5); // top  right vertex
    glVertex3f(s/2, s/4, s * 1.5); // top left vertex
    
    // bottom face
    glVertex3f(s/2, -s, s * 1.5); // far left
    glVertex3f(-s/2, -s, s * 1.5); // far right
    glVertex3f(s/2, -s, s); // left big cube
    glVertex3f(-s/2, -s, s); // right big cube
    
    // left face (looking outside in)
    glVertex3f(-s/2, -s, s * 1.5);
    glVertex3f(-s/2, 2/4, s * 1.5);
    glVertex3f(-s/2, -s, s);
    glVertex3f(-s/2, 2/4, s);
    
    // right face (looking outside in)
    glVertex3f(s/2, -s, s * 1.5);
    glVertex3f(s/2, s/4, s * 1.5);
    glVertex3f(s/2, -s, s);
    glVertex3f(s/2, s/4, s);
    
    glEnd();
}

void drawBall(GLfloat s)
{
    /**************** Create Ball ****************/
    
    glutWireSphere(s/6,100,100);
}
