
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

ControlKey ExitKey;
short ExitRequested = 0;

ControlKey controlDisplayKey;
short controlDisplayRequested = 0;

ControlKey physicsControl_AirDecel;
float phys_AirDecel = 0.0f;
ControlKey physicsControl_Gravity;
float phys_Grav = 0.0f;
ControlKey physicsControl_SimSpeed;
float phys_Spd = 0.0f;
ControlKey throwForceControl;
ControlKey physicsControl_BallBounce;

int redScore = 0;
int blueScore = 0;

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
GUItext scoreTxtRed;
GUItext scoreTxtBlue;
GUItext throwForceText;
GUIline redBorder1;
GUIline redBorder2;
GUIline blueBorder1;
GUIline blueBorder2;

GUItext simParam1;
GUItext simParam2;
GUItext simParam3;
GUItext simParam4;

GUIline HUDtop;
GUIline HUDside;
GUIline HUDbottom;

GUItext controlDisplayPrompt;

GUIframe dataFrame;
GUIframeEntry dataFrameOptions[] = {{&mouseLockText, GUI_TEXT}, {&posText, GUI_TEXT}, {&ballText, GUI_TEXT}, {&ballText2, GUI_TEXT},
                                    {&controlDisplayPrompt, GUI_TEXT},
                                    {&scoreTxtRed, GUI_TEXT}, {&redBorder1, GUI_LINE}, {&redBorder2, GUI_LINE},
                                    {&scoreTxtBlue, GUI_TEXT}, {&blueBorder1, GUI_LINE}, {&blueBorder2, GUI_LINE}};

GUIframe simulationFrame;
GUIframeEntry simFrameOptions[] = {{&simParam1, GUI_TEXT}, {&simParam2, GUI_TEXT}, {&simParam3, GUI_TEXT}, {&throwForceText, GUI_TEXT}, {&simParam4, GUI_TEXT}};

GUIframe borderFrame;
GUIframeEntry borderFrameOptions[] = {{&HUDbottom, GUI_LINE}, {&HUDtop, GUI_LINE}, {&HUDside, GUI_LINE}};

// Ball GameObject params.
collider_Sphere ballBounds;
collider_Sphere ballModel;
RigidBody ballPhysics;
GameObject ball;
GameObjectComponent ballComponents[] = {{&ballBounds, COLL_SPHERE}, {&ballPhysics, RIGIDBODY}, {&ballModel, MODEL_SPHERE}};

// Room GameObject params.
// Surface colliders.
collider_AABB roomFloor;
collider_AABB roomWall_N;
collider_AABB roomWall_S;
collider_AABB roomWall_E;
collider_AABB roomWall_W;
collider_AABB roomRoof;

collider_Sphere redGoal;
collider_Sphere blueGoal;

// 2D Texture planes.
TexturedPlane testPlane;
TexturedPlane testPlane2;
TexturedPlane testPlane3;
TexturedPlane testPlane4;
TexturedPlane testPlane5;
GameObject room;
GameObjectComponent roomComponents[] = {{&roomFloor, COLL_BOX}, {&roomWall_N, COLL_BOX}, {&roomWall_S, COLL_BOX}, {&roomWall_E, COLL_BOX}, {&roomWall_W, COLL_BOX}, {&roomRoof, COLL_BOX},
                                        {&redGoal, COLL_SPHERE}, {&blueGoal, COLL_SPHERE},
                                        {&testPlane, MODEL_TEXPLANE}, {&testPlane2, MODEL_TEXPLANE}, {&testPlane3, MODEL_TEXPLANE}, {&testPlane4, MODEL_TEXPLANE}, {&testPlane5, MODEL_TEXPLANE}};

collider_AABB* roomSurfaces[] = {&roomFloor, &roomWall_N, &roomWall_S, &roomWall_E, &roomWall_W, &roomRoof};

// Player GameObject params.
collider_Sphere playerRange;
point3 playerRangeNormal;
collider_AABB playerBody;
GameObject player;
GameObjectComponent playerComponents[] = {{&playerRange, COLL_SPHERE}, {&playerBody, COLL_BOX}};

