/** @Overview: Creating a cube (room) that can be textured using the OpenGl graphics API.
 
 @Author: Matthew MacLennan
 @StudentNumber: 32225946
 @Date: 31st May 2016
 
 @Version: 1.0
 **/

#ifndef MakeRoom_h
#define MakeRoom_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/** @brief: To check that the scale of the room is above 0.0.
 
 @param: scale (GLfloat) - The read in scale.
 @param: s (GLfloat) - The variable used to create the room in future methods.
 
 @return: NONE.
**/
void getCubeScale(GLfloat scale);

/** @brief: A side of the cube.
 
 @param: s (GLfloat) - The variable used to create the room in scale.
 
 @return: NONE.
**/
void cubeSideOne();

/** @brief: A side of the cube.
 
 @param: s (GLfloat) - The variable used to create the room in scale.
 
 @return: NONE.
**/
void cubeSideTwo();

/** @brief: A side of the cube.
 
 @param: s (GLfloat) - The variable used to create the room in scale.
 
 @return: NONE.
**/
void cubeSideThree();

/** @brief: A side of the cube.
 
 @param: s (GLfloat) - The variable used to create the room in scale.
 
 @return: NONE.
**/
void cubeSideFour();

/** @brief: A side of the cube.
 
 @param: s (GLfloat) - The variable used to create the room in scale.
 
 @return: NONE.
**/
void cubeSideFive();

/** @brief: A side of the cube.
 
 @param: s (GLfloat) - The variable used to create the room in scale.
 
 @return: NONE.
**/
void cubeSideSix();

/** @brief: Using the 6 makeSide methods to create the cube (room).
 
 @return: NONE.
**/
void makeCube();

#endif /* MakeRoom_h */
