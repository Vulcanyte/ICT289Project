
// External headers.
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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
#include "RigidBody.h"
#include "Texturing.h"
#include "Interaction.h"

#include "TexturedPlane.h"

// Core Program Parameters.
GL_Window programWindow;
const float FRAMERATE = 1/60.0f;                     // ~60 FPS.
const float FRAMERATE_MILLIS = 1/60.0f * 1000;       // Millisecond version of framerate.
const float PHYSICS_MILLIS = 200;                 // Millisecond version of physics update rate.

ControlKey physicsControl_AirDecel;
float phys_AirDecel = 0.0f;
ControlKey physicsControl_Gravity;
float phys_Grav = 0.0f;
ControlKey physicsControl_SimSpeed;
float phys_Spd = 0.0f;

// Camera-related Parameters.
Camera cam;
CameraControlKeys controlKeys;
CameraController controller;

// Pop-up Menu-related Parameters.
GL_PopupMenu cameraMenu;
GL_PopupMenuEntry camOptions[] = {{"First-Person Camera", 1}, {"Third-Person Camera", 2}};

// GUI-related Parameters.
GUItext mouseLockText;
GUItext posText;
GUItext ballText;
GUItext ballText2;
GUItext debugTxt;

GUItext simParam1;
GUItext simParam2;
GUItext simParam3;

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
GUIframeEntry dataFrameOptions[] = {{&mouseLockText, GUI_TEXT}, {&posText, GUI_TEXT}, {&ballText, GUI_TEXT}, {&ballText2, GUI_TEXT}, {&controlDisplayPrompt, GUI_TEXT}};

GUIframe simulationFrame;
GUIframeEntry simFrameOptions[] = {{&simParam1, GUI_TEXT}, {&simParam2, GUI_TEXT}, {&simParam3, GUI_TEXT}};

GUIframe debugFrame;
GUIframeEntry debugFrameOptions[] = {{&debugTxt, GUI_TEXT}};

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

<<<<<<< HEAD
// Set up interaction control structs.
interactionController interController;
interactionControlKeys interControls;

// 2D Texture planes.
TexturedPlane testPlane;
TexturedPlane testPlane2;
TexturedPlane testPlane3;
TexturedPlane testPlane4;
TexturedPlane testPlane5;
=======
// Texture params.
GLuint myTex[4];

float penetration = 0;
>>>>>>> origin/master

void printPoint(point3 p)
{
    printf("X: %1.3f, Y: %1.3f, Z: %1.3f\n", p[0], p[1], p[2]);
    return;
}

void camMenuFunc(int option)
{
    switch(option)
    {
        case 1:
            controller.typeOfController = FIRST_PERSON;
            cameraUpdateFPS(&cam);
            break;

        case 2:
            controller.typeOfController = THIRD_PERSON;
            cameraUpdateTPS(&cam);
            break;

        default:
            // Do nothing...
            break;
    }
}

void myinit( void )
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(5.0);
    
    // --------------------   Set up the camera.   --------------------
<<<<<<< HEAD

            cameraInit(&cam, -500, 500, -500, 500, 0.01f, 10000.0f, 45, 1, PERSPECTIVE);
            cameraOrientate_f(&cam, -100, 180, 200, 150, 100, 0);

            // Bind the camera to some controls.
            controllerBindCameraToKeys(&controller, &cam, &controlKeys, FIRST_PERSON);
            controllerEditBasicKeyControls(&controller, 'w', 's', 'q', 'e', 'a', 'd', 'c', 400.0f);
            controllerEditMouseControls(&controller, 0.005f, 0.005f);

            // Activate the camera.
            cameraProject(&cam);

            if(controller.typeOfController == FIRST_PERSON)
                cameraUpdateFPS(&cam);
            else
                cameraUpdateTPS(&cam);

            // Enable depth testing.
            glEnable(GL_DEPTH_TEST);

    // --------------------   Set up the interaction.   --------------------

            // Bind control keys.
            bindKeysToControls(&interController, &playerRange, &interControls);
            changingInteractionKeyControls(&interController, 'f', 't', 'm');

    // --------------------   Set up the popup menus.   --------------------

            GLPopupMenuCreate(&cameraMenu, "Main Menu", camMenuFunc, GLUT_MIDDLE_BUTTON, camOptions, 2);

