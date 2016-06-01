
#ifndef FLAG_JVTypes

    #define FLAG_JVTypes

    #ifdef __APPLE__
    #include <GLUT/glut.h>
    #else
    #include <GL/glut.h>
    #endif

    /// A 2D point in space.
    typedef float point2[2];

    /// A 3D point in space.
    typedef float point3[3];

    /// An integer version of a point2.
    typedef int int2[2];

    /// A Glubyte array for textureing representing red, green and blue
    typedef GLubyte pixel[3];

#endif
