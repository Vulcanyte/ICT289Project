//
//  Interaction.c
//  Interaction
//
//  Created by Matthew MacLennan on 25/05/2016.
//  Copyright © 2016 Matthew MacLennan. All rights reserved.
//

#include "Interaction.h"

short checkRadius(collider_Sphere* charCSphere, collider_AABB* goalCBox)
{
    return collisionCollideSB(charCSphere, goalCBox);
}

// needs to read in ball object from room_and_ball and its position
void moveBall()
{
    // take position of ball to edge of detection circle
    // move ball around to face camera
    // lock it to frount of camera (moves with camera)
}

// will play around with this to get it working
void bindKeysToControls(interactionControls* controller, collider_Sphere* playerSphere, interactionControlKeys* controls)
{
    controller->playerSphere = charCSphere;
    controller->interactionControls = controls;
}

// to change the binds
void controllerExitInteractionKeyControls(interactionControls* controller, char pKey, char tKey, char eKey)
{
    if(pKey != '\n')
        controller->keybinds->pickUpKey = pKey;
    
    if(pKey != '\n')
        controller->keybinds->throwKey = tKey;
    
    if(pKey != '\n')
        controller->keybinds->ExitKey = eKey;
}
