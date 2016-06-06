#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#include <GL/freeglut.h>

#include "CameraController.h"

#define PI 3.14159265

void controllerBindCameraToKeys(CameraController* controller, Camera* cam, CameraControlKeys* controls, ControlType typeOfController)
{
    controller->cam = cam;
    controller->camControls = controls;
    controller->typeOfController = typeOfController;
}

void controllerEditBasicKeyControls(CameraController* controller, char fKey, char bKey, char uKey, char dKey, char lKey, char rKey, char lockKey, float speedMod)
{

    if(fKey != '\n')
        controller->camControls->forwardKey.key = fKey;

    if(bKey != '\n')
        controller->camControls->backwardKey.key = bKey;

    if(uKey != '\n')
        controller->camControls->upKey.key = uKey;

    if(dKey != '\n')
        controller->camControls->downKey.key = dKey;

    if(lKey != '\n')
        controller->camControls->strafe_L.key = lKey;

    if(rKey != '\n')
        controller->camControls->strafe_R.key = rKey;

    if(lockKey != '\n')
        controller->camControls->mouseLock.key = lockKey;

    if(speedMod >= 0)
        controller->speedModifier = speedMod;
}

void controllerEditMouseControls(CameraController* controller, float sensitivityX, float sensitivityY)
{
    if(sensitivityX >= 0.0f)
        controller->mouseSensitivityX = sensitivityX;

    if(sensitivityY >= 0.0f)
        controller->mouseSensitivityY = sensitivityY;
}

void controllerToggleMouseLock(CameraController* controller)
{

    if(controller->mouseLock)
    {
        controller->mouseLock = 0;
    }
    else
    {
        controller->mouseLock = 1;
    }

    switch(controller->mouseLock)
    {
        case 0:
            printf("Mouse control disabled\n");
            controller->cam->rotation[1] += controller->cam->mouseOriginDelta[0];
            controller->cam->rotation[0] += controller->cam->mouseOriginDelta[1];
            controller->cam->mouseOrigin[0] = 500;
            controller->cam->mouseOrigin[1] = 500;
            glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
            break;

        case 1:
            printf("Mouse control enabled\n");
            glutWarpPointer(500, 500);
            controller->mousePos[0] = 500;
            controller->mousePos[1] = 500;
            controller->cam->mouseOriginDelta[0] = 0;
            controller->cam->mouseOriginDelta[1] = 0;
            controller->cam->mouseOrigin[0] = 500;
            controller->cam->mouseOrigin[1] = 500;
            controller->skipCheck = 0;
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            break;

        default:
            printf("Error: Mouse lock set to a number other than 1 or 0. Nothing was done!");
            break;
    }
}

void controllerCheckKeys(CameraController* controller, char ch)
{
    if(ch == controller->camControls->forwardKey.key)
    {
        controller->camControls->forwardKey.down = (controller->camControls->forwardKey.down == 0) ? 1 : 0;
    }
    else
    if(ch == controller->camControls->backwardKey.key)
    {
        controller->camControls->backwardKey.down = (controller->camControls->backwardKey.down == 0) ? 1 : 0;
    }
    else
    if(ch == controller->camControls->upKey.key)
    {
        controller->camControls->upKey.down = (controller->camControls->upKey.down == 0) ? 1 : 0;
    }
    else
    if(ch == controller->camControls->downKey.key)
    {
        controller->camControls->downKey.down = (controller->camControls->downKey.down == 0) ? 1 : 0;
    }
    else
    if(ch == controller->camControls->strafe_L.key)
    {
        controller->camControls->strafe_L.down = (controller->camControls->strafe_L.down == 0) ? 1 : 0;
    }
    else
    if(ch == controller->camControls->strafe_R.key)
    {
        controller->camControls->strafe_R.down = (controller->camControls->strafe_R.down == 0) ? 1 : 0;
    }
    else
    if(ch == controller->camControls->mouseLock.key)
    {
        controllerToggleMouseLock(controller);
    }

    return;
}

