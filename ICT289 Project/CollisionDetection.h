
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
        point3 offset;          // The XYZ world co-ordinate offset from a linked mode / etc.
        float radius;           // The radius of the sphere collider.
        short isColliding;      // 1 (TRUE) if the collider is currently colliding with another collider, else 0 (FALSE).

    }collider_Sphere;

    /// Axis-Alligned Bounding Box (AABB) collider type.
    typedef struct
    {
        point3 position;        // The XYZ world co-ordinates of the AABB collider.
        point3 offset;          // The XYZ world co-ordinate offset from a linked mode / etc.
        float sizeX;            // The X dimension of the AABB collider.
        float sizeY;            // The Y dimension of the AABB collider.
        float sizeZ;            // The Z dimension of the AABB collider.
        short isColliding;      // 1 (TRUE) if the collider is currently colliding with another collider, else 0 (FALSE).

    }collider_AABB;

    // --------------------   Initialisation functions.   --------------------

    /** @brief: Initialise a Sphere Collider.

        @param: sph (collider_Sphere* ) - The sphere collider to be initialised.
        @param: posX (float) - The X world co-ordinate that the sphere collider will be placed at.
        @param: posY (float) - The Y world co-ordinate that the sphere collider will be placed at.
        @param: posZ (float) - The Z world co-ordinate that the sphere collider will be placed at.
        @param: radius (float) - The radius of the collision sphere.

        @return: NONE.
    **/
    void collisionInit_S(collider_Sphere* sph, float posX, float posY, float posZ, float r);

    /** @brief: Initialise an AABB Collider.

        @param: box (collider_AABB* ) - The AABB collider to be initialised.
        @param: posX (float) - The X world co-ordinate that the AABB collider will be placed at.
        @param: posY (float) - The Y world co-ordinate that the AABB collider will be placed at.
        @param: posZ (float) - The Z world co-ordinate that the AABB collider will be placed at.
        @param: sizeX (float) - The AABB's X dimension.
        @param: sizeY (float) - The AABB's Y dimension.
        @param: sizeZ (float) - The AABB's Z dimension.

        @return: NONE.
    **/
    void collisionInit_B(collider_AABB* box, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ);

    /** @brief: Offset a Sphere Collider relative to a linked GameObject.

        @param: box (collider_Sphere* ) - The Sphere collider to be initialised.
        @param: posX (float) - The X world co-ordinate offset that the Sphere collider will be placed at relative to a linked GameObject.
        @param: posY (float) - The Y world co-ordinate offset that the Sphere collider will be placed at relative to a linked GameObject.
        @param: posZ (float) - The Z world co-ordinate offset that the Sphere collider will be placed at relative to a linked GameObject.

        @return: NONE.
    **/
    void collisionOffset_S(collider_Sphere* sph, float offsetX, float offsetY, float offsetZ);

    /** @brief: Offset an AABB Collider relative to a linked GameObject.

        @param: box (collider_AABB* ) - The AABB collider to be initialised.
        @param: posX (float) - The X world co-ordinate offset that the AABB collider will be placed at relative to a linked GameObject.
        @param: posY (float) - The Y world co-ordinate offset that the AABB collider will be placed at relative to a linked GameObject.
        @param: posZ (float) - The Z world co-ordinate offset that the AABB collider will be placed at relative to a linked GameObject.

        @return: NONE.
    **/
    void collisionOffset_B(collider_AABB* box, float offsetX, float offsetY, float offsetZ);

    //------------------------   Collision Detection functions.   --------------------------

    /** @brief: Check for collisions between two sphere colliders.

        @param: sph1 (collider_Sphere* ) - The first sphere to be tested.
        @param: sph2 (collider_Sphere* ) - The second sphere to be tested.

        @return: 1 (TRUE) if the two spheres are currently colliding, else 0 (FALSE).
    **/
    short collisionCollideSS(collider_Sphere* sph1, collider_Sphere* sph2);

    /** @brief: Check for collisions between an AABB collider and a sphere collider.

        @param: sph (collider_Sphere* ) - The sphere to be tested.
        @param: box (collider_AABB* ) - The box to be tested.

        NOTE: Current implementation only tests sphere <-> box FACE collisions.

        @return: 1 (TRUE) if the two colliders are currently colliding, else 0 (FALSE).
    **/
    short collisionCollideSB(collider_Sphere* sph, collider_AABB* box);

    /** @brief: Check for collisions between two AABB colliders.

        @param: box1 (collider_AABB* ) - The first box to be tested.
        @param: box2 (collider_AABB* ) - The second box to be tested.

        @return: 1 (TRUE) if the two boxes are currently colliding, else 0 (FALSE).
    **/
    short collisionCollideBB(collider_AABB* box1, collider_AABB* box2);

    /** @brief: Find the collision normals for two colliding spheres.

        @param: coll_1 (collider_Sphere* ) - The first collider to be tested.
        @param: coll_2 (collider_Sphere* ) - The second collider to be tested.
        @param: norm_sph1X (float* ) - The X value of the collision normal of the FIRST collider (coll_1 param).
        @param: norm_sph1Y (float* ) - The Y value of the collision normal of the FIRST collider (coll_1 param).
        @param: norm_sph1Z (float* ) - The Z value of the collision normal of the FIRST collider (coll_1 param).
        @param: norm_sph2X (float* ) - The X value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_sph2Y (float* ) - The Y value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_sph2Z (float* ) - The Z value of the collision normal of the SECOND collider (coll_2 param).

        @return: (float) - The penetration depth of the collision.
    **/
    float collisionFindNormalSS(collider_Sphere* coll_1, collider_Sphere* coll_2, float* norm_sph1X, float* norm_sph1Y, float* norm_sph1Z, float* norm_sph2X, float* norm_sph2Y, float* norm_sph2Z);

    /** @brief: Find the collision normals for a sphere colliding with a box.

        @param: coll_1 (collider_Sphere* ) - The first collider to be tested.
        @param: coll_2 (collider_AABB* ) - The second collider to be tested.
        @param: norm_sphX (float* ) - The X value of the collision normal of the FIRST collider (coll_1 param).
        @param: norm_sphY (float* ) - The Y value of the collision normal of the FIRST collider (coll_1 param).
        @param: norm_sphZ (float* ) - The Z value of the collision normal of the FIRST collider (coll_1 param).
        @param: norm_boxX (float* ) - The X value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_boxY (float* ) - The Y value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_boxZ (float* ) - The Z value of the collision normal of the SECOND collider (coll_2 param).

        @return: (float) - The penetration depth of the collision.
    **/
    float collisionFindNormalSB(collider_Sphere* coll_1, collider_AABB* coll_2, float* norm_sphX, float* norm_sphY, float* norm_sphZ, float* norm_boxX, float* norm_boxY, float* norm_boxZ);

    /** @brief: Find the collision normals for two colliding boxes.

        @param: coll_1 (collider_AABB* ) - The first collider to be tested.
        @param: coll_2 (collider_AABB* ) - The second collider to be tested.
        @param: norm_box1X (float* ) - The X value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_box1Y (float* ) - The Y value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_box1Z (float* ) - The Z value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_box2X (float* ) - The X value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_box2Y (float* ) - The Y value of the collision normal of the SECOND collider (coll_2 param).
        @param: norm_box2Z (float* ) - The Z value of the collision normal of the SECOND collider (coll_2 param).

        @return: (float) - The penetration depth of the collision.
    **/
    float collisionFindNormalBB(collider_AABB* coll_1, collider_AABB* coll_2, float* norm_box1X, float* norm_box1Y, float* norm_box1Z, float* norm_box2X, float* norm_box2Y, float* norm_box2Z);

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

        @param: sph (collider_Sphere* ) - The sphere collider to be drawn.

        @return: NONE.
    **/
    void collisionDebug_DrawS(collider_Sphere* sph);

    /** @brief: Draw an AABB. Note: Only draws if the debug mode flag is set to TRUE.

        @param: box (collider_AABB* ) - The AABB to be drawn.

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
