
/** @Overview: Functionality for a 2D textured plane using the OpenGl graphics API.

    @Author: Matthew MacLennan
    @StudentNumber: 32225946
    @Date: 6th June 2016

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

    /** @brief: Initialise plane object.
 
    @param: plane (TexturedPlane* ) - The relevant TexturedPlane object.
    @param: posX (float) - The x position of the texture.
    @param: posY (float) - The y position of the texture.
    @param: posZ (float) - The z position of the texture.
    @param: width (float) - The width of the loaded image.
    @param: height (float) - The height of the loaded image.
    @param: texFile (char*) - The name of the loaded image.
 
    @return: NONE.
    **/
    void texPlaneInit(TexturedPlane* plane, float posX, float posY, float posZ, float width, float height, char* texFile);

    /** @brief: Set x, y, z position for plane.
 
    @param: plane (TexturedPlane*) - The relevant TexturedPlane object.
    @param: posX (float) - The x coord of the texture plane.
    @param: posY (float) - The y coord of the texture plane.
    @param: posZ (float) - the z coord of the texture plane.
    @param: width (float) - The width of the image loaded.
    @param: height (float) - The height of the image loaded.
    @param: texFile (char*) - The image file loaded.
 
    @return: NONE.
    **/
    void texPlaneSetPosition(TexturedPlane* plane, float posX, float posY, float posZ);

    /** @brief: Sets the x, y, z rotation for the plane.
     
    @param: plane (TexturedPlane*) - The relevant TexturedPlane object.
    @param: rotX (float) - The rotation coord for x.
    @param: rotY (float) - The rotation coord for y.
    @param: rotZ (float) - The rotation coord for z.
 
    @return: NONE.
    **/
    void texPlaneSetRotation(TexturedPlane* plane, float rotX, float rotY, float rotZ);

    /** @brief: Draws the texture on the model.
 
    @param: plane (TexturedPlane*) - The relevant TexturedPlane object.
 
    @return: NONE.
    **/
    void texPlaneDraw(TexturedPlane* plane);

#endif // FLAG_TexturePlane