=======
    
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
    
    // --------------------   Set up the interaction.   --------------------
    
    // Set up interaction control structs.
    interactionController* interController;
    interactionControlKeys* interControls;
    
    // Bind control keys.
    bindKeysToControls(interController, &playerBody, interControls);
    changingInteractionKeyControls(interController, 'f', 't', 'm');
    
    // --------------------   Set up the popup menus.   --------------------
    
    GLPopupMenuCreate(&mainMenu, "Main Menu", testMenuFunct, GLUT_MIDDLE_BUTTON, testOptions, 4);
    GLPopupMenuCreate(&subMenuTest, "SubMenu", testSubMenuFunc, -1, subTestOptions, 4);
    
    GLPopupMenuCreateSub(&mainMenu, &subMenuTest);
    
>>>>>>> origin/master
    // --------------------   Set up the GameObjects.   --------------------
    
    // Set up the player.
    gameObjectInit(&player, cam.position[0], cam.position[1], cam.position[2], playerComponents, 2);
    
    // Set up the ball.
    gameObjectInit(&ball, 0,200,0, ballComponents, 2);
    
    // --------------------   Set up the collision colliders.   --------------------
<<<<<<< HEAD

            // Initialise the player colliders.
            collisionInit_S(&playerRange, 0,0,0, 10);
            collisionInit_B(&playerBody, 0, 0, 0, 20, 20, 20);

            // Initialise the ball collider.
            collisionInit_S(&ballBounds, 0, 0, 0, 30);

            // Initialise the room colliders.
            collisionInit_B(&roomFloor, 0, -100, 0, 1000, 200, 1000);
            collisionInit_B(&roomWall_N, 0, 250, 500, 1000, 500, 100);
            collisionInit_B(&roomWall_S, 0, 250, -500, 1000, 500, 100);
            collisionInit_B(&roomWall_E, 500, 250, 0, 100, 500, 1000);
            collisionInit_B(&roomWall_W, -500, 250, 0, 100, 500, 1000);
            collisionInit_B(&roomRoof, 0, 500, 0, 1000, 100, 1000);

            collisionDebug_Toggle(1);

    // --------------------   Set up the Physics.   --------------------

            physicsSetSimulationSpeed(0.1f);

            physicsInit(&ballPhysics, 1, 0.8f, 1, 1, 0);
            physicsSetPosition(&ballPhysics, ball.position[0], ball.position[1], ball.position[2]);
            physicsAddVelocity(&ballPhysics, -100, 0, 20);
            physicsSetAirDeceleration(2.0f);

            physicsControl_AirDecel.key = '1';
            phys_AirDecel = physicsGetParam(PHYS_AIRDECEL);
            physicsControl_Gravity.key = '2';
            phys_Grav = physicsGetParam(PHYS_GRAVITY);
            physicsControl_SimSpeed.key = '3';
            phys_Spd = physicsGetParam(PHYS_SPEED);

    // --------------------   Set up the GUI.   --------------------

            // Set the default GUI text color to BLACK.
            GUIsetTextColor(0.0f, 0.0f, 0.0f);

            GUInewText(&mouseLockText, "Mouse Lock: ", 0, 50, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&posText, "Pos: ", 0, 80, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&ballText, "Ball Pos: ", 0, 140, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&ballText2, "Ball Vel: ", 0, 170, (void*)GLUT_BITMAP_HELVETICA_18);

            GUIlinkTextToParam(&mouseLockText, &controller.mouseLock, INT_param);
            GUIlinkTextToParam(&posText, cam.position, POINT3_param);
            GUIlinkTextToParam(&ballText, ballPhysics.position, POINT3_param);
            GUIlinkTextToParam(&ballText2, ballPhysics.velocity, POINT3_param);
            GUIlinkTextToParam(&controlDisplayPrompt, "X", CHAR_param);

            GUInewFrame(&dataFrame, 1, dataFrameOptions, 5);

            GUInewText(&simParam1, "Air Decel. (m/s) : ", 0, 30, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&simParam2, "Gravity (m/s) : ", 0, 60, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&simParam3, "Simulation Speed : ", 0, 90, (void*)GLUT_BITMAP_HELVETICA_18);

            GUIlinkTextToParam(&simParam1, &phys_AirDecel, FLOAT_param);
            GUIlinkTextToParam(&simParam2, &phys_Grav, FLOAT_param);
            GUIlinkTextToParam(&simParam3, &phys_Spd, FLOAT_param);

            GUInewFrame(&simulationFrame, 2, simFrameOptions, 3);
            GUIpositionFrame(&simulationFrame, 0, 200);

            // Initialise Control frame elements.
            GUInewText(&controlDisplayPrompt, "Show/Hide controls: ", 0, programWindow.dimensions[1], (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_forward, "Forward: ", 0, 50, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_backward, "Backward: ", 0, 80, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_upward, "Upward: ", 0, 110, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_downward, "Downward: ", 0, 140, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_left, "Left: ", 0, 170, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_right, "Right: ", 0, 200, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplay_mouseLock, "Mouse Control Toggle: ", 0, 230, (void*)GLUT_BITMAP_HELVETICA_18);

            GUIlinkTextToParam(&controlDisplay_forward, &controller.camControls->forwardKey, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_backward, &controller.camControls->backwardKey, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_upward, &controller.camControls->upKey, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_downward, &controller.camControls->downKey, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_left, &controller.camControls->strafe_L, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_right, &controller.camControls->strafe_R, CHAR_param);
            GUIlinkTextToParam(&controlDisplay_mouseLock, &controller.camControls->mouseLock, CHAR_param);

            GUInewFrame(&controlDisplayFrame, 3, controlDisplayFrameOptions, 7);
            GUIpositionFrame(&controlDisplayFrame, 0, 250);
            GUIdisableFrame(&controlDisplayFrame);  // HIDE the default control display by default.

            GUInewLine(&HUDtop, 0, 20, 302, 20, 10.0f, 1.0, 1.0, 0.0);
            GUInewLine(&HUDside, 300, 15, 300, 203, 5.0f, 1.0, 0.5, 0.0);
            GUInewLine(&HUDbottom, 0, 200, 300, 200, 5.0f, 1.0, 0.5, 0.0);

            GUInewFrame(&borderFrame, 4, borderFrameOptions, 3);

            texPlaneInit(&testPlane, 0, 250, 451, 1000, 500, "\\IMG\\bush1.raw");
            texPlaneSetRotation(&testPlane, 0, 180, 0);

            texPlaneInit(&testPlane2, 0, 250, -451, 1000, 500, "\\IMG\\bush1.raw");
            texPlaneSetRotation(&testPlane2, 0, 0, 0);

            texPlaneInit(&testPlane3, -451, 250, 0, 1000, 500, "\\IMG\\link.raw");
            texPlaneSetRotation(&testPlane3, 0, 90, 0);

            texPlaneInit(&testPlane4, 451, 250, 0, 1000, 500, "\\IMG\\link.raw");
            texPlaneSetRotation(&testPlane4, 0, -90, 0);

            texPlaneInit(&testPlane5, 0, 0, 0, 1000, 1000, "\\IMG\\link.raw");
            texPlaneSetRotation(&testPlane5, -90, 0, 0);

            glEnable(GL_TEXTURE_2D);

            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);         // if different change for each tex
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);         // MODULATE IS DEFAULT

            gameObjectUpdate(&player);
            gameObjectUpdate(&ball);
