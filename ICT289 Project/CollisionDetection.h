
/** @Overview: Collision Detection functionality.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 5th May 2016

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVCollision

    #define FLAG_JVCollision

    #include "CustomDataTypes.h"
    #include <GL/freeglut.h>

    // --------------------   Custom Datatypes.   --------------------

    /// Sphere collider type.
    typedef struct
    {
        point3 position;        // The XYZ world co-ordinates of the sphere collider.
        float radius;           // The radius of the sphere collider.
        short isColliding;      // 1 (TRUE) if the collider is currently colliding with another collider, else 0 (FALSE).

    }collider_Sphere;

    /// Axis-Alligned Bounding Box (AABB) collider type.
    typedef struct
    {
        point3 position;        // The XYZ world co-ordinates of the AABB collider.
        float sizeX;            // The X dimension of the AABB collider.
        float sizeY;            // The Y dimension of the AABB collider.
        float sizeZ;            // The Z dimension of the AABB collider.
        short isColliding;      // 1 (TRUE) if the collider is currently colliding with another collider, else 0 (FALSE).

    }collider_AABB;

    // --------------------   Initialisation functions.   --------------------

    /** @brief: Initialise a Sphere Collider.

        @param: sph (collider_Sphere*) - The sphere collider to be initialised.
        @param: posX (float) - The X world co-ordinate that the sphere collider will be placed at.
        @param: posY (float) - The Y world co-ordinate that the sphere collider will be placed at.
        @param: posZ (float) - The Z world co-ordinate that the sphere collider will be placed at.
        @param: radius (float) - The radius of the collision sphere.

        @return: NONE.
    **/
    void collisionInit_S(collider_Sphere* sph, float posX, float posY, float posZ, float r);

    /** @brief: Initialise an AABB Collider.

        @param: box (collider_AABB*) - The AABB collider to be initialised.
        @param: posX (float) - The X world co-ordinate that the AABB collider will be placed at.
        @param: posY (float) - The Y world co-ordinate that the AABB collider will be placed at.
        @param: posZ (float) - The Z world co-ordinate that the AABB collider will be placed at.
        @param: sizeX (float) - The AABB's X dimension.
        @param: sizeY (float) - The AABB's Y dimension.
        @param: sizeZ (float) - The AABB's Z dimension.

        @return: NONE.
    **/
    void collisionInit_B(collider_AABB* box, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ);

    //------------------------   Collision Detection functions.   --------------------------

    /** @brief: Check for collisions between two sphere colliders.

        @param: sph1 (collider_Sphere*) - The first sphere to be tested.
        @param: sph2 (collider_Sphere*) - The second sphere to be tested.

        @return: 1 (TRUE) if the two spheres are currently colliding, else 0 (FALSE).
    **/
    short collisionCollideSS(collider_Sphere* sph1, collider_Sphere* sph2);

    /** @brief: Check for collisions between an AABB collider and a sphere collider.

        @param: sph (collider_Sphere*) - The sphere to be tested.
        @param: box (collider_AABB*) - The box to be tested.

        @return: 1 (TRUE) if the two colliders are currently colliding, else 0 (FALSE).
    **/
    short collisionCollideSB(collider_Sphere* sph, collider_AABB* box);

    /** @brief: Check for collisions between two AABB colliders.

        @param: box1 (collider_AABB*) - The first box to be tested.
        @param: box2 (collider_AABB*) - The second box to be tested.

        @return: 1 (TRUE) if the two boxes are currently colliding, else 0 (FALSE).
    **/
    short collisionCollideBB(collider_AABB* box1, collider_AABB* box2);

    //------------------------   Debug functions.   --------------------------

    /** @brief: Toggle Debug mode for collision detection on / off.

        @param: debugMode (float) - The status of the debug mode flag. 1 to activate, or 0 to deactivate.

        @return: NONE.
    **/
    void collisionDebug_Toggle(short debugMode);

    /** @brief: Get the current status of the debug mode flag.

        @param: NONE.

        @return: 1 (TRUE) if debug mode is currently active, else 0 (FALSE).
    **/
    short collisionDebug_FlagStatus();

    /** @brief: Draw a collision sphere. Note: Only draws if the debug mode flag is set to TRUE.

        @param: sph (collider_Sphere*) - The sphere collider to be drawn.

        @return: NONE.
    **/
    void collisionDebug_DrawS(collider_Sphere* sph);

    /** @brief: Draw an AABB. Note: Only draws if the debug mode flag is set to TRUE.

        @param: box (collider_AABB*) - The AABB to be drawn.

        @return: NONE.
    **/
    void collisionDebug_DrawB(collider_AABB* box);

    /** @brief: Specify the color that colliders will turn when they are colliding with another collider(s). Note: Only relevant in debug mode.

        @param: r (float) - The R color component.
        @param: g (float) - The G color component.
        @param: b (float) - The B color component.

        @return: NONE.
    **/
    void collisionDebug_PosColor(float r, float g, float b);

    /** @brief: Specify the color that colliders will turn when they are NOT colliding with any other collider(s). Note: Only relevant in debug mode.

        @param: r (float) - The R color component.
        @param: g (float) - The G color component.
        @param: b (float) - The B color component.

        @return: NONE.
    **/
    void collisionDebug_NegColor(float r, float g, float b);

#endif
