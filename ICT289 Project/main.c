
// External headers.
#include <gl/freeglut.h>

// Local headers.
#include "DrawablePrimitives.h"
#include "Camera.h"
#include "CameraController.h"
#include "PopupMenu.h"
#include "CustomGUI.h"
#include "GLWindow.h"

// Camera-related Parameters.
Camera cam;
CameraControlKeys controlKeys;
CameraController controller;

// Menu-related Parameters.
GL_PopupMenu mainMenu;
GL_PopupMenu subMenuTest;
GL_PopupMenuEntry testOptions[] = {{"Red", 1}, {"Blue", 2}, {"GREEN", 3}, {"ORANGE", 4}};
GL_PopupMenuEntry subTestOptions[] = {{"SUB Red", 1}, {"SUB Blue", 2}, {"SUB Green", 3}, {"SUB Orange", 4}};

// GUI-related Parameters.
GUItext mouseLockText;
GUItext posText;
GUItext lookText;
GUItext debugText;
GUIline HUDtop;
GUIline HUDside;
GUIline HUDbottom;

GUIframe dataFrame;
GUIframeEntry dataFrameOptions[] = {{&mouseLockText, GUI_TEXT}, {&posText, GUI_TEXT}, {&lookText, GUI_TEXT}, {&debugText, GUI_TEXT}};

GUIframe borderFrame;
GUIframeEntry borderFrameOptions[] = {{&HUDbottom, GUI_LINE}, {&HUDtop, GUI_LINE}, {&HUDside, GUI_LINE}};

// Other Program Parameters.
GL_Window programWindow;

void myinit( void )
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(5.0);

    // --------------------   Set up the camera.   --------------------
            cameraInit(&cam, -500, 500, -500, 500, 0.01f, 10000.0f, 45, 1, PERSPECTIVE);
            cameraOrientate_f(&cam, -100, 180, 200, 150, 100, 0);

            // Activate the camera.
            cameraProject(&cam);
            cameraUpdate(&cam);

            // Bind the camera to some controls.
            controllerBindCameraToKeys(&controller, &cam, &controlKeys, FIRST_PERSON);
            controllerEditBasicKeyControls(&controller, 'w', 's', 'q', 'e', 'a', 'd', 'c', 8.0f);
            controllerEditMouseControls(&controller, 0.005f, 0.005f);

            // Enable depth testing.
            glEnable(GL_DEPTH_TEST);

    // --------------------   Set up the menus.   --------------------
            GLPopupMenuCreate(&mainMenu, "Main Menu", testMenuFunct, GLUT_MIDDLE_BUTTON, testOptions, 4);
            GLPopupMenuCreate(&subMenuTest, "SubMenu", testSubMenuFunc, -1, subTestOptions, 4);

            GLPopupMenuCreateSub(&mainMenu, &subMenuTest);

    // --------------------   Set up the GUI.   --------------------
            // Initialise individual elements.
            GUInewLine(&HUDtop, 0, 20, 302, 20, 10.0f, 1.0, 1.0, 0.0);
            GUInewLine(&HUDside, 300, 15, 300, 203, 5.0f, 1.0, 0.5, 0.0);
            GUInewLine(&HUDbottom, 0, 200, 300, 200, 5.0f, 1.0, 0.5, 0.0);
            GUInewText(&mouseLockText, "Mouse Lock: ", 0, 50, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&posText, "Pos: ", 0, 80, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&lookText, "Dir: ", 0, 110, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&debugText, "Check: ", 0, 140, (void*)GLUT_BITMAP_HELVETICA_18);

            // Initialise entire frames.
            GUInewFrame(&dataFrame, 2, dataFrameOptions, 4);
            GUInewFrame(&borderFrame, 1, borderFrameOptions, 3);

            // Link elements to other parameters for display / etc.
            GUIlinkTextToParam(&mouseLockText, &controller.mouseLock, INT_param);
            GUIlinkTextToParam(&posText, cam.position, POINT3_param);
            GUIlinkTextToParam(&lookText, cam.lookAt, POINT3_param);
            GUIlinkTextToParam(&debugText, cam.rotation, POINT3_param);
}

void keyboard( unsigned char ch, int num1, int num2 )
{
    controllerCheckKeys(&controller, ch);

    glutPostRedisplay();
}

void mouseMove( int x, int y )
{
    controllerCheckMouse(&controller, x, y );

    glutPostRedisplay();
}

void mouseButton( int button, int state, int x, int y )
{
    controllerCheckButtons(&controller, button, state, x, y);

    glutPostRedisplay();
}

void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update the camera.
    cameraUpdate(&cam);

    // --------------------   START Drawing the GUI.   --------------------
    GUIenable2DRendering(&programWindow);

    GUIrenderFrame(&dataFrame);    // Render data;
    GUIrenderFrame(&borderFrame);  // Render borders;

    GUIdisable2DRendering(&programWindow);
    // --------------------   STOP Drawing the GUI.   --------------------

    DrawHouse(GL_LINE_LOOP);

    glPushMatrix();
        glTranslatef(350, 0, 50);
        glRotatef(-90, 0, 1, 0);
        DrawHouse(GL_POLYGON);
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}


int main( int argc, char** argv )
{
    // Initialisation.
    glutInit(&argc,argv);
    GLWindowCreate(&programWindow, "Draw House", 0, 0, 1000, 1000);
    myinit();

    // Function callbacks.
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    //glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMove);

    // OpenGL main loop.
    glutMainLoop();
    return 0;
}
