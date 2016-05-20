
#include "GameObject.h"

void* gameObjectGetComponent(GameObject* object, componentType type, int index)
{
    int i = 0;          // For incrementing through the entire contents of a game object's components.
    int typeIndex = 0;  // For counting the number of instances of the specified component type.

    for(i = 0; i < object->numComponents; i++)
    {
        // Iterate through the game object and return the first positive match for the specified search type.
        if(object->components[i].type == type)
        {
            // If the match is the same index as was specified, return this index, otherwise increment the counter and continue.
            if(typeIndex == index)
                return object->components[i].component;
            else
                typeIndex++;
        }
    }

    // Return NULL if there are no positive matches to the specified search type.
    return NULL;
}

int gameObjectGetNumComponents(GameObject* object, componentType type)
{
    int i = 0;          // For incrementing through the entire contents of a game object's components.
    int typeIndex = 0;  // For counting the number of instances of the specified component type.

    for(i = 0; i < object->numComponents; i++)
    {
        // Iterate through the game object and return the first positive match for the specified search type.
        if(object->components[i].type == type)
                typeIndex++;
    }

    return typeIndex;
}

void gameObjectInit(GameObject* object, float posX, float posY, float posZ, GameObjectComponent components[], int numComp)
{
    object->position[0] = posX;
    object->position[1] = posY;
    object->position[2] = posZ;

    object->components = components;

    object->numComponents = numComp;
}

void gameObjectUpdate(GameObject* object)
{
    // Iterate through the attached componentns and update relevant information.
    int i = 0;
    for(i = 0; i < object->numComponents; i++)
    {
        gameObjectUpdateComponent(object, object->components[i].component, object->components[i].type);
    }
}

void gameObjectUpdateComponent(GameObject* object, void* component, componentType type)
{
    switch(type)
    {
        case MODEL:

            break;

        case COLL_SPHERE:
            ((collider_Sphere*)component)->position[0] = object->position[0] + ((collider_Sphere*)component)->offset[0];
            ((collider_Sphere*)component)->position[1] = object->position[1] + ((collider_Sphere*)component)->offset[1];
            ((collider_Sphere*)component)->position[2] = object->position[2] + ((collider_Sphere*)component)->offset[2];
            break;

        case COLL_BOX:
            ((collider_AABB*)component)->position[0] = object->position[0] + ((collider_AABB*)component)->offset[0];
            ((collider_AABB*)component)->position[1] = object->position[1] + ((collider_AABB*)component)->offset[1];
            ((collider_AABB*)component)->position[2] = object->position[2] + ((collider_AABB*)component)->offset[2];
            break;

        case RIGIDBODY:

            break;

        default:
            // Do nothing...
            break;
    }
}

void gameObjectRender(GameObject* object)
{
    int i = 0;
    for(i = 0; i < object->numComponents; i++)
    {
        switch(object->components[i].type)
        {
            case MODEL:
                // Render any models here. Ideally there should be a modelRender function that can be called for each model component.
                break;

            case COLL_SPHERE:
                collisionDebug_DrawS(((collider_Sphere*)object->components[i].component));
                break;

            case COLL_BOX:
                collisionDebug_DrawB(((collider_AABB*)object->components[i].component));
                break;

            default:
                // Do nothing...
                break;
        }
    }
}

void gameObjectSetPos(GameObject* object, float posX, float posY, float posZ)
{
    object->position[0] = posX;
    object->position[1] = posY;
    object->position[2] = posZ;
}
