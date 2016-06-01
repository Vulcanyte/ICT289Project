
#include "Interaction.h"
#include "GameObject.h"
#include "Camera.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// binds controls
void bindKeysToControls(interactionController* controller, collider_Sphere* charCS, interactionControlKeys* controls)
{
    controller->player = charCS;
    controller->keybinds = controls;
}

// to change the binds
void changingInteractionKeyControls(interactionController* controller, char pKey, char tKey, char eKey)
{
    if(pKey != '\n')
        controller->keybinds->pickUpKey = pKey;

    if(tKey != '\n')
        controller->keybinds->throwKey = tKey;

    if(eKey != '\n')
        controller->keybinds->exitKey = eKey;
}

// function to check if the ball can be picked up
short checkForPickUp(collider_Sphere* charCS, collider_Sphere* ballCS, interactionController* controller, char ch)
{
    if (collisionCollideSS(charCS, ballCS) == 1 )
    {
        if(ch == controller->keybinds->pickUpKey)
        {
            return 1;
        }
    }

    return 0;
}

void moveBallToPlayer(Camera cam)
{
    collider_Sphere ball; // Creates ball
    GameObjectComponent ballComponent = {&ball, MODEL}; // Makes ball a model
    GameObject gameBall; // Makes a gameObject for ball

    gameObjectSetPos(&gameBall, cam.position[0], cam.position[1], cam.position[2]); // Sets position of ball to in front of the camera.
}