// Set up interaction control structs.
interactionController interController;
interactionControlKeys interControls;

TexturedPlane controlImg;
TexturedPlane exitScreen;

// Convenient method for printing an entire point in a readable format.
void printPoint(point3 p)
{
    printf("X: %1.3f, Y: %1.3f, Z: %1.3f\n", p[0], p[1], p[2]);
    return;
}

// Menu function for swapping camera control types.
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

// Custom initialisation function.
void myinit( void )
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(5.0);

    // --------------------   Set up the camera.   --------------------

            cameraInit(&cam, -500, 500, -500, 500, 0.01f, 10000.0f, 45, 1, PERSPECTIVE);
            cameraOrientate_f(&cam, -100, 100, 200, 80, 100, 0);
            cam.mouseCentre[0] = programWindow.dimensions[0] * 0.5f;
            cam.mouseCentre[1] = programWindow.dimensions[1] * 0.5f;

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

    // --------------------   Set up the interaction parameters and control keys (non-physics).   --------------------

            // Bind control keys.
            bindKeysToControls(&interController, &playerRange, &interControls);
            changingInteractionKeyControls(&interController, 'f', 't', 'm');
            interController.force = 150.0f;

            throwForceControl.key = '4';
            ExitKey.key = 27;               // Escape key.
            controlDisplayKey.key = 'x';

    // --------------------   Set up the popup menus.   --------------------

            GLPopupMenuCreate(&cameraMenu, "Main Menu", camMenuFunc, GLUT_MIDDLE_BUTTON, camOptions, 2);

    // --------------------   Set up the GameObjects.   --------------------

            // Set up the player.
            gameObjectInit(&player, cam.position[0], cam.position[1], cam.position[2], playerComponents, 2);

            // Set up the ball.
            gameObjectInit(&ball, 0,200,0, ballComponents, 3);

            // Set up the room.
            gameObjectInit(&room, 0, 0, 0, roomComponents, 13);

    // --------------------   Set up the collision colliders.   --------------------

            // Initialise the player colliders.
            collisionInit_S(&playerRange, 0,0,0, 300);
            collisionInit_B(&playerBody, 0, 0, 0, 20, 20, 20);

            // Initialise the ball collider.
            collisionInit_S(&ballBounds, 0, 0, 0, 30);
            collisionInit_S(&ballModel, 0, 0, 0, ballBounds.radius);

            // Initialise the room colliders.
            collisionInit_B(&roomFloor, 0, -100, 0, 3200, 200, 2000);
            collisionInit_B(&roomWall_N, 0, 250, 1000, 3200, 500, 100);
            collisionInit_B(&roomWall_S, 0, 250, -1000, 3200, 500, 100);
            collisionInit_B(&roomWall_E, 1600, 250, 0, 100, 500, 2000);
            collisionInit_B(&roomWall_W, -1600, 250, 0, 100, 500, 2000);
            collisionInit_B(&roomRoof, 0, 600, 0, 3200, 200, 2000);

            collisionInit_S(&redGoal, -1012, 0, 0, 210);
            collisionInit_S(&blueGoal, 1012, 0, 0, 210);

            collisionDebug_Toggle(0);

    // --------------------   Set up the Physics.   --------------------

            physicsSetSimulationSpeed(5.0f);

            physicsInit(&ballPhysics, 1, 0.8f, 1, 1, 0);
            physicsSetPosition(&ballPhysics, ball.position[0], ball.position[1], ball.position[2]);
            physicsSetAirDeceleration(0.1f);

            physicsControl_AirDecel.key = '1';
            phys_AirDecel = physicsGetParam(PHYS_AIRDECEL);
            physicsControl_Gravity.key = '2';
            phys_Grav = physicsGetParam(PHYS_GRAVITY);
            physicsControl_SimSpeed.key = '3';
            phys_Spd = physicsGetParam(PHYS_SPEED);
            physicsControl_BallBounce.key = '5';

    // --------------------   Set up the GUI.   --------------------

            // Set the default GUI text color to BLACK.
            GUIsetTextColor(0.0f, 0.0f, 0.0f);

            // -------------------------- DATA FRAME --------------------------------------
            GUInewText(&mouseLockText, "Mouse Lock: ", 0, 100, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&posText, "Pos: ", 0, 130, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&ballText, "Ball Pos: ", 0, 160, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&ballText2, "Ball Vel: ", 0, 190, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&scoreTxtRed, "RED: ", 5, 20, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&scoreTxtBlue, "BLUE: ", 205, 20, (void*)GLUT_BITMAP_HELVETICA_18);

            GUInewLine(&redBorder1, 0, 25, 200, 25, 3, 1, 0, 0);
            GUInewLine(&redBorder2, 200, 25, 200, 0, 3, 1, 0, 0);
            GUInewLine(&blueBorder1, 200, 25, 400, 25, 3, 0, 0, 1);
            GUInewLine(&blueBorder2, 400, 25, 400, 0, 3, 0, 0, 1);

            GUIlinkTextToParam(&mouseLockText, &controller.mouseLock, INT_param);
            GUIlinkTextToParam(&posText, cam.position, POINT3_param);
            GUIlinkTextToParam(&ballText, ballPhysics.position, POINT3_param);
            GUIlinkTextToParam(&ballText2, ballPhysics.velocity, POINT3_param);
            GUIlinkTextToParam(&scoreTxtRed, &redScore, INT_param);
            GUIlinkTextToParam(&scoreTxtBlue, &blueScore, INT_param);

            GUInewFrame(&dataFrame, 1, dataFrameOptions, 11);

            // -------------------------- SIMULATION FRAME --------------------------------------
            GUInewText(&simParam1, "1 - Air Density : ", 0, 30, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&simParam2, "2 - Gravity : ", 0, 60, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&simParam3, "3 - Simulation Speed : ", 0, 90, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&throwForceText, "4 - Throw Force : ", 0, 120, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&simParam4, "5 - Ball bounce efficiency : ", 0, 150, (void*)GLUT_BITMAP_HELVETICA_18);
            GUInewText(&controlDisplayPrompt, "Show/Hide controls with X", 0, programWindow.dimensions[1], (void*)GLUT_BITMAP_HELVETICA_18);

            GUIlinkTextToParam(&simParam1, &phys_AirDecel, FLOAT_param);
            GUIlinkTextToParam(&simParam2, &phys_Grav, FLOAT_param);
            GUIlinkTextToParam(&simParam3, &phys_Spd, FLOAT_param);
            GUIlinkTextToParam(&throwForceText, &interController.force, FLOAT_param);
            GUIlinkTextToParam(&simParam4, &ballPhysics.bounceDecay, FLOAT_param);

            GUInewFrame(&simulationFrame, 2, simFrameOptions, 5);
            GUIpositionFrame(&simulationFrame, 0, 200);

            // -------------------------- BORDER FRAME --------------------------------------
            GUInewLine(&HUDtop, 0, 50, 302, 50, 10.0f, 1.0, 1.0, 0.0);
            GUInewLine(&HUDside, 300, 45, 300, 363, 5.0f, 1.0, 0.5, 0.0);
            GUInewLine(&HUDbottom, 0, 360, 300, 360, 5.0f, 1.0, 0.5, 0.0);

            GUInewFrame(&borderFrame, 4, borderFrameOptions, 3);

    // --------------------   Set up the Textured Surfaces.   --------------------

            texPlaneInit(&testPlane, 0, 250, 951, 3200, 500, "\\IMG\\BrickTex2.raw");
            texPlaneSetRotation(&testPlane, 0, 180, 0);
            texPlaneSetCornerColor(&testPlane, 0, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane, 1, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane, 2, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane, 3, 1, 0.7f, 0);

            texPlaneInit(&testPlane2, 0, 250, -951, 3200, 500, "\\IMG\\BrickTex2.raw");
            texPlaneSetRotation(&testPlane2, 0, 0, 0);
            texPlaneSetCornerColor(&testPlane2, 0, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane2, 1, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane2, 2, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane2, 3, 1, 0.7f, 0);

            texPlaneInit(&testPlane3, -1551, 250, 0, 2000, 500, "\\IMG\\BrickTex2.raw");
            texPlaneSetRotation(&testPlane3, 0, 90, 0);
            texPlaneSetCornerColor(&testPlane3, 0, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane3, 1, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane3, 2, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane3, 3, 1, 0.7f, 0);

            texPlaneInit(&testPlane4, 1551, 250, 0, 2000, 500, "\\IMG\\BrickTex2.raw");
            texPlaneSetRotation(&testPlane4, 0, -90, 0);
            texPlaneSetCornerColor(&testPlane4, 0, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane4, 1, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane4, 2, 1, 0.7f, 0);
            texPlaneSetCornerColor(&testPlane4, 3, 1, 0.7f, 0);

            texPlaneInit(&testPlane5, 0, 0, 0, 3200, 2000, "\\IMG\\FloorTex.raw");
            texPlaneSetRotation(&testPlane5, -90, 0, 0);
            texPlaneSetCornerColor(&testPlane5, 0, 1, 0, 0);
            texPlaneSetCornerColor(&testPlane5, 1, 1, 0, 0);
            texPlaneSetCornerColor(&testPlane5, 2, 0, 0, 1);
            texPlaneSetCornerColor(&testPlane5, 3, 0, 0, 1);

            texPlaneInit(&controlImg, 240, 800, 0, 480, 300, "\\IMG\\Controls.raw");
            texPlaneSetRotation(&controlImg, 0, 180, 0);
            texPlaneSetCornerColor(&controlImg, 0, 1, 1, 1);
            texPlaneSetCornerColor(&controlImg, 1, 1, 1, 1);
            texPlaneSetCornerColor(&controlImg, 2, 1, 1, 1);
            texPlaneSetCornerColor(&controlImg, 3, 1, 1, 1);

            texPlaneInit(&exitScreen, 480, 500, 0.1f, 960, 600, "\\IMG\\ExitScreen.raw");
            texPlaneSetRotation(&exitScreen, 0, 180, 0);
            texPlaneSetCornerColor(&exitScreen, 0, 1, 1, 1);
            texPlaneSetCornerColor(&exitScreen, 1, 1, 1, 1);
            texPlaneSetCornerColor(&exitScreen, 2, 1, 1, 1);
            texPlaneSetCornerColor(&exitScreen, 3, 1, 1, 1);

            glEnable(GL_TEXTURE_2D);

            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

            gameObjectUpdate(&player);
            gameObjectUpdate(&ball);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    programWindow.dimensions[0] = w;
    programWindow.dimensions[1] = h;

    cam.rightPlane = -w * 0.5f;
    cam.leftPlane = w * 0.5f;
    cam.topPlane = h * 0.5f;
    cam.bottomPlane = -h * 0.5f;

    cam.mouseCentre[0] = programWindow.dimensions[0] * 0.5f;
    cam.mouseCentre[1] = programWindow.dimensions[1] * 0.5f;

    cameraProject(&cam);
}

