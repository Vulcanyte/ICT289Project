
#include "Interaction.h"

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
        controller->keybinds->pickUpKey.key = pKey;

    if(tKey != '\n')
        controller->keybinds->throwKey.key = tKey;

    if(eKey != '\n')
        controller->keybinds->exitKey.key = eKey;
}

void interactionCheckKeys(interactionController* controller, char ch)
{
    if(ch == controller->keybinds->pickUpKey.key)
        controller->keybinds->pickUpKey.down = (controller->keybinds->pickUpKey.down == 0) ? 1 : 0;

    if(ch == controller->keybinds->throwKey.key)
        controller->keybinds->throwKey.down = (controller->keybinds->throwKey.down == 0) ? 1 : 0;

    if(ch == controller->keybinds->exitKey.key)
        controller->keybinds->exitKey.down = (controller->keybinds->exitKey.down == 0) ? 1 : 0;
}

// function to check if the ball can be picked up
short checkForPickUp(collider_Sphere* charCS, collider_Sphere* ballCS, interactionController* controller)
{
    if (collisionCollideSS(charCS, ballCS))
    {
        if(controller->keybinds->pickUpKey.down)
        {
            controller->pickUpCheck = 1;
            return 1;
        }
    }

    return 0;
}

void moveBallToPlayer(interactionController* controller, Camera* cam, GameObject* ball, RigidBody* ballPhysics)
{
    if(controller->pickUpCheck)
    {
        ballPhysics->hasGravity = 0;
        ballPhysics->velocity[0] = 0;
        ballPhysics->velocity[1] = 0;
        ballPhysics->velocity[2] = 0;
        physicsSetPosition(ballPhysics, cam->position[0] + cam->lookAt[0] * 200, cam->position[1] + cam->lookAt[1] * 200, cam->position[2] + cam->lookAt[2] * 200);
        //gameObjectUpdate(ball);
    }
}

void throwBall(interactionController* controller, Camera* cam, RigidBody* ballPhysics)
{
    if(controller->pickUpCheck && controller->keybinds->throwKey.down)
    {
        ballPhysics->hasGravity = 1;
        physicsAddVelocity(ballPhysics, cam->lookAt[0] * controller->force, cam->lookAt[1] * controller->force, cam->lookAt[2] * controller->force);
        controller->pickUpCheck = 0;
        printf("THROW EXECUTED!\n");
    }
}
