
/** @Overview: GUI functions using the OpenGl graphics API.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 8th April 2016

    @Version: 1.0
**/

// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVGUI

    #define FLAG_JVGUI

    #include <GL/freeglut.h>

    #include "CustomDataTypes.h"
    #include "GLWindow.h"

    /// Different types of external linked parameters require different labels to assist formatting. Below are the supported data types.
    typedef enum {CHAR_param = 1, STR_param = 2, INT_param = 3, FLOAT_param = 4, POINT2_param = 5, POINT3_param = 6, TIME_param = 7} LinkedParamType;

    /// Different types of GUI elements require different labels.
    typedef enum {GUI_TEXT = 1, GUI_LINE = 2} GUIelementType;

    /// Data container for a single GUI text element.
    typedef struct
    {

        char* text;                 // Default text displayed when rendered.
        void* font;                 // Font type that the text is rendered in.
        point2 position;            // Window co-ordinates for the text element's position.
        void* linkedParam;          // External linked parameter for optional display.
        LinkedParamType paramType;  // Type description for any external linked parameter.

    }GUItext;

    /// Data container for a single GUI line element.
    typedef struct
    {

        point2 startPoint;  // Start point for the line.
        point2 endPoint;    // End point for the line.
        float thickness;    // Thickness of the line.
        point3 color;       // Color of the line.

    }GUIline;

    /// Data container for a single entry in a GUIframe's contents.
    typedef struct
    {

        void* GUIelement;       // GUI element reference.
        GUIelementType type;    // The specific type of element this GUI element is.

    }GUIframeEntry;

    /// Data container for an entire frame on the GUI.
    typedef struct
    {

        int frameID;                    // Identifier for this GUI frame.
        GUIframeEntry* frameElements;   // List of the elements contained within this frame.
        int numElements;                // The number of elements contained within this frame.
        int renderON;                   // TRUE (1) if this frame is to be rendered, else FALSE (0).
        int2 offset;                    // Co-ordinate offset that will be applied to ALL GUI elements contained within this frame.

    }GUIframe;




    // --------------------   Initialisation functions.   --------------------
    /** @brief: Initialise a new GUI line element.

        @param: newLine (GUIline*) - Data container for the new GUI line element.
        @param: startX (float) - The window X co-ordinate for the line's beginning.
        @param: startY (float) - The window Y co-ordinate for the line's beginning.
        @param: endX (float) - The window X co-ordinate for the line's end.
        @param: endY (float) - The window Y co-ordinate for the line's end.
        @param: thickness (float) - The thickness of the line.
        @param: colorR (float) - The R conponent of the line's color.
        @param: colorG (float) - The G conponent of the line's color.
        @param: colorB (float) - The B conponent of the line's color.

        @return: NONE.
    **/
    void GUInewLine(GUIline* newLine, float startX, float startY, float endX, float endY, float thickness, float colorR, float colorG, float colorB);

    /** @brief: Initialise a new GUI text element.

        @param: newText (GUItext*) - Data container for the new GUItext element.
        @param: text (char*) - The text held within the new GUItext element.
        @param: posX (float) - The window X position for the new text element.
        @param: posY (float) - The window Y position for the new text element.
        @param: font (void*) - The font type for the text element.

        @pre: The GUItext pointer must point towards a declared object.
        @post: The GUItext object has now been initialised. It can be rendered / etc. immediately.

        @return: NONE.
    **/
    void GUInewText(GUItext* newText, char* text, float posX, float posY, void* font);

    /** @brief: Link an external parameter to be displayed by the text element.

        @param: textElement (GUItext*) - The text element being affected by this function.
        @param: param (void*) - The external parameter being linked to this text element.
        @param: paramType (LinkedParamType) - The type of paramter that is being linked to.

        @pre: The GUItext pointer must point towards a declared object.
        @post: The GUItext object will now display the external parameter when it is rendered.

        @return: NONE.
    **/
    void GUIlinkTextToParam(GUItext* textElement, void* param, LinkedParamType paramType);

    /** @brief: Initialise a new GUI frame.

        @param: newFrame (GUIframe*) - The new GUIframe being created.
        @param: identifierTag (int) - Value of the new frame's ID tag.
        @param: options (GUIframeEntry [] ) - A list of the elements contained within this frame.
        @param: numOptions (int) - The number of elements contained within 'options'.

        @pre: The GUIframe pointer must point towards a declared object.
        @post: NONE.

        @return: NONE.
    **/
    void GUInewFrame(GUIframe* newFrame, int identifierTag, GUIframeEntry options[], int numOptions);

    /** @brief: Move a frame to a point onscreen.

        @param: frame (GUIframe*) - The frame to be moved.
        @param: offset (point2) - The window co-ordinates that the frame will be moved to.

        @return: NONE.
    **/
    void GUIpositionFrame(GUIframe* frame, int offsetX, int offsetY);

    // --------------------   Rendering functions.   --------------------
    /** @brief: Enable 2D rendering on window. Required BEFORE beginning to call GUI rendering functions.

        @param: activeWindow (GL_Window*) - Data container for window data.

        @pre: activeWindow must point to a declared GL_Window struct.
        @post: 2D rendering can be executed. Note that 2D rendering MUST also be disabled with GUIdisable2DRendering( ).

        @return: NONE.
    **/
    void GUIenable2DRendering(GL_Window* activeWindow);

    /** @brief: Disable 2D rendering on window. Required AFTER finished calling GUI rendering functions.

        @param: activeWindow (GL_window*) - Data container for window data.

        @pre: activeWindow must point to a declared GL_Window struct.
        @post: Regular rendering can be executed.

        @return: NONE.
    **/
    void GUIdisable2DRendering(GL_Window* activeWindow);

    /** @brief: Render a GUItext element onscreen.

        @param: textElement (GUItext*) - The text element being rendered onscreen.

        @pre: textElement must point to an INITIALISED GUItext struct.
        @post: NONE.

        @return: NONE.
    **/
    void GUIrenderText(GUItext* textElement);

    /** @brief: Render a GUIline element onscreen.

        @param: lineElement (GUIline*) - The line element being rendered.

        @pre: lineElement must point to an INITIALISED GUIline struct.
        @post: NONE.

        @return: NONE.
    **/
    void GUIrenderLine(GUIline* lineElement);

    /** @brief: Render a frame.

        @param: frame (GUIframe*) - The frame to render.

        @pre: frame must point to an INITIALISED GUIframe struct.
        @post: NONE.

        @return: NONE.
    **/
    void GUIrenderFrame(GUIframe* frame);

    /** @brief: Allow a frame to be rendered.

        @param: frame (GUIframe*) - The frame that will be allowed to render.

        @return: NONE.
    **/
    void GUIenableFrame(GUIframe* frame);

    /** @brief: Hide a frame from view.

        @param: frame (GUIframe*) - The frame that will be hidden.

        @return: NONE.
    **/
    void GUIdisableFrame(GUIframe* frame);

    /** @brief: Set the color of all GUI text elements.

        @param: r (float) - The R channel of the GUI's color.
        @param: g (float) - The G channel of the GUI's color.
        @param: b (float) - The B channel of the GUI's color.

        @return: NONE.
    **/
    void GUIsetTextColor(float r, float g, float b);

#endif
