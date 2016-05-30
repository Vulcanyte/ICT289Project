
// External headers.
#include <gl/freeglut.h>

// Local headers.
#include "DrawablePrimitives.h"
#include "Camera.h"
#include "CameraController.h"
#include "PopupMenu.h"
#include "CustomGUI.h"
#include "GLWindow.h"
#include "CollisionDetection.h"
#include "FileIO.h"
#include "GameObject.h"
#include "Room_and_Ball.h"
#include "RigidBody.h"

// Core Program Parameters.
GL_Window programWindow;
const float FRAMERATE = 1/60.0f;                     // ~60 FPS.
const float FRAMERATE_MILLIS = 1/60.0f * 1000;       // Millisecond version of framerate.
const float PHYSICS_MILLIS = 200;                 // Millisecond version of physics update rate.

// Camera-related Parameters.
Camera cam;
CameraControlKeys controlKeys;
CameraController controller;

// Pop-up Menu-related Parameters.
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

GUItext controlDisplayPrompt;
GUItext controlDisplay_forward;
GUItext controlDisplay_backward;
GUItext controlDisplay_upward;
GUItext controlDisplay_downward;
GUItext controlDisplay_left;
GUItext controlDisplay_right;
GUItext controlDisplay_mouseLock;

GUIframe dataFrame;
GUIframeEntry dataFrameOptions[] = {{&mouseLockText, GUI_TEXT}, {&posText, GUI_TEXT}, {&lookText, GUI_TEXT}, {&debugText, GUI_TEXT}, {&controlDisplayPrompt, GUI_TEXT}};

GUIframe borderFrame;
GUIframeEntry borderFrameOptions[] = {{&HUDbottom, GUI_LINE}, {&HUDtop, GUI_LINE}, {&HUDside, GUI_LINE}};

GUIframe controlDisplayFrame;
GUIframeEntry controlDisplayFrameOptions[] = {  {&controlDisplay_forward, GUI_TEXT},
                                                {&controlDisplay_backward, GUI_TEXT},
                                                {&controlDisplay_upward, GUI_TEXT},
                                                {&controlDisplay_downward, GUI_TEXT},
                                                {&controlDisplay_left, GUI_TEXT},
                                                {&controlDisplay_right, GUI_TEXT},
                                                {&controlDisplay_mouseLock, GUI_TEXT}};

// Ball GameObject params.
collider_Sphere ballBounds;
RigidBody ballPhysics;
GameObject ball;
GameObjectComponent ballComponents[] = {{&ballBounds, COLL_SPHERE}, {&ballPhysics, RIGIDBODY}};

// Room GameObject params.
collider_AABB roomFloor;
collider_AABB roomWall_N;
collider_AABB roomWall_S;
collider_AABB roomWall_E;
collider_AABB roomWall_W;
collider_AABB roomRoof;
GameObject room;
GameObjectComponent roomComponents[] = {{&roomFloor, COLL_BOX}, {&roomWall_N, COLL_BOX}, {&roomWall_S, COLL_BOX}, {&roomWall_E, COLL_BOX}, {&roomWall_W, COLL_BOX}, {&roomRoof, COLL_BOX}};

collider_AABB* roomSurfaces[] = {&roomFloor, &roomWall_N, &roomWall_S, &roomWall_E, &roomWall_W, &roomRoof};

// Player GameObject params.
collider_Sphere playerRange;
point3 playerRangeNormal;
collider_AABB playerBody;
GameObject player;
GameObjectComponent playerComponents[] = {{&playerRange, COLL_SPHERE}, {&playerBody, COLL_BOX}};

