/*
#include "Texturing.h"
#include "CustomDataTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define MAXROW 200
#define MAXCOL 320  // 320x200 pixel images

typedef GLubyte pixelSingle;
typedef char name[15];

name image_file_name;

pixelSingle image[MAXROW][MAXCOL][3]; // image arrays
pixelSingle p;

name inf_name, outf_name; // strings to store file names
FILE *inf_handle, *outf_handle; // file handles created at file open

GLuint myTex[4]; // to hold he texture names returned by glGenTextures

int charin;
int r, c;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glutSwapBuffers();
}

GLuint GetTexImage(char* name)
{
    GLuint tmpTex;
    
    if((inf_handle = fopen(name, "rb")) == NULL) // open failed
    {
        puts("*** Can't open input file - please check file name typed!\n ");
        fprintf(stderr,"filename %s not found\n",name);
        charin = getchar();
        exit(1); // terminate execution
    }
    
    for ( r = 0;  r < MAXROW; r++ )
        for ( c = 0;  c < MAXCOL; c++)  {
            if((charin=fgetc(inf_handle))==EOF)   // read failed
            {
                printf("***File reading failed! \n");
                charin = getchar();
                exit(1);    // terminate execution
            }
            image[r][c][0] = image[r][c][1] = image[r][c][2]= charin;
        }
    
    printf("\nImage input completed!\n");
    fclose(inf_handle);    // close input file
    
    glGenTextures(1, &tmpTex);    // generate one texture name and return in tmpTex
    glBindTexture(GL_TEXTURE_2D, tmpTex); // bind tmpTex to 2D texture
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, MAXCOL,MAXROW, GL_RGB, GL_UNSIGNED_BYTE,image);
    
    return tmpTex;
}
*/