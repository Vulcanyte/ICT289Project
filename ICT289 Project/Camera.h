
/** @Overview: Camera functionality using the OpenGl graphics API.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 7th April 2016

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVCamera

    #define FLAG_JVCamera

    #include "CustomDataTypes.h"

    // --------------------   Custom Datatypes.   --------------------
    /// Enumeration of different camera projection types.
    typedef enum {UNSPECIFIED = 0, ORTHO_2D = 1, ORTHOGONAL  = 2, PERSPECTIVE = 3, FRUSTUM = 4} Camera_Type;

    /// Container for parameters of a single instance of a camera.
    typedef struct{

        float leftPlane;            // Left clipping plane.
        float rightPlane;           // Right clipping plane.
        float topPlane;             // Top clipping plane.
        float bottomPlane;          // Bottom clipping plane.
        float nearPlane;            // Near clipping plane.
        float farPlane;             // Far clipping plane.
        float perspective_fov;      // Field of view (Perspective projection mode only).
        float perspective_aspect;   // Aspect ratio (Perspective projection mode only).
        float zoomLevel;            // The zoom level of the camera.

        point3 position;            // Camera position co-ordinates.
        point3 rotation;            // Camera rotation parameters.
        point3 lookAt;              // Camera lookAt co-ordinates.
        point3 rightVector;         // Camera's right vector.

        int2 mouseOrigin;           // The old co-ordinates for the screen centre point of the mouse. Used for mouse rotation control.
        point2 mouseOriginDelta;    // The new co-ordinates for the screen centre point of the mouse. Used for mouse rotation control.

        Camera_Type CamType;        // Camera projection type specification.

    } Camera;




    // --------------------   Initialisation functions.   --------------------
    /** @brief: Initialise a newly created camera.

        @param: newCamera (Camera* ) - The camera that is being affected by this function.
        @param: lPlane (float) - The left clipping plane of the affected camera.
        @param: rPlane (float) - The right clipping plane of the affected camera.
        @param: bPlane (float) - The bottom clipping plane of the affected camera.
        @param: tPlane (float) - The top clipping plane of the affected camera.
        @param: nPlane (float) - The near clipping plane of the affected camera.
        @param: fPlane (float) - The far clipping plane of the affected camera.
        @param: fov (float) - The field of view used by a perspective camera projection.
        @param: zoom (float) - The zoom level of the camera.
        @param: typeOfCamera (Camera_Type) - The type of projection that the affected camera will use.

        @return: NONE.
    **/
    void cameraInit(Camera* newCamera, float lPlane, float rPlane, float bPlane, float tPlane, float nPlane, float fPlane, float fov, float zoom, Camera_Type typeOfCamera);

    /** @brief: Set the type of a camera (change it to a different type). NOTE: This function automatically updates the OpenGl projection matrix.

        @param: newCamera (Camera* ) - The camera that is being affected by this function.
        @param: typeOfCamera (Camera_Type) - The new projection type that the camera will use.

        @return: NONE.
    **/
    void cameraSetType(Camera* cam, Camera_Type typeOfCamera);

    /** @brief: Orientate the camera by setting its position and lookAt co-ordinates. This is the float version.

        @param: cam (Camera* ) - The camera that is being affected by this function.
        @param: posX (float) - The X co-ordinate of the camera's position.
        @param: posY (float) - The Y co-ordinate of the camera's position.
        @param: posZ (float) - The Z co-ordinate of the camera's position.
        @param: lookX (float) - The X co-ordinate of the camera's lookAt.
        @param: lookY (float) - The Y co-ordinate of the camera's lookAt.
        @param: lookZ (float) - The Z co-ordinate of the camera's lookAt.

        @return: NONE.
    **/
    void cameraOrientate_f(Camera* cam, float posX, float posY, float posZ, float lookX, float lookY, float lookZ);

    /** @brief: Orientate the camera by setting its position and lookAt co-ordinates. This is the point3 version.

        @param: cam (Camera* ) - The camera that is being affected by this function.
        @param: pos (point3) - The co-ordinates for the camera's position.
        @param: look (point3) - The co-ordinates for the camera's lookAt.

        @return: NONE.
    **/
    void cameraOrientate_p(Camera* cam, point3 pos, point3 look);

    // --------------------   Rendering functions.   --------------------
    /** @brief: Update the OpenGl projection matrix using the parameters in a specified camera struct.

        @param: cam (Camera* ) - The camera that is being referenced.

        @return: NONE.
    **/
    void cameraProject(Camera* cam);

    /** @brief: Update the OpenGl lookAt using the parameters in a specified camera struct.

        @param: cam (Camera* ) - The camera that is being referenced.

        @return: NONE.
    **/
    void cameraUpdate(Camera* cam);

    /** @brief: Update the Camera's zoom level. NOTE: This function automatically updates the OpenGl projection matrix.

        @param: cam (Camera* ) - The camera that is being referenced.
        @param: zoomLevel (float) - The new zoom level of the camera. NOTE: values below 1.0 are ignored.

        @return: NONE.
    **/
    void cameraSetZoom(Camera* cam, float zoomLevel);

#endif
