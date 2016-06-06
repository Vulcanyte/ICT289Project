
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

<<<<<<< HEAD
/** @brief: Reads the image file and takes away the important variables from it.

 @param: w (int) - Temp int for width.
 @param: h (int) - Temp int for height.
 @param: max (int) - Max intensity.
 @param: i (int) - Int for looping.
 @param: j (int) - Int for looping.
 @param: r (unsigned int) - Red.
 @param: g (unsigned int) - Green.
 @param: b (unsigned int) - Blue.
 @param: k (int) - A temp variable used to gather the information needed for r, g and b.
 @param: ch (char) - The variable used to take the information from the file and transfer it to the program.
 @param: fp (FILE *) - A pointer to the image file being opened.

=======
/* @brief: Sets up buffers for texturing.
 
>>>>>>> origin/master
 @return: NONE.
//
void display();

<<<<<<< HEAD
/** @brief: Textures the model.

 @param: level (GLint) - The level of detail.
 @param: components (GLint) - The number of colours being used (RGB).
 @param: border (GLint) - No border = 0.

 @return: NONE.
**/
void initTextures();

/** @brief: Applies texture to the model.

 @return: NONE.
**/
void initialise();
=======
/** @brief: Gets the image for texturing and returns the useable data.
 
 @param: name (char*) - Name of texture file.
 @param: tmpTex (GLuint) - The data for the texure being gathered.
 
 @return: tmpTex.
//
GLuint GetTexImage(char* name);
>>>>>>> origin/master

#endif /* Texturing_h */