=======
    
    // Initialise the player colliders.
    collisionInit_S(&playerRange, 0,0,0, 10);
    collisionInit_B(&playerBody, 0, 0, 0, 20, 20, 20);
    
    // Initialise the ball collider.
    collisionInit_S(&ballBounds, 0, 0, 0, 30);
    
    // Initialise the room colliders.
    collisionInit_B(&roomFloor, 0, -100, 0, 1000, 200, 1000);
    collisionInit_B(&roomWall_N, 0, 250, 500, 1000, 500, 100);
    collisionInit_B(&roomWall_S, 0, 250, -500, 1000, 500, 100);
    collisionInit_B(&roomWall_E, 500, 250, 0, 100, 500, 1000);
    collisionInit_B(&roomWall_W, -500, 250, 0, 100, 500, 1000);
    collisionInit_B(&roomRoof, 0, 500, 0, 1000, 100, 1000);
    
    collisionDebug_Toggle(1);
    
    // --------------------   Set up the RigidBodies.   --------------------
    
    physicsSetSimulationSpeed(10.0f);
    
    physicsInit(&ballPhysics, 1, 0.8f, 1, 1, 0);
    physicsSetPosition(&ballPhysics, ball.position[0], ball.position[1], ball.position[2]);
    physicsAddVelocity(&ballPhysics, -100, 0, 20);
    physicsSetAirDeceleration(2.0f);
    
    // --------------------   Set up the GUI.   --------------------
    
    // Set the default GUI text color to BLACK.
    GUIsetTextColor(0.0f, 0.0f, 0.0f);
    
    GUInewText(&mouseLockText, "Mouse Lock: ", 0, 50, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&posText, "Pos: ", 0, 80, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&ballText, "Ball Pos: ", 0, 140, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&ballText2, "Ball Vel: ", 0, 170, (void*)GLUT_BITMAP_HELVETICA_18);
    
    GUIlinkTextToParam(&mouseLockText, &controller.mouseLock, INT_param);
    GUIlinkTextToParam(&posText, cam.position, POINT3_param);
    GUIlinkTextToParam(&ballText, ballPhysics.position, POINT3_param);
    GUIlinkTextToParam(&ballText2, ballPhysics.velocity, POINT3_param);
    GUIlinkTextToParam(&controlDisplayPrompt, "X", CHAR_param);
    
    GUInewFrame(&dataFrame, 1, dataFrameOptions, 5);
    
    // Initialise Control frame elements.
    GUInewText(&controlDisplayPrompt, "Show/Hide controls: ", 0, programWindow.dimensions[1], (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&controlDisplay_forward, "Forward: ", 0, 50, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&controlDisplay_backward, "Backward: ", 0, 80, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&controlDisplay_upward, "Upward: ", 0, 110, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&controlDisplay_downward, "Downward: ", 0, 140, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&controlDisplay_left, "Left: ", 0, 170, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&controlDisplay_right, "Right: ", 0, 200, (void*)GLUT_BITMAP_HELVETICA_18);
    GUInewText(&controlDisplay_mouseLock, "Mouse Control Toggle: ", 0, 230, (void*)GLUT_BITMAP_HELVETICA_18);
    
    GUIlinkTextToParam(&controlDisplay_forward, &controller.camControls->forwardKey, CHAR_param);
    GUIlinkTextToParam(&controlDisplay_backward, &controller.camControls->backwardKey, CHAR_param);
    GUIlinkTextToParam(&controlDisplay_upward, &controller.camControls->upKey, CHAR_param);
    GUIlinkTextToParam(&controlDisplay_downward, &controller.camControls->downKey, CHAR_param);
    GUIlinkTextToParam(&controlDisplay_left, &controller.camControls->strafe_L, CHAR_param);
    GUIlinkTextToParam(&controlDisplay_right, &controller.camControls->strafe_R, CHAR_param);
    GUIlinkTextToParam(&controlDisplay_mouseLock, &controller.camControls->mouseLock, CHAR_param);
    
    GUInewFrame(&controlDisplayFrame, 3, controlDisplayFrameOptions, 7);
    GUIpositionFrame(&controlDisplayFrame, 0, 250);
    GUIdisableFrame(&controlDisplayFrame);  // HIDE the default control display by default.
    
    GUInewLine(&HUDtop, 0, 20, 302, 20, 10.0f, 1.0, 1.0, 0.0);
    GUInewLine(&HUDside, 300, 15, 300, 203, 5.0f, 1.0, 0.5, 0.0);
    GUInewLine(&HUDbottom, 0, 200, 300, 200, 5.0f, 1.0, 0.5, 0.0);
    
    GUInewFrame(&borderFrame, 2, borderFrameOptions, 3);
    
    gameObjectUpdate(&player);
    gameObjectUpdate(&ball);
>>>>>>> origin/master
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

    if(ch == physicsControl_AirDecel.key)
        physicsControl_AirDecel.down = 1;

    if(ch == physicsControl_Gravity.key)
        physicsControl_Gravity.down = 1;

    if(ch == physicsControl_SimSpeed.key)
        physicsControl_SimSpeed.down = 1;
}

