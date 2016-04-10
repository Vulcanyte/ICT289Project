
/** @Overview: Basic menu functionality using the OpenGl graphics API.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 8th April 2016

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVMenu

    #define FLAG_JVMenu

    #include "PopupMenuFunctions.h"

    // --------------------   Custom Datatypes.   --------------------
    /// Declaration of the foramt that a menu option selection function must have.
    typedef void (*PopupMenuOptionFunc)(int);

    /// Container for a single entry in a menu.
    typedef struct
    {

        char* label;    // Label for a single menu option.
        int value;      // Value of the single menu option.

    }GL_PopupMenuEntry;

    /// Container for all relevant data to a single menu level.
    typedef struct
    {

        char* menuName;         // Name of the menu.
        int menuID;             // ID tag for the menu.
        int accessButton;       // Button that opens the menu when pressed.

        GL_PopupMenuEntry* options;  // List of options that will appear in this menu level.

    }GL_PopupMenu;

    // --------------------   Initialisation functions.   --------------------
    /** @brief: Create a new OpenGL popup menu.

        @param: newMenu (GL_PopupMenu* ) - Reference to the popup menu being created.
        @param: menuName (char* ) - Name of the menu.
        @param: menuFunc (MenuOptionFunc) - Function pointer to a properly formatted function for handling user input on this menu level.
        @param: button (int) - The button that will activate the menu when it is pressed. Values less than zero will not attach the menu to a button.
        @param: options (GL_PopupMenuEntry [] ) - List of all ooptions that will be displayed at this menu level.
        @param: arraySize (int) - The number of elements in the options array.

        @return: NONE.
    **/
    void GLPopupMenuCreate(GL_PopupMenu* newMenu, char* menuName, PopupMenuOptionFunc menuFunc, int button, GL_PopupMenuEntry options[], int arraySize);

    /** @brief: Make a popup menu a member of another popup menu's hierarchy.

        @param: parent (GL_Menu* ) - The parent of the sub menu.
        @param: child (GL_Menu* ) - The menu being placed within the parent menu's hierarchy.

        @return: NONE.
    **/
    void GLPopupMenuCreateSub(GL_PopupMenu* parent, GL_PopupMenu* child);

    /** @brief: Change which popup menu is being affected by future operations.

        @param: menu (GL_PopupMenu* ) - The menu being affected by this function.

        @return: NONE.
    **/
    void GLPopupMenuFocus(GL_PopupMenu* menu);

    /** @brief: Detach a menu from its activation button.

        @param: menu (GL_PopupMenu* ) - The menu being affected by this function.

        @return: NONE.
    **/
    void GLPopupMenuDetach(GL_PopupMenu* menu);

#endif
