
/** @Overview: Functionality for a 2D textured plane using the OpenGl graphics API.

    @Author:
    @StudentNumber:
    @Date:

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_TexturePlane

    #define FLAG_TexturePlane

    #include "CustomDataTypes.h"

    typedef struct
    {

        point3 pos;
        point2 bounds;
        point3 rot;

        unsigned int textureID;

    } TexturedPlane;

    void texPlaneInit(TexturedPlane* plane, float posX, float posY, float posZ, float width, float height, char* texFile);

    void texPlaneSetPosition(TexturedPlane* plane, float posX, float posY, float posZ);

    void texPlaneSetRotation(TexturedPlane* plane, float rotX, float rotY, float rotZ);

    void texPlaneDraw(TexturedPlane* plane);

#endif // FLAG_TexturePlane
