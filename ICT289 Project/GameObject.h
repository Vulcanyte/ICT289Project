
/** @Overview: GameObject methods for simplifying game world updating.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 18th May 2016

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVGameObject

    #define FLAG_JVGameObject

    // Add headers for usable components here...
    #include "CollisionDetection.h"

    /// Enumeration type for specifying which kind of component is attached to a game object.
    typedef enum {MODEL = 0, COLL_SPHERE = 1, COLL_BOX = 2, RIGIDBODY = 4} componentType;

    /// Entry for a single game object component.
    typedef struct
    {
        void* component;
        componentType type;

    }GameObjectComponent;

    /// Data container for an object in the game world.
    typedef struct
    {
        point3 position;

        // (Currently rotation and scale are not necessary.)
        //point3 rotation;
        //point3 scale;

        GameObjectComponent* components;
        int numComponents;

    }GameObject;

    /** @brief: Get the specified instance of a certain component type, from a specified game object.

        @param: object (GameObject* ) - The relevant GameObject.
        @param: type (componentType) - The enumeration that corresponds to the desired struct type.
        @param: index (int) - 0 to select first instance of component type, else use a positive number for other indexes.

        @return: The first instance of the desired struct type found in the game object, or NULL if no match was found.
    **/
    void* gameObjectGetComponent(GameObject* object, componentType type, int index);

    /** @brief: Get the number of occurences of a specified component type within a specified GameObject.

        @param: object (GameObject* ) - The relevant GameObject.
        @param: type (componentType) - The enumeration that corresponds to the desired struct type.

        @return: The number of matches to the specified type that exist in the specified GameObject.
    **/
    int gameObjectGetNumComponents(GameObject* object, componentType type);

    /** @brief: Initialise a game object.

        @param: object (GameObject* ) - The relevant GameObject.
        @param: posX (float) - The X world co-ordinate of the game object.
        @param: posY (float) - The Y world co-ordinate of the game object.
        @param: posZ (float) - The Z world co-ordinate of the game object.
        @param: components (GameObjectComponent [] ) - A list of the components attached to this game object.
        @param: numComp (int) - The number of components that have been attached to this game object.

        @return: NONE.

        @pre: The 'object' param address must point to a declared GameObject struct.
        @post: The GameObject struct can now be used elsewhere in the program.
    **/
    void gameObjectInit(GameObject* object, float posX, float posY, float posZ, GameObjectComponent components[], int numComp);

    /** @brief: Update all components in a specified game object.

        @param: object (GameObject* ) - The relevant GameObject.

        @return: NONE.

        @post: All of the components within the specified game object have now had their relevant data updated.
    **/
    void gameObjectUpdate(GameObject* object);

    /** @brief: Update a specific component within a specified game object.

        @param: object (GameObject* ) - The relevant GameObject.
        @param: component (void* ) - The address specified component to be updated.
        @param: type (componentType) - The enumeration type specification of the component.

        @return: NONE.
    **/
    void gameObjectUpdateComponent(GameObject* object, void* component, componentType type);

    /** @brief: Render all models attached to a specified game object.

        @param: object (GameObject* ) - The relevant GameObject.

        @return: NONE.
    **/
    void gameObjectRender(GameObject* object);

    /** @brief: Set the world position co-ordinates of a specified game object.

        @param: object (GameObject* ) - The relevant GameObject.
        @param: posX (float) - The X world co-ordinate of the game object.
        @param: posY (float) - The Y world co-ordinate of the game object.
        @param: posZ (float) - The Z world co-ordinate of the game object.

        @return: NONE.
    **/
    void gameObjectSetPos(GameObject* object, float posX, float posY, float posZ);

#endif