void printPoint(point3 p)
{
    printf("%1.3f, %1.3f, %1.3f\n", p[0], p[1], p[2]);
    return;
}

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
            controllerEditBasicKeyControls(&controller, 'w', 's', 'q', 'e', 'a', 'd', 'c', 400.0f);
            controllerEditMouseControls(&controller, 0.005f, 0.005f);

            // Enable depth testing.
            glEnable(GL_DEPTH_TEST);

    // --------------------   Set up the popup menus.   --------------------
            GLPopupMenuCreate(&mainMenu, "Main Menu", testMenuFunct, GLUT_MIDDLE_BUTTON, testOptions, 4);
            GLPopupMenuCreate(&subMenuTest, "SubMenu", testSubMenuFunc, -1, subTestOptions, 4);

            GLPopupMenuCreateSub(&mainMenu, &subMenuTest);

    // --------------------   Set up the GameObjects.   --------------------

            // Set up the player.
            gameObjectInit(&player, cam.position[0], cam.position[1], cam.position[2], playerComponents, 2);
            gameObjectUpdate(&player);

            // Set up the ball.
            gameObjectInit(&ball, 0,200,0, ballComponents, 2);

    // --------------------   Set up the collision colliders.   --------------------

            // Initialise the player colliders.
            collisionInit_S(&playerRange, 0,0,0, 10);
            collisionInit_B(&playerBody, 0, 0, 0, 20, 20, 20);

            // Initialise the ball collider.
            collisionInit_S(&ballBounds, 0, 0, 0, 30);

            // Initialise the room colliders.
            collisionInit_B(&roomFloor, 0, 0, 0, 1000, 100, 1000);
            collisionInit_B(&roomWall_N, 0, 250, 500, 1000, 500, 100);
            collisionInit_B(&roomWall_S, 0, 250, -500, 1000, 500, 100);
            collisionInit_B(&roomWall_E, 500, 250, 0, 100, 500, 1000);
            collisionInit_B(&roomWall_W, -500, 250, 0, 100, 500, 1000);
            collisionInit_B(&roomRoof, 0, 500, 0, 1000, 100, 1000);

            collisionDebug_Toggle(1);

    // --------------------   Set up the RigidBodies.   --------------------

            physicsInit(&ballPhysics, 1, 1.0f, 1, 1, 0);
            physicsSetPosition(&ballPhysics, ball.position[0], ball.position[1], ball.position[2]);

    // --------------------   Set up the GUI.   --------------------
            // Initialise individual elements.

            // Set the default GUI text color to BLACK.
            GUIsetTextColor(0.0f, 0.0f, 0.0f);

            GUInewLine(&HUDtop, 0, 20, 302, 20, 10.0f, 1.0, 1.0, 0.0);
            GUInewLine(&HUDside, 300, 15, 300, 203, 5.0f, 1.0, 0.5, 0.0);
            GUInewLine(&HUDbottom, 0, 200, 300, 200, 5.0f, 1.0, 0.5, 0.0);
            GUInewText(&mouseLockText, "Mouse Lock: ", 0, 50, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&posText, "Pos: ", 0, 80, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&lookText, "Dir: ", 0, 110, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&debugText, "Check: ", 0, 140, (void*)GLUT_BITMAP_HELVETICA_18);

            // Initialise Control frame elements.
            GUInewText(&controlDisplayPrompt, "Show/Hide controls: ", 0, programWindow.dimensions[1], (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_forward, "Forward: ", 0, 50, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_backward, "Backward: ", 0, 80, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_upward, "Upward: ", 0, 110, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_downward, "Downward: ", 0, 140, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_left, "Left: ", 0, 170, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_right, "Right: ", 0, 200, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_mouseLock, "Mouse Control Toggle: ", 0, 230, (void*)GLUT_BITMAP_HELVETICA_18);

            // Initialise entire frames.
            GUInewFrame(&dataFrame, 1, dataFrameOptions, 5);
            GUInewFrame(&borderFrame, 2, borderFrameOptions, 3);
            GUInewFrame(&controlDisplayFrame, 3, controlDisplayFrameOptions, 7);

            GUIpositionFrame(&controlDisplayFrame, 0, 250);
            GUIdisableFrame(&controlDisplayFrame);  // HIDE the default control display by default.

            // Link elements to other parameters for display / etc.
            GUIlinkTextToParam(&mouseLockText, &controller.mouseLock, INT_param);
            GUIlinkTextToParam(&posText, cam.position, POINT3_param);
            GUIlinkTextToParam(&lookText, cam.lookAt, POINT3_param);
            GUIlinkTextToParam(&debugText, cam.rotation, POINT3_param);

            GUIlinkTextToParam(&controlDisplayPrompt, "X", CHAR_param);

            GUIlinkTextToParam(&controlDisplay_forward, &controller.camControls->forwardKey, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_backward, &controller.camControls->backwardKey, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_upward, &controller.camControls->upKey, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_downward, &controller.camControls->downKey, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_left, &controller.camControls->strafe_L, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_right, &controller.camControls->strafe_R, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_mouseLock, &controller.camControls->mouseLock, CHAR_param);
}

void keyboard( unsigned char ch, int num1, int num2 )
{
    controllerCheckKeys(&controller, ch);

    if(ch == 'x' || ch == 'X')
    {
        if(controlDisplayFrame.renderON == 1)
            GUIdisableFrame(&controlDisplayFrame);
        else
            GUIenableFrame(&controlDisplayFrame);
    }
}