void keyboard( unsigned char ch, int num1, int num2 )
{
    interactionCheckKeys(&interController, ch);
    controllerCheckKeys(&controller, ch);

    if(ch == physicsControl_AirDecel.key)
        physicsControl_AirDecel.down = 1;

    if(ch == physicsControl_Gravity.key)
        physicsControl_Gravity.down = 1;

    if(ch == physicsControl_SimSpeed.key)
        physicsControl_SimSpeed.down = 1;

    if(ch == throwForceControl.key)
        throwForceControl.down = 1;

    if(ch == physicsControl_BallBounce.key)
        physicsControl_BallBounce.down = 1;
}

void keyboardUp( unsigned char ch, int num1, int num2 )
{
    interactionCheckKeys(&interController, ch);

    if(ch != controlKeys.mouseLock.key)
        controllerCheckKeys(&controller, ch);

    if(ch == physicsControl_AirDecel.key)
        physicsControl_AirDecel.down = 0;

    if(ch == physicsControl_Gravity.key)
        physicsControl_Gravity.down = 0;

    if(ch == physicsControl_SimSpeed.key)
        physicsControl_SimSpeed.down = 0;

    if(ch == throwForceControl.key)
        throwForceControl.down = 0;

    if(ch == physicsControl_BallBounce.key)
        physicsControl_BallBounce.down = 0;

    if(ch == controlDisplayKey.key)
        controlDisplayRequested = (controlDisplayRequested == 0) ? 1 : 0;

    if(ch == ExitKey.key)
    {
        if(ExitRequested == 1)
            exit(0);
        else
            ExitRequested = 1;
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
        if(physicsControl_AirDecel.down && phys_AirDecel >= 0 && phys_AirDecel < 0.99f)
        {
            phys_AirDecel += 0.01f;
            physicsSetAirDeceleration(phys_AirDecel);
        }

        if(physicsControl_Gravity.down && phys_Grav >= 0)
        {
            phys_Grav += 0.1f;
            physicsSetGravity(phys_Grav);
        }

        if(physicsControl_SimSpeed.down && phys_Spd >= 0.1f && phys_Spd <= 9.9)
        {
            phys_Spd += 0.1f;
            physicsSetSimulationSpeed(phys_Spd);
        }

        if(throwForceControl.down && interController.force <= 290)
        {
            interController.force += 10.0f;
        }

        if(physicsControl_BallBounce.down && ballPhysics.bounceDecay <= 0.9f)
        {
            ballPhysics.bounceDecay += 0.05f;
        }
    }
    else
    if(button == 4)
    {
        if(physicsControl_AirDecel.down && phys_AirDecel >= 0.01f)
        {
            phys_AirDecel -= 0.01f;
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

        if(throwForceControl.down && interController.force > 100.0f)
        {
            interController.force -= 10.0f;
        }

        if(physicsControl_BallBounce.down && ballPhysics.bounceDecay >= 0.1f)
        {
            ballPhysics.bounceDecay -= 0.05f;
        }
    }
}

void FrameUpdate(int value)
{
    glutTimerFunc(FRAMERATE_MILLIS, FrameUpdate, 0);

    controllerKeyUpdate(&controller, FRAMERATE);

    gameObjectSetPos(&player, cam.position[0], cam.position[1], cam.position[2]);
    gameObjectUpdate(&player);

    // Keep the player within the room using the below code.
    int i = 0;
    for(i = 0; i < 6; i++)
        if(collisionCollideBB(&playerBody, roomSurfaces[i]))
        {
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

    if(controller.typeOfController == FIRST_PERSON)
        cameraUpdateFPS(&cam);
    else
        cameraUpdateTPS(&cam);

    // Check for any ball <-> surface collisions and alter the ball's trajectory if there is one.
    for (i = 0; i < 6; i++)
        if(collisionCollideSB(&ballBounds, roomSurfaces[i]))
        {
            point3 normal1 = {0,0,0};
            point3 normal2 = {0,0,0};

            float penetration = collisionFindNormalSB(&ballBounds, roomSurfaces[i], &normal1[0], &normal1[1], &normal1[2], &normal2[0], &normal2[1], &normal2[2]);

            if(normal1[0] != 0)
                ballPhysics.velocity[0] *= -1 * ballPhysics.bounceDecay;

            if(normal1[1] != 0)
            {
                if(abs(ballPhysics.velocity[1]) < 1.0f * physicsGetParam(PHYS_SPEED) && normal1[1] == -1)
                {
                    ballPhysics.velocity[1] = 0;
                    ballPhysics.hasGravity = 0;
                }
                else
                    ballPhysics.velocity[1] *= -1 * ballPhysics.bounceDecay;
            }

            if(normal1[2] != 0)
                ballPhysics.velocity[2] *= -1 * ballPhysics.bounceDecay;

            // Use of penetration value is done instead by this update.
            physicsUpdate(&ballPhysics, FRAMERATE);
        }

    if(collisionCollideSS(&ballBounds, &redGoal) && !interController.pickUpCheck)
    {
        redScore++;

        // TODO: move the ball back to the centre of the area.
        physicsSetPosition(&ballPhysics, 0, 50, 0);
        ballPhysics.velocity[0] = 0;
        ballPhysics.velocity[1] = 0;
        ballPhysics.velocity[2] = 0;
        gameObjectSetPos(&ball, 0, 50, 0);
    }

    if(collisionCollideSS(&ballBounds, &blueGoal) && !interController.pickUpCheck)
    {
        blueScore++;

        // TODO: move the ball back to the centre of the area.
        physicsSetPosition(&ballPhysics, 0, 50, 0);
        ballPhysics.velocity[0] = 0;
        ballPhysics.velocity[1] = 0;
        ballPhysics.velocity[2] = 0;
        gameObjectSetPos(&ball, 0, 50, 0);
    }

    checkForPickUp(&playerRange, &ballBounds, &interController);
    throwBall(&interController, &cam, &ballPhysics);
    moveBallToPlayer(&interController, &cam, &ball, &ballPhysics);

    gameObjectUpdate(&ball);

    // Update the screen.
    glutPostRedisplay();
}

void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --------------------   START Drawing the GUI.   --------------------
    GUIenable2DRendering(&programWindow);

    // Draw some backgrounds to make the HUD more readable.
    glPushMatrix();
    glLoadIdentity();
        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
            glVertex3f(0, 50, -0.1f);
            glVertex3f(0, 360, -0.1f);
            glVertex3f(300, 360, -0.1f);
            glVertex3f(300, 50, -0.1f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
            glVertex3f(0, 0, -0.1f);
            glVertex3f(200, 0, -0.1f);
            glVertex3f(200, 25, -0.1f);
            glVertex3f(0, 25, -0.1f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
            glVertex3f(200, 0, -0.1f);
            glVertex3f(400, 0, -0.1f);
            glVertex3f(400, 25, -0.1f);
            glVertex3f(200, 25, -0.1f);
        glEnd();
    glPopMatrix();

    GUIrenderFrame(&dataFrame);             // Render data.
    GUIrenderFrame(&borderFrame);           // Render borders.
    GUIrenderFrame(&simulationFrame);       // Render the simulation parameters.

    if(controlDisplayRequested == 1)
    {
        glPushMatrix();
        glLoadIdentity();
        texPlaneDraw(&controlImg);
        glPopMatrix();
    }

    if(ExitRequested == 1)
    {
        glPushMatrix();
        glLoadIdentity();
        texPlaneDraw(&exitScreen);
        glPopMatrix();
    }

    GUIdisable2DRendering(&programWindow);
    // --------------------   STOP Drawing the GUI.   --------------------

    // --------------------   START drawing the environment.   --------------------

    // Render everything related to the room.
    gameObjectRender(&room);

    // Render everything related to the ball.
    gameObjectRender(&ball);

    if(controller.typeOfController != FIRST_PERSON)
    {
        collisionDebug_Toggle(1);
        collisionDebug_DrawB(&playerBody);
        collisionDebug_Toggle(0);
    }


    // --------------------   STOP drawing the environment.   --------------------

    glutSwapBuffers();
    glFlush();
}


int main( int argc, char** argv )
{
    // Initialisation.
    glutInit(&argc,argv);

    GLWindowCreate(&programWindow, "Test", 0, 0, 1000, 1000);
    myinit();

    // Function callbacks.
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(MouseWheel);

    // Timer functions.
    glutTimerFunc(FRAMERATE_MILLIS, FrameUpdate, 0);

    // OpenGL main loop.
    glutMainLoop();
    return 0;
}
