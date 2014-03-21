

//=============================================================================
// Color
//=============================================================================
template <int _r, int _g, int _b>
struct Color {
    static const int r = _r;
    static const int g = _g;
    static const int b = _b;
};

//=============================================================================
// ColAdd
//=============================================================================
template <typename c1, typename c2>
struct ColAdd {
    typedef Color<
        c1::r + c2::r,
        c1::g + c2::g,
        c1::b + c2::b
    > result;
};

//=============================================================================
// ColSub
//=============================================================================
template <typename c1, typename c2>
struct ColSub {
    typedef Color<
        c1::r - c2::r,
        c1::g - c2::g,
        c1::b - c2::b
    > result;
};

//=============================================================================
//  ColMult
//=============================================================================
template <typename c1, typename c2>
struct ColMult {
    typedef Color<
        c1::r * c2::r,
        c1::g * c2::g,
        c1::b * c2::b
    > result;
};

//=============================================================================
//  ColDiv
//=============================================================================
template <typename c1, typename c2>
struct ColDiv {
    typedef Color<
        c1::r / c2::r,
        c1::g / c2::g,
        c1::b / c2::b
    > result;
};


//=============================================================================
// ColScale
//=============================================================================
template <typename c, int num, int den = 1>
struct ColScale {
    typedef Color<
        c::r * num / den,
        c::g * num / den,
        c::b * num / den
    > result;
};


//=============================================================================
//  Constants
//=============================================================================
typedef Color<0x00, 0x00, 0x00> Black;
typedef Color<0xff, 0xff, 0xff> White;
typedef Color<0xff, 0x00, 0x00> Red;
typedef Color<0x00, 0xff, 0x00> Green;
typedef Color<0x00, 0x00, 0xff> Blue;



