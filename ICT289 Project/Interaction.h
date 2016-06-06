
/** @Overview: Interaction functionality using the OpenGl graphics API.

 @Author: Matthew MacLennan
 @StudentNumber: 32225946
 @Date: 25th May 2016

 @Version: 1.1
**/

#ifndef Interaction_h
#define Interaction_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "CustomDataTypes.h"
#include "CollisionDetection.h"
#include "Camera.h"
#include "GameObject.h"
#include "RigidBody.h"

/// Container for basic interaction key controls.
typedef struct
{
    ControlKey pickUpKey;
    ControlKey throwKey;
    ControlKey exitKey;

} interactionControlKeys;



/// Container that binds a CS to a set of control keys, as well as other basic parameters required for interaction.
typedef struct
{

    collider_Sphere* player;    // The players CS for detecting the ball
    interactionControlKeys* keybinds;   // Binds for the interaction keys
    float force;                // force of the throw
    GLfloat playerX;            // The x, y, z coords of the player
    GLfloat playerY;
    GLfloat playerZ;
    short pickUpCheck;          // 0 or 1 check if the ball collider is in range of the pick up collider

}interactionController;

// --------------------   Initialisation functions.   --------------------
/** @brief: Bind the player CS to a set of keyboard key controls, using a interactionController.

 @param: controller (interactionController* ) - The interactionController that is being affected by this function.
 @param: player (collider_Sphere* ) - The CS that is being bound.
 @param: controls (interactionControlKeys* ) - The keys that are being bound to.

 @return: NONE.
 **/
void bindKeysToControls(interactionController* controller, collider_Sphere* charCS, interactionControlKeys* controls);

/** @brief: Rebind the key controls / edit movement speed of a interactionController. NOTE: Use '\n' to keep a currently bound key.

 @param: controller (interactionController* ) - The interactionController that is being affected by this function.
 @param: pKey (char) - The pick up control key.
 @param: tKey (char) - The throw control key.
 @param: eKey (char) - The exit control key.

 @return: NONE.
 **/
void changingInteractionKeyControls(interactionController* controller, char pKey, char tKey, char eKey);

/** @brief: Check to see if the playerCS and ballCS are colliding.

 @param: charCS (collider_Sphere* ) - The characters collider sphere.
 @param: ballCS (collider_Sphere* ) - The ball collider sphere.
 @param: controller (interactionController* ) - The controls.
 @param: ch (char) - The pressed key.

 @return: 1 (TRUE) if the CSs are colliding and the interaction key is being pressed, else 0 (FALSE).
 **/
short checkForPickUp(collider_Sphere* charCS, collider_Sphere* ballCS, interactionController* controller);

/** @brief: Moves a Collider_Sphere (ball) object to infront of the player's camera.

 @param: cam (Camera* ) - The player's camera.
 @param: ball (GameObject* ) - The gameobject representing the ball.

 @return: NONE.
**/
void moveBallToPlayer(interactionController* controller, Camera* cam, GameObject* ball, RigidBody* ballPhysics);

void throwBall(interactionController* controller, Camera* cam, RigidBody* ballPhysics);

void interactionCheckKeys(interactionController* controller, char ch);

#endif /* Interaction_h */
