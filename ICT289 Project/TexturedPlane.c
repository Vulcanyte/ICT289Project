
#include <GL/freeglut.h>

#include "TexturedPlane.h"
#include "FileIO.h"

void texPlaneInit(TexturedPlane* plane, float posX, float posY, float posZ, float width, float height, char* texFile)
{
    plane->pos[0] = posX;
    plane->pos[1] = posY;
    plane->pos[2] = posZ;

    plane->rot[0] = 0;
    plane->rot[1] = 0;
    plane->rot[2] = 0;

    plane->bounds[0] = width;
    plane->bounds[1] = height;

    // TODO: Load a texture file and bind the texture ID to the texID variable of this plane.
    plane->textureID = fileGetTexImage(texFile);
}

void texPlaneSetPosition(TexturedPlane* plane, float posX, float posY, float posZ)
{
    plane->pos[0] = posX;
    plane->pos[1] = posY;
    plane->pos[2] = posZ;
}

void texPlaneSetRotation(TexturedPlane* plane, float rotX, float rotY, float rotZ)
{
    plane->rot[0] = rotX;
    plane->rot[1] = rotY;
    plane->rot[2] = rotZ;
}

void texPlaneDraw(TexturedPlane* plane)
{
    glBindTexture(GL_TEXTURE_2D, plane->textureID);

    glPushMatrix();

    glTranslatef(plane->pos[0], plane->pos[1], plane->pos[2]);

    glRotatef(plane->rot[0], 1, 0, 0);
    glRotatef(plane->rot[1], 0, 1, 0);
    glRotatef(plane->rot[2], 0, 0, 1);

    glTranslatef(-plane->pos[0], -plane->pos[1], -plane->pos[2]);

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);

        glVertex3f(plane->pos[0] - plane->bounds[0] * 0.5f, plane->pos[1] - plane->bounds[1] * 0.5f, plane->pos[2]);
        glTexCoord2f(0.0, 0.0);

        glVertex3f(plane->pos[0] - plane->bounds[0] * 0.5f, plane->pos[1] + plane->bounds[1] * 0.5f, plane->pos[2]);
        glTexCoord2f(1.0, 0.0);

        glVertex3f(plane->pos[0] + plane->bounds[0] * 0.5f, plane->pos[1] + plane->bounds[1] * 0.5f, plane->pos[2]);
        glTexCoord2f(1.0, 1.0);

        glVertex3f(plane->pos[0] + plane->bounds[0] * 0.5f, plane->pos[1] - plane->bounds[1] * 0.5f, plane->pos[2]);
        glTexCoord2f(0.0, 1.0);

    glEnd();

    glPopMatrix();
}
