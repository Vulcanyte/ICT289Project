
#include "GLWindow.h"
#include <GL/freeglut.h>

void GLWindowCreate(GL_Window* newWindow, char* name, int posX, int posY, int sizeX, int sizeY)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Set window creation to size (sizeX, sizeY).
    glutInitWindowSize(sizeX,sizeY);
    newWindow->dimensions[0] = sizeX;
    newWindow->dimensions[1] = sizeY;

    // Move window to screen point (posX, posY).
    glutInitWindowPosition(posX,posY);
    newWindow->pos[0] = posX;
    newWindow->pos[1] = posY;

    // Create a new window titled 'name'
    glutCreateWindow(name);
    newWindow->windowName = name;
}
