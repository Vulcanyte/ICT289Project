//
//  Interaction.h
//  Interaction
//
//  Created by Matthew MacLennan on 25/05/2016.
//  Copyright © 2016 Matthew MacLennan. All rights reserved.
//

#ifndef Interaction_h
#define Interaction_h

#include "CollisionDetection.h"
typedef struct
{
    
    char pickUpKey;
    char throwKey;
    char exitKey;
    
}interactionControlKeys;

typedef struct
{
    
    interactionControlKeys keybinds; // Binds for the interaction keys
    float force; // force of the throw
    short pickUpCheck; // 0 or 1 check if the ball collider is in range of the pick up collider
    
    
}interactionControls;

short checkRadius(collider_Sphere* charCSphere, collider_AABB* goalCBox);
/** @brief: Check to see if the sphere and goal box are colliding.
 
 @param: charCSphere (collider_Sphere* ) - The characters collider sphere.
 @param: goalCBox (collider_AABB* ) - The goal collider box.
 
 @return: 1 (TRUE) if the two colliders are currently colliding, else 0 (FALSE).
 **/

void moveBall();

void bindKeysToControls(interactionControls* controller, collider_Sphere* playerSphere, interactionControlKeys* controls);

void controllerExitInteractionKeyControls(interactionControls* controller, char pKey, char tKey, char eKey);

#endif /* Interaction_h */
