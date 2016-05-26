#include "RigidBody.h"

float physicsGravity = 9.8f;        // The acceleration force of gravity.
float physicsAirDeceleration = 0.1f;     // Decay rate of horizontal movement. Represents air resistance.
float terminalVelocity = -144;      // Maximum downwards velocity that an object can move with only the force of gravity.

void physicsInit(RigidBody* body, float mass, float bounceDecay, short gravity, short active, short staticObject)
{
    body->velocity[0] = 0;
    body->velocity[1] = 0;
    body->velocity[2] = 0;

    body->position[0] = 0;
    body->position[1] = 0;
    body->position[2] = 0;

    body->mass = mass;
    body->bounceDecay = bounceDecay;
    body->hasGravity = gravity;
    body->active = active;
    body->staticObject = staticObject;
}

void physicsSetPosition(RigidBody* body, float posX, float posY, float posZ)
{
    body->position[0] = posX;
    body->position[1] = posY;
    body->position[2] = posZ;
}

void physicsAddForce(RigidBody* body, float forceX, float forceY, float forceZ)
{
    body->velocity[0] += forceX;
    body->velocity[1] += forceY;
    body->velocity[2] += forceZ;
}

void physicsUpdate(RigidBody* body, float deltaTime, float gameSpeed)
{
    if(body->active)
    {
        // Y axis always has gravity.
        if(body->velocity[1] - (physicsGravity * deltaTime) > terminalVelocity && body->hasGravity)
            body->velocity[1] -= physicsGravity * deltaTime;

        // X axis.
        if(body->velocity[0] != 0 && physicsAirDeceleration != 0)
        {
            if(abs(body->velocity[0] - (physicsAirDeceleration * deltaTime)) > (physicsAirDeceleration * deltaTime))
            {
                if(body->velocity[0] > 0)
                    body->velocity[0] -= physicsAirDeceleration * deltaTime;
                else
                    body->velocity[0] += physicsAirDeceleration * deltaTime;
            }
            else
                body->velocity[0] = 0;
        }

        // Z axis.
        if(body->velocity[2] != 0 && physicsAirDeceleration != 0)
        {
            if(abs(body->velocity[2] - (physicsAirDeceleration * deltaTime)) > (physicsAirDeceleration * deltaTime))
            {
                if(body->velocity[2] > 0)
                    body->velocity[2] -= physicsAirDeceleration * deltaTime;
                else
                    body->velocity[2] += physicsAirDeceleration * deltaTime;
            }
            else
                body->velocity[2] = 0;
        }

        body->position[0] += body->velocity[0] * deltaTime * gameSpeed;
        body->position[1] += body->velocity[1] * deltaTime * gameSpeed;
        body->position[2] += body->velocity[2] * deltaTime * gameSpeed;
    }
}

void physicsSetAirDeceleration(float newValue)
{
    physicsAirDeceleration = (newValue < 0) ? 0 : newValue;
}

void physicsSetGravity(float newValue)
{
    physicsGravity = (newValue < 0) ? 0 : newValue;
}
