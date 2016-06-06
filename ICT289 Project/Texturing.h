
/** @Overview: Adding textures to the graphics, using the OpenGL graphics API.
 
 @Author: Matthew MacLennan
 @StudentNumber: 32225946
 @Date: 30th May 2016
 
 @Version: 1.0
**/
/*
#ifndef Texturing_h
#define Texturing_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* @brief: Sets up buffers for texturing.
 
 @return: NONE.
//
void display();

/** @brief: Gets the image for texturing and returns the useable data.
 
 @param: name (char*) - Name of texture file.
 @param: tmpTex (GLuint) - The data for the texure being gathered.
 
 @return: tmpTex.
//
GLuint GetTexImage(char* name);

#endif /* Texturing_h */