void keyboardUp( unsigned char ch, int num1, int num2 )
{
    if(ch != controlKeys.mouseLock.key)
        controllerCheckKeys(&controller, ch);

    if(ch == physicsControl_AirDecel.key)
    {
        physicsControl_AirDecel.down = 0;
        printf("AirDecel UP\n");
    }

    if(ch == physicsControl_Gravity.key)
    {
        physicsControl_Gravity.down = 0;
    }

    if(ch == physicsControl_SimSpeed.key)
    {
        physicsControl_SimSpeed.down = 0;
    }
}

void mouseMove( int x, int y )
{
    controllerCheckMouse(&controller, x, y );
}

void mouseButton( int button, int state, int x, int y )
{
    controllerCheckButtons(&controller, button, state, x, y);
}

void MouseWheel( int button, int dir, int x, int y)
{
    // Ignore one half of the incoming key presses, so functionlaity is only called ONCE.
    if(dir == GLUT_UP)
        return;

    if(button == 3)
    {
        if(physicsControl_AirDecel.down && phys_AirDecel >= 0)
        {
            phys_AirDecel += 0.1f;
            physicsSetAirDeceleration(phys_AirDecel);
        }

        if(physicsControl_Gravity.down && phys_Grav >= 0)
        {
            phys_Grav += 0.1f;
            physicsSetGravity(phys_Grav);
        }

        if(physicsControl_SimSpeed.down && phys_Spd >= 0.1f)
        {
            phys_Spd += 0.1f;
            physicsSetSimulationSpeed(phys_Spd);
        }
    }
    else
    if(button == 4)
    {
        if(physicsControl_AirDecel.down && phys_AirDecel >= 0.1f)
        {
            phys_AirDecel -= 0.1f;
            physicsSetAirDeceleration(phys_AirDecel);
        }

        if(physicsControl_Gravity.down && phys_Grav >= 0.1f)
        {
            phys_Grav -= 0.1f;
            physicsSetGravity(phys_Grav);
        }

        if(physicsControl_SimSpeed.down && phys_Spd >= 0.2f)
        {
            phys_Spd -= 0.1f;
            physicsSetSimulationSpeed(phys_Spd);
        }
    }
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
<<<<<<< HEAD
=======
            
>>>>>>> origin/master
            point3 normal1 = {0,0,0};
            point3 normal2 = {0,0,0};
            
            float penetration = collisionFindNormalBB(&playerBody, roomSurfaces[i], &normal1[0], &normal1[1], &normal1[2], &normal2[0], &normal2[1], &normal2[2]);
            
            playerBody.position[0] -= -(normal1[0] * penetration + normal1[0]);
            playerBody.position[1] -= -(normal1[1] * penetration + normal1[1]);
            playerBody.position[2] -= -(normal1[2] * penetration + normal1[2]);
        }
    
    // Update the camera's position.
    cam.position[0] = playerBody.position[0];
    cam.position[1] = playerBody.position[1];
    cam.position[2] = playerBody.position[2];
    
    // Update the camera.
