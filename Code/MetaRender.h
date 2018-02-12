#include <cstdio>

//=============================================================================
// Camera
//=============================================================================
template <typename _center, typename _dir, int _halfSize, int _eyeDist>
struct Camera {
private:
    typedef _center center;
    typedef _dir dir;
    typedef typename VecAdd<center, typename VecScale<_dir, _eyeDist>::result>::result eye;
    static const int halfSize = _halfSize;

public:
    template <int x, int y, int width, int height>
    struct GetRay {
    private:
        typedef Vector<
            -halfSize + 2*halfSize * x/width, 
            -halfSize + 2*halfSize * y/height, 
            0
        > pos;
        typedef typename VecSub<pos, eye>::result dir;
    public:
        typedef Ray<pos, dir> result;
    };
};


//=============================================================================
// Query - Find the resulting intersect info for a ray against a list of objects
//=============================================================================
template <typename ray, typename list>
struct Query {
private:
    typedef Intersect<ray, typename list::head> curr; 
    typedef Query<ray, typename list::tail> tail;

    static const bool useCurr   = curr::found && curr::dist < tail::dist;

    static const int64  bestDist = useCurr ? curr::dist : tail::dist;

    typedef typename If<
        useCurr,
        typename list::head,
        typename tail::object
    >::result bestObject;

    typedef typename If<
        useCurr,
        typename curr::normal,
        typename tail::normal
    >::result bestNormal;

public:
    static const int64 dist = bestDist;
    typedef bestNormal normal;
    typedef bestObject object;
};

// Partial specialization to stop recursion
template <typename ray>
struct Query<ray, Null> {
    static const int64 dist = 0xffffffff;
    typedef Null normal;
    typedef Null object;
};


//=============================================================================
// TEST DATA - can later be passed in as template arguments
//=============================================================================
typedef Typelist<
    Sphere<Vector< 00, 0, 500>, 40, Red>,
    Sphere<Vector<-60, 0, 500>, 20, Green>,
    Sphere<Vector< 60, 0, 500>, 20, Blue>
>::head MyObjectList;

typedef Camera<
    Vector<0, 0, -0>,
    Vector<0, 0, 1>,
    80,
    250
> MyCamera;

typedef Vector<10, 10, 10> MyLight;
const int MyLightLen = VecLen<MyLight>::result; // Preprocess this to save some time


//=============================================================================
// ComputeColor
//=============================================================================
template <typename object, typename normal>
struct ComputeColor {
private:
    //compile_assert(VecLenSq<normal>::result != 0);

    static const int normalLen = VecLen<normal>::result;
    static const int NdotL       = VecDot<normal, MyLight>::result;
    static const int diffuse     = Max<NdotL, 0>::result;
    static const int den         = normalLen * MyLightLen;
    typedef typename ColScale<
        typename object::color, 
        diffuse + 192, 
        Max<den, 1>::result
    >::result litColor;

public:
    typedef litColor result;
};

// Partial specialization for when no object was intersected with
template <typename normal>
struct ComputeColor<Null, normal> {
    typedef Black result;
};

// Error caused by a zeroed normal, partially specialize to continue execution
template <typename object>
struct ComputeColor<object, Vector<0, 0, 0>> {
    typedef typename object::color result;
};


//=============================================================================
// Raytrace - Does the work of figuring out a color given a position on screen
//=============================================================================
template <int x, int y, int width, int height>
struct Raytrace {
private:
    typedef typename MyCamera::GetRay<x, y, width, height>::result ray;
    typedef Query<ray, MyObjectList> query;

    // TODO: recursively call Raytrace for shadows, reflection, etc...

    typedef typename ComputeColor<
        typename query::object,
        typename query::normal
    >::result color;
public:
    typedef typename color result;
};


//=============================================================================
// Render - does the work of translating compile-time constants to the output file
//=============================================================================
template <int x, int y, int width, int height>
inline void Render (FILE * pFile) {
    typedef Raytrace<x, y, width, height>::result color;
    putc(Clamp<color::b, 0, 255>::result, pFile);
    putc(Clamp<color::g, 0, 255>::result, pFile);
    putc(Clamp<color::r, 0, 255>::result, pFile);
}


//=============================================================================
// Loop - a "double for" loop, y in range 0 to height acts as outer loop
//=============================================================================
template <int x, int y, int width, int height>
struct Loop {
private:
    typedef Loop<x+1, y, width, height> right;

public:
    static void Exec (FILE * pFile) {
        Render<x, y, width, height>(pFile);
        right::Exec(pFile);
    }

};

// Partial specialization which initiates next row and continues down current row
template <int y, int width, int height>
struct Loop<0, y, width, height> {
private:
    typedef Loop<1, y, width, height> right;
    typedef Loop<0, y+1, width, height> down;

public:
    static void Exec (FILE * pFile) {
        Render<0, y, width, height>(pFile);
        right::Exec(pFile);
        down::Exec(pFile);
    }
};

// Partial specialization which ends a single row
template <int y, int width, int height>
struct Loop<width, y, width, height> {
    static void Exec (FILE * pFile) {
        // Nothing
    }
};

// Partial specialization which ends all recursion
template <int width, int height>
struct Loop<0, height, width, height> {
    static void Exec (FILE * pFile) {
        // Nothing
    }
};



//=============================================================================
// Render - Creates a file for output and initializes the render loop. Can later 
//          pass parameters to this instead of using "hard coded" objects.
//=============================================================================
template <int width, int height>
struct Renderer {
    static void Save (const char * filename) {
        FILE * pFile;
        int rv = fopen_s(&pFile, filename, "w");
        if (rv != 0) {
            printf("Bad file: %s", filename);
            return;
        }

        putc(0, pFile);
        putc(0, pFile);
        putc(2, pFile);                         /* uncompressed RGB */
        putc(0, pFile); putc(0, pFile);
        putc(0, pFile); putc(0, pFile);
        putc(0, pFile);
        putc(0, pFile); putc(0, pFile);           /* X origin */
        putc(0, pFile); putc(0, pFile);           /* y origin */
        putc((width & 0x00FF), pFile);
        putc((width & 0xFF00) / 256, pFile);
        putc((height & 0x00FF), pFile);
        putc((height & 0xFF00) / 256, pFile);
        putc(24, pFile);                        /* 24 bit bitmap */
        putc(0, pFile);

        Loop<0, 0, width, height>::Exec(pFile);

        fclose(pFile);
    };

};

