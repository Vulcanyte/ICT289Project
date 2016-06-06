
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

    /// A GLubyte array for textureing representing red, green and blue.
    typedef GLubyte pixel[3];

    /// A GLybyte for one byte for each pixel.
    typedef GLubyte pixelSingle;

    /// An Array for texuture names.
    typedef char name[15];

    /// Representation of a single keyboard key, as well as its down state.
    typedef struct
    {
        char key;       // A certain key.
        short down;     // TRUE (1) if pushed down, else FALSE (0).

    }ControlKey;

#endif
