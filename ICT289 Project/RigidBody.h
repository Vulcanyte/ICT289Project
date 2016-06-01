
/** @Overview: Basic simulated physics functionality.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 23rd May 2016

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVPhysics

    #include "CustomDataTypes.h"

    #define FLAG_JVPhysics

    typedef enum {PHYS_AIRDECEL = 0, PHYS_GRAVITY = 1, PHYS_SPEED = 2} PhysParam;

    typedef struct
    {
        point3 velocity;        // The direction that the rigidbody is currently moving.
        point3 position;        // The world co-ordinates of the RigidBody.
        float mass;             // The mass of the RigidBody.
        float bounceDecay;      // The efficiency in velocity retention if a collision occurs.
        short hasGravity;       // TRUE (1) to allow this rigidbody to be affected by gravity, else FALSE (0).
        short active;           // TRUE (1) to allow physics simulation updating, else FALSE (0).
        short staticObject;     // TRUE (1) to prevent this rigidBody from moving, else FALSE (0).

    }RigidBody;

    /** @brief: Initialise a rigidBody object.

        @param: body (RigidBody* ) - The relevant RigidBody object.
        @param: mass (float) - The mass of the rigidBody in kilograms.
        @param: bounceDecay (float) - The effeciency of energy retention in the event a collider attached to this rigidBody collides with another.
        @param: gravity (short) - TRUE (1) to allow this rigidbody to be affected by gravity, else FALSE (0).
        @param: active (short) - TRUE (1) to allow physics simulation updating, else FALSE (0).
        @param: staticObject (short) - TRUE (1) to prevent this rigidBody from moving, else FALSE (0).

        @pre: The referenced rigidBody must point to a declared rigidBody structure.

        @post: The rigidBody has now has all internal parameters set to defaults / user specifications. It can be used with other physics functions at from this point onwards.

        @return: NONE.
    **/
    void physicsInit(RigidBody* body, float mass, float bounceDecay, short gravity, short active, short staticObject);

    /** @brief: Initialise a rigidBody object.

        @param: body (RigidBody* ) - The relevant RigidBody object.
        @param: posX (float) - The X world co-ordinate to place the affected rigidBody object.
        @param: posY (float) - The Y world co-ordinate to place the affected rigidBody object.
        @param: posZ (float) - The Z world co-ordinate to place the affected rigidBody object.

        @return: NONE.
    **/
    void physicsSetPosition(RigidBody* body, float posX, float posY, float posZ);

    /** @brief: Apply a force to a rigidBody object.

        @param: body (RigidBody* ) - The relevant RigidBody object.
        @param: forceX (float) - A new force applied to the X world axis of the affected rigidBody.
        @param: forceY (float) - A new force applied to the Y world axis of the affected rigidBody.
        @param: forceZ (float) - A new force applied to the Z world axis of the affected rigidBody.

        @return: NONE.
    **/
    void physicsAddForce(RigidBody* body, float forceX, float forceY, float forceZ);

    /** @brief: Update a rigidBody object's physics.

        @param: body (RigidBody* ) - The relevant RigidBody object.
        @param: deltaTime (float) - The elapsed time since this function was called.

        @return: NONE.
    **/
    void physicsUpdate(RigidBody* body, float deltaTime);

    /** @brief: Set the deceleration due to air resistance in the simulation.

        @param: newValue (float) - The new air resistance.

        @return: NONE.
    **/
    void physicsSetAirDeceleration(float newValue);

    /** @brief: Set the aceleration due to gravity.

        @param: newValue (float) - The new acceleration of gravity.

        @return: NONE.
    **/
    void physicsSetGravity(float newValue);

    /** @brief: Set the speed of the physics simulation.

        @param: newValue (float) - The new simulation speed.

        @return: NONE.
    **/
    void physicsSetSimulationSpeed(float newValue);

    /** @brief: Get a modifiable parameter from within the physics system.

        @param: param (PhysParam) - Enumeration specifying the requested parameter.

        @return: (float) - The value of the modifiable parameter.
    **/
    float physicsGetParam(PhysParam param);


#endif
