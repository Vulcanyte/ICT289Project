
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

int width, height; // of image

pixel *image; // array of pixels

char *fileName = "FILE NAME HERE";

void readImage() // reads image as ppm file
{
    int w, h, max;
    int i, j;
    unsigned int r, g, b;
    int k;
    char ch;
    FILE *fp;

    fp = fopen(fileName, "r");

    // read the header
    fscanf(fp, "P%c\n", &ch);
    if(ch != '3')
    {
        fprintf(stderr, "Only ascii mode 3 channel PPM files");
        exit(-1);
    }

    // read the width
    fscanf(fp, "%d", &w);

    // read the height
    fscanf(fp, "%d", &h);

    // max intensity
    fscanf(fp, "%d", &max);

    // no error checking yet
    width = w;
    height = h;

    // printf("width = %d, height = %d\n", width, height);

    image = (pixel *)malloc(width * height * sizeof(pixel));

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            fscanf(fp, "%d %d %d", &r, &g, &b);
            k = i * width + j;
            (*(image + k)) [0] = (GLubyte)r;
            (*(image + k)) [1] = (GLubyte)g;
            (*(image + k)) [2] = (GLubyte)b;
        }
    }

    fclose(fp);
}

void initTextures()
{
    GLint level = 0; // only 1 level
    GLint components = 3; // r, g, b
    GLint border = 0; // no border

    readImage();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // each pixelrow on a byte alighment boundary

    glTexImage2D(GL_TEXTURE_2D, level, components, (GLsizei)width, (GLsizei)height, border, GL_RGB, GL_UNSIGNED_BYTE, image); // info about image

    // chooses mapping type from texels to pixels
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // overwrite pixel with texture colour
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // enables texturing
    glEnable(GL_TEXTURE_2D);
}

void initialise()
{
    glEnable(GL_DEPTH_TEST); // enables depth buffer
    
    glClearDepth(1.0); // set the depth buffer for clearing
    
    initTextures(); // start texture mapping
}