<<<<<<< HEAD
    if(controller.typeOfController == FIRST_PERSON)
        cameraUpdateFPS(&cam);
    else
        cameraUpdateTPS(&cam);

=======
    cameraUpdate(&cam);
    
>>>>>>> origin/master
    for (i = 0; i < 6; i++)
        if(collisionCollideSB(&ballBounds, roomSurfaces[i]))
        {
            point3 normal1 = {0,0,0};
            point3 normal2 = {0,0,0};
<<<<<<< HEAD

            float penetration = collisionFindNormalSB(&ballBounds, roomSurfaces[i], &normal1[0], &normal1[1], &normal1[2], &normal2[0], &normal2[1], &normal2[2]);

=======
            
            
            penetration = collisionFindNormalSB(&ballBounds, roomSurfaces[i], &normal1[0], &normal1[1], &normal1[2], &normal2[0], &normal2[1], &normal2[2]);
            
>>>>>>> origin/master
            if(normal1[0] != 0)
                ballPhysics.velocity[0] *= -1 * ballPhysics.bounceDecay;
            
            if(normal1[1] != 0)
            {
                if(abs(ballPhysics.velocity[1]) < 1.0f * physicsGetParam(PHYS_SPEED))
                {
                    ballPhysics.velocity[1] = 0;
                    ballPhysics.hasGravity = 0;
                }
                else
                    ballPhysics.velocity[1] *= -1 * ballPhysics.bounceDecay;
            }
            
            if(normal1[2] != 0)
                ballPhysics.velocity[2] *= -1 * ballPhysics.bounceDecay;
            
            physicsUpdate(&ballPhysics, FRAMERATE);
<<<<<<< HEAD
=======
            
            /*ballPhysics.position[0] -= -(normal1[0] * penetration + normal1[0]);
             ballPhysics.position[1] -= -(normal1[1] * penetration) + normal1[1];
             ballPhysics.position[2] -= -(normal1[2] * penetration + normal1[2]);*/
            
            printf("ball velocity");
            printPoint(ballPhysics.velocity);
            
            printf("ball Normal: ");
            printPoint(normal1);
            printf("floor Normal: ");
            printPoint(normal2);
>>>>>>> origin/master
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
    GUIrenderFrame(&debugFrame);            // Render any debug stuff.
<<<<<<< HEAD
    GUIrenderFrame(&simulationFrame);       // Render the simulation parameters.

=======
    
>>>>>>> origin/master
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
<<<<<<< HEAD

    if(controller.typeOfController != FIRST_PERSON)
        collisionDebug_DrawB(&playerBody);

    glEnable(GL_TEXTURE_2D);

    texPlaneDraw(&testPlane);
    texPlaneDraw(&testPlane2);
    texPlaneDraw(&testPlane3);
    texPlaneDraw(&testPlane4);
    texPlaneDraw(&testPlane5);

    glDisable(GL_TEXTURE_2D);

    // --------------------   STOP drawing the environment.   --------------------

=======
    
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
    
>>>>>>> origin/master
    glutSwapBuffers();
    glFlush();
}


int main( int argc, char** argv )
{
    // Initialisation.
    glutInit(&argc,argv);
    
    /* Texturing
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    */
    
    GLWindowCreate(&programWindow, "Test", 0, 0, 1000, 1000);
    myinit();
    
    // Function callbacks.
    glutDisplayFunc(display);
    
    /* Texturing calls.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    myTex[0] = GetTexImage("BrickWall.raw");
    myTex[1] = GetTexImage("Roof.raw");
    myTex[2] = GetTexImage("Floor.Raw");
    myTex[3] = GetTexImage("GoalWall.raw");
    
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    */
    
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboard);
<<<<<<< HEAD
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(MouseWheel);

=======
    
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMove);
    
>>>>>>> origin/master
    // Timer functions.
    glutTimerFunc(FRAMERATE_MILLIS, FrameUpdate, 0);
    
    // OpenGL main loop.
    glutMainLoop();
    return 0;
}