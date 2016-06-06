
/** @Overview: File IO functions for accessing data from external files.

    @Author: Joshua Voysey
    @StudentNumber: 32210066
    @Date: 8th April 2016

    @Version: 1.0
**/



// This flag is used so that the compiler only accesses this header file once during compilation.
// Excluding this guard will cause an error when multiple #includes for this header exist in a single program.
#ifndef FLAG_JVIO

    #define FLAG_JVIO

    #include <stdio.h>
    #include <unistd.h>
    #include <GL/freeglut.h>

    /** @brief: Read in the data from an external .RAW formatted file.

        @param: filePath (const char * ) - The path of the .RAW file relative to the current working directory.
        @param: data (unsigned char [ ] ) - The container for the color information held within the .RAW file.
        @param: width (int) - The width of the image.
        @param: height (int) - The height of the image.

        @return: NONE.

        NOTE: The code for this function was taken from an example project:

            'Rotating cube with texture mapping'
            E. Angel, Interactive Computer Graphics
            A Top-Down Approach with OpenGL, Third Edition
            Addison-Wesley Longman, 2003

        @pre: The .RAW file MUST exist before this function is called, else this function will exit prematurely.
    **/
    GLuint fileGetTexImage(char* name);


    unsigned int fileGenRawTexture(const char* filePath, int width, int height);

    /** @brief: Read in the data from an external .RAW formatted file and output it to a .TXT formatted file.

        @param: rawFilePath (const char * ) - The path of the .RAW file relative to the current working directory.
        @param: txtFilePath (const char * ) - The path of the .TXT file relative to the current working directory (NOT created if non-existent).
        @param: width (int) - The width of the image.
        @param: height (int) - The height of the image.

        @return: NONE.

        @pre: BOTH files MUST exist before this function is called, else this function will exit prematurely.
    **/
    void fileConvertRAWtoTXT(const char* rawFilePath, const char* txtFilePath, int width, int height);

    /** @brief: Get the absolute path of the program's current working directory.

        @param: NONE.

        @return: A string (max 1024 characters) that represents the absolute path of the current working directory.

        @post: If the current working directory has not been set before this function is called, it is now.
    **/
    const char* fileGetWorkingDirectory();

#endif