void keyboardUp( unsigned char ch, int num1, int num2 )
{
    if(ch != controlKeys.mouseLock.key)
        controllerCheckKeys(&controller, ch);
}

void mouseMove( int x, int y )
{
    controllerCheckMouse(&controller, x, y );
}

void mouseButton( int button, int state, int x, int y )
{
    controllerCheckButtons(&controller, button, state, x, y);
}

void FrameUpdate(int value)
{
    glutTimerFunc(FRAMERATE_MILLIS, FrameUpdate, 0);

    controllerKeyUpdate(&controller, FRAMERATE);

    gameObjectSetPos(&player, cam.position[0], cam.position[1], cam.position[2]);
    collisionOffset_S(&playerRange, cam.lookAt[0] * 100, cam.lookAt[1] * 100, cam.lookAt[2] * 100);
    gameObjectUpdate(&player);

    // Keep the player within the room using the below code.
    int i = 0;
    for(i = 0; i < 6; i++)
        if(collisionCollideBB(&playerBody, roomSurfaces[i]))
        {

            point3 normal1 = {0,0,0};
            point3 normal2 = {0,0,0};

            float penetration = collisionFindNormalBB(&playerBody, roomSurfaces[i], &normal1[0], &normal1[1], &normal1[2], &normal2[0], &normal2[1], &normal2[2]);

            playerBody.position[0] -= -normal1[0] * penetration + normal1[0];
            playerBody.position[1] -= -normal1[1] * penetration + normal1[1];
            playerBody.position[2] -= -normal1[2] * penetration + normal1[2];
        }

    // Update the camera's position.
    cam.position[0] = playerBody.position[0];
    cam.position[1] = playerBody.position[1];
    cam.position[2] = playerBody.position[2];

    // Update the camera.
    cameraUpdate(&cam);

    if(collisionCollideSB(&ballBounds, &roomFloor))
    {
        point3 normal1 = {0,0,0};
        point3 normal2 = {0,0,0};

        float penetration = collisionFindNormalSB(&ballBounds, &roomFloor, &normal1[0], &normal1[1], &normal1[2], &normal2[0], &normal2[1], &normal2[2]);

        ballPhysics.position[0] -= -normal1[0] * penetration;
        ballPhysics.position[1] -= -normal1[1] * penetration;
        ballPhysics.position[2] -= -normal1[2] * penetration;

        ballPhysics.velocity[0] *= abs(normal1[0]) * (ballPhysics.velocity[0] * -1 * ballPhysics.bounceDecay);
        ballPhysics.velocity[1] *= abs(normal1[1]) * (ballPhysics.velocity[1] * -1 * ballPhysics.bounceDecay);
        ballPhysics.velocity[2] *= abs(normal1[2]) * (ballPhysics.velocity[2] * -1 * ballPhysics.bounceDecay);
    }

    gameObjectUpdate(&ball);

    // Update the screen.
    glutPostRedisplay();
}

void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --------------------   START Drawing the GUI.   --------------------
    GUIenable2DRendering(&programWindow);

    GUIrenderFrame(&dataFrame);             // Render data.
    GUIrenderFrame(&borderFrame);           // Render borders.
    GUIrenderFrame(&controlDisplayFrame);   // Render controls.

    GUIdisable2DRendering(&programWindow);
    // --------------------   STOP Drawing the GUI.   --------------------

    // --------------------   START drawing the environment.   --------------------

    collisionDebug_DrawB(&roomFloor);
    collisionDebug_DrawB(&roomWall_N);
    collisionDebug_DrawB(&roomWall_S);
    collisionDebug_DrawB(&roomWall_E);
    collisionDebug_DrawB(&roomWall_W);
    collisionDebug_DrawB(&roomRoof);

    collisionDebug_DrawS(&ballBounds);

    //drawRoom(100.0f);

    //gameObjectRender(&player);

    // --------------------   STOP drawing the environment.   --------------------

    //DrawHouse(GL_LINE_LOOP);

    /*glPushMatrix();
    glLoadIdentity();
        glTranslatef(350, 0, 50);
        glRotatef(-90, 0, 1, 0);
        DrawHouse(GL_POLYGON);

    glPopMatrix();*/

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
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboard);

    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMove);

    // Timer functions.
    glutTimerFunc(FRAMERATE_MILLIS, FrameUpdate, 0);

    // OpenGL main loop.
    glutMainLoop();
    return 0;
}
