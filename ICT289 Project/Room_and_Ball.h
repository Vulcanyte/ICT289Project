
/** @Overview: Creation of the enviroment, using the OpenGL graphics API.

    @Author: Matthew MacLennan
    @StudenNumber: 32225946
    @Date: 18th May 2016

    @Version: 1.0
**/


#ifndef Room_and_Ball_h
#define Room_and_Ball_h

#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// --------------------   Draw Room   --------------------
void drawRoom(GLfloat s);

/** @brief: Create the room objects, using glVertex3f() functions.

    @param: GLfloat (s) - The scale value for the room itself.

    @return: NONE.
**/

// --------------------   Draw Ball   --------------------
void drawBall(GLfloat s);

/** @brief: Create the ball object, using glutWireSphere().

    @param: GLfloat (s) - The scale value for the ball.

    @return: NONE.
**/


#endif /* Room_and_Ball_h */
