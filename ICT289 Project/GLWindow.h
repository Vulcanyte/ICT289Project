
/** @Overview: Window functions using the OpenGl graphics API.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 8th April 2016

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVWindow

    #define FLAG_JVWindow

    #include "CustomDataTypes.h"

    // --------------------   Custom Datatypes.   --------------------
    /// Data container for all parameters related to an OpenGL window.
    typedef struct
    {

        char* windowName;   // Name of the window.
        point2 pos;         // Onscreen position of the window.
        point2 dimensions;  // Onscreen size of the window.
        short renderGUI;    // 1 (TRUE) if the window is currently set to render the GUI, else 0 (FALSE).

    }GL_Window;




    // --------------------   Initialisation functions.   --------------------
    /** @brief: Create a new OpenGL window. All data related to the window should be stored within the GL_Window* parameter.

        @param: newWindow (GL_Window*) - Data container for the new window being created.
        @param: name (char*) - Name of the window.
        @param: posX (int) - The screen X position for the new window.
        @param: posY (int) - The screen Y position for the new window.
        @param: sizeX (int) - The X dimension of the new window (screen co-ordinates).
        @param: sizeY (int) - The Y dimension of the new window (screen co-ordinates).

        @return: NONE.
    **/
    void GLWindowCreate(GL_Window* newWindow, char* name, int posX, int posY, int sizeX, int sizeY);

#endif