void controllerKeyUpdate(CameraController* controller, float deltaTime)
{
    if(controller->camControls->forwardKey.down)
    {
        if(controller->typeOfController == TOP_DOWN)
            controller->cam->position[1] += -1 * controller->speedModifier;
        else
        {
            float directionMod = 1.0f;

            if(controller->camControls->strafe_L.down || controller->camControls->strafe_R.down)
            {
                directionMod *= sin(45);
            }

            controller->cam->position[0] += directionMod * controller->speedModifier * controller->cam->lookAt[0] * deltaTime;
            controller->cam->position[2] += directionMod * controller->speedModifier * controller->cam->lookAt[2] * deltaTime;
        }
    }

    if(controller->camControls->backwardKey.down)
    {
        if(controller->typeOfController == TOP_DOWN)
            controller->cam->position[1] += 1 * controller->speedModifier;
        else
        {
            float directionMod = 1.0f;

            if(controller->camControls->strafe_L.down || controller->camControls->strafe_R.down)
            {
                directionMod *= sin(45);
            }

            controller->cam->position[0] += -directionMod * controller->speedModifier * controller->cam->lookAt[0] * deltaTime;
            controller->cam->position[2] += -directionMod * controller->speedModifier * controller->cam->lookAt[2] * deltaTime;
        }
    }

    if(controller->camControls->upKey.down)
    {
        if(controller->typeOfController == TOP_DOWN)
            controller->cam->position[2] += 1 * controller->speedModifier;
        else
            controller->cam->position[1] += 1 * controller->speedModifier * deltaTime;
    }

    if(controller->camControls->downKey.down)
    {
        if(controller->typeOfController == TOP_DOWN)
            controller->cam->position[2] += -1 * controller->speedModifier;
        else
            controller->cam->position[1] += -1 * controller->speedModifier * deltaTime;
    }

    if(controller->camControls->strafe_L.down)
    {
        float directionMod = 1.0f;

        if(controller->camControls->forwardKey.down || controller->camControls->backwardKey.down)
        {
            directionMod *= sin(45);
        }

        controller->cam->position[0] += -directionMod * controller->speedModifier * controller->cam->rightVector[2] * deltaTime;
        controller->cam->position[2] += -directionMod * controller->speedModifier * controller->cam->rightVector[0] * deltaTime;
    }

    if(controller->camControls->strafe_R.down)
    {
        float directionMod = 1.0f;

        if(controller->camControls->forwardKey.down || controller->camControls->backwardKey.down)
        {
            directionMod *= sin(45);
        }

        controller->cam->position[0] += directionMod * controller->speedModifier * controller->cam->rightVector[2] * deltaTime;
        controller->cam->position[2] += directionMod * controller->speedModifier * controller->cam->rightVector[0] * deltaTime;
    }
}

void controllerCheckMouse(CameraController* controller, int x, int y)
{
    // Only execute functionality if the controller's mouse lock has been set to TRUE, and the controller isn't a top-down type.
    if(controller->mouseLock == 1 && controller->typeOfController != TOP_DOWN)
    {
        // Update the controllers tracker for mouse position.
        if(controller->skipCheck == 1)
        {
            controller->mousePos[0] = x;
            controller->mousePos[1] = y;

            if(controller->mousePos[0] != controller->cam->mouseCentre[0] || controller->mousePos[1] != controller->cam->mouseCentre[1])
            {
                // Calculate the mouse movement changes.
                float checkY = controller->cam->mouseOriginDelta[1] - (y - controller->cam->mouseOrigin[1]) * controller->mouseSensitivityY;

                // Update the x rotation.
                controller->cam->mouseOriginDelta[0] += (x - controller->cam->mouseOrigin[0]) * controller->mouseSensitivityX;

                // Clamp the y rotation.
                if(controller->cam->rotation[0] + checkY < 1.57f && controller->cam->rotation[0] + checkY > -1.57f)
                {
                    controller->cam->mouseOriginDelta[1] -= (y - controller->cam->mouseOrigin[1]) * controller->mouseSensitivityY;
                }

                // Update the lookAt co-ordinates.
                controller->cam->lookAt[0] = sin(controller->cam->rotation[1] + controller->cam->mouseOriginDelta[0]);
                controller->cam->lookAt[1] = sin(controller->cam->rotation[0] + controller->cam->mouseOriginDelta[1]);
                controller->cam->lookAt[2] = -cos(controller->cam->rotation[1] + controller->cam->mouseOriginDelta[0]);

                controller->cam->rightVector[0] = controller->cam->lookAt[0];
                controller->cam->rightVector[2] = -controller->cam->lookAt[2];

                controller->cam->mouseOrigin[0] = controller->cam->mouseCentre[0];
                controller->cam->mouseOrigin[1] = controller->cam->mouseCentre[1];

                glutWarpPointer(controller->cam->mouseCentre[0], controller->cam->mouseCentre[1]);
            }
        }
        else
        {
            controller->skipCheck = 1;
        }
    }

}

void controllerCheckButtons(CameraController* controller, int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_UP)
        {
            controller->cam->rotation[1] += controller->cam->mouseOriginDelta[0];
            controller->cam->rotation[0] += controller->cam->mouseOriginDelta[1];
            controller->cam->mouseOrigin[0] = -1;
            controller->cam->mouseOrigin[1] = -1;
        }
        else
        {
            controller->cam->mouseOrigin[0] = x;
            controller->cam->mouseOrigin[1] = y;
        }
    }
}
