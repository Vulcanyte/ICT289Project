
/** @Overview: Key control functionality for a camera, using the OpenGl graphics API.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 7th April 2016

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVController

    #define FLAG_JVController

    #include "Camera.h"

    // --------------------   Custom Datatypes.   --------------------
    /// Specification for how the camera controls will affect the bound camera.
    typedef enum {FIRST_PERSON = 0, THIRD_PERSON = 1, TOP_DOWN = 2} ControlType;

    /// Container for basic key controls for reference from within a camera controller struct.
    typedef struct
    {
        char forwardKey;    // The forward movement keyboard key.
        char backwardKey;   // The backward movement keyboard key.
        char upKey;         // The upward movement keyboard key.
        char downKey;       // The downward movement keyboard key.
        char strafe_L;      // The left strafe keyboard key.
        char strafe_R;      // The right strafe keyboard key.

        char mouseLock;     // The keyboard key that, when pressed, activates / deactivates camera rotation via mouse movement.

    } CameraControlKeys;

    /// Container that binds a camera to a set of control keys, as well as other basic parameters required for camera control.
    typedef struct
    {

        Camera* cam;                        // The camera that is bound to a set of key controls.
        CameraControlKeys* camControls;     // The keyboard keys of the bound camera.
        ControlType typeOfController;       // The type of controls that this controller will use.
        point2 mousePos;                    // The last known position of the mouse (in screen co-ordinates).
        short mouseLock;                    // Toggle specifying if the camera rotation via mouse movement is currently active.
        float mouseSensitivityX;            // X Rotation speed modifier.
        float mouseSensitivityY;            // Y Rotation speed modifier.
        float speedModifier;                // Movement speed modifier.
        short skipCheck;                    //

    } CameraController;




    // --------------------   Initialisation functions.   --------------------
    /** @brief: Bind a camera to a set of keyboard key controls, using a cameraController.

        @param: controller (CameraController* ) - The cameraController that is being affected by this function.
        @param: cam (Camera* ) - The camera that is being bound.
        @param: controls (CameraControlKeys* ) - The keys that are being bound to.
        @param: controllerType (ControlType) - The type of controls that the cameraController will use.

        @return: NONE.
    **/
    void controllerBindCameraToKeys(CameraController* controller, Camera* cam, CameraControlKeys* controls, ControlType controllerType);

    /** @brief: Rebind the key controls / edit movement speed of a cameraController. NOTE: Use '\n' to keep a currently bound key.

        @param: controller (CameraController* ) - The cameraController that is being affected by this function.
        @param: fKey (char) - The forward movement control key.
        @param: bKey (char) - The backward movement control key.
        @param: uKey (char) - The upward movement control key.
        @param: dKey (char) - The downward movement control key.
        @param: lKey (char) - The left strafe control key.
        @param: rKey (char) - The right strafe control key.
        @param: lockKey (char) - The mouse <-> cam lock toggle key.
        @param: speedMod (float) - The movement speed modifier of the cameraController. Values less than 0 will be treated like '\n'.

        @return: NONE.
    **/
    void controllerEditBasicKeyControls(CameraController* controller, char fKey, char bKey, char uKey, char dKey, char lKey, char rKey, char lockKey, float speedMod);

    /** @brief: Edit mouse controls of a cameraController.

        @param: controller (CameraController* ) - The cameraController that is being affected by this function.
        @param: sensitivityX (float) - The speed modifier for the camera's X rotation speed.
        @param: sensitivityY (float) - The speed modifier for the camera's Y rotation speed.

        @return: NONE.
    **/
    void controllerEditMouseControls(CameraController* controller, float sensitivityX, float sensitivityY);

    /** @brief: Toggle the mouse <-> cam lock.

        @param: controller (CameraController* ) - The cameraController that is being affected by this function.

        @return: NONE.
    **/
    void controllerToggleMouseLock(CameraController* controller);

    // --------------------   Continuously checked functions.   --------------------
    /** @brief: Check keyboard camera controls when keyboard input is detected.

        @param: controller (CameraController* ) - The cameraController that is being affected by this function.
        @param: ch (char) - The character value of the keyboard key that has been pressed.

        @return: NONE.
    **/
    void controllerCheckKeys(CameraController* controller, char ch);

    /** @brief: Check mouse movement controls when mouse movement is detected.

        @param: controller (CameraController* ) - The cameraController that is being affected by this function.
        @param: x (int) - The current screen X co-ordinate of the mouse.
        @param: y (int) - The current screen Y co-ordinate of the mouse.

        @return: NONE.
    **/
    void controllerCheckMouse(CameraController* controller, int x, int y);

    /** @brief: Check mouse button controls when mouse button input is detected.

        @param: controller (CameraController* ) - The cameraController that is being affected by this function.
        @param: button (int) - The mouse button that is being pressed.
        @param: state (int) - The press state (up or down) of the mouse button.
        @param: x (int) - The current screen X co-ordinate of the mouse.
        @param: y (int) - The current screen Y co-ordinate of the mouse.

        @return: NONE.
    **/
    void controllerCheckButtons(CameraController* controller, int button, int state, int x, int y);

#endif
