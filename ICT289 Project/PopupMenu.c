
#include "PopupMenu.h"
#include <GL/freeglut.h>

void GLPopupMenuCreate(GL_PopupMenu* newMenu, char* menuName, PopupMenuOptionFunc menuFunc, int button, GL_PopupMenuEntry options[], int arraySize)
{
    newMenu->menuName = menuName;
    newMenu->menuID = glutCreateMenu(menuFunc);
    newMenu->accessButton = button;
    newMenu->options = options;

    int i;

    for(i = 0; i < arraySize; i++)
    {
        printf("Added entry: %s %d\n", options[i].label, options[i].value);
        glutAddMenuEntry(options[i].label, options[i].value);
    }

    if(button >= 0)
        glutAttachMenu(newMenu->accessButton);
}

void GLPopupMenuCreateSub(GL_PopupMenu* parent, GL_PopupMenu* child)
{
    GLPopupMenuFocus(parent);

    glutAddSubMenu(child->menuName, child->menuID);
}

void GLPopupMenuFocus(GL_PopupMenu* menu)
{
    glutSetMenu(menu->menuID);
}

void GLPopupMenuDetach(GL_PopupMenu* menu)
{
    glutDetachMenu(menu->accessButton);
}
