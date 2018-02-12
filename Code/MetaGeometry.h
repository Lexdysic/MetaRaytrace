#include "MetaVector.h"


//=============================================================================
// Sphere
//=============================================================================
template <typename _pos, int _radius, typename _color>
struct Sphere {
    typedef _pos     pos;
    typedef _color   color;
    static const int radius = _radius;
};


//=============================================================================
// Ray
//=============================================================================
template <typename _pos, typename _dir>
struct Ray {
    typedef _pos pos;
    typedef _dir dir;
};


//=============================================================================
// Intersect
//=============================================================================
template <typename ray, typename sphere>
struct Intersect {
private:
    typedef typename VecSub<typename ray::pos, typename sphere::pos>::result   m;
    static const int64 a    = VecDot<typename ray::dir, typename ray::dir>::result;
    static const int64 b    = 2 * VecDot<m, typename ray::dir>::result;
    static const int64 c    = VecDot<m, m>::result - sphere::radius * sphere::radius;
    static const int64 disc = b*b - 4*a*c;

    // Query - Conditional computation of intersection results (saves lots of time)
    template <bool cond, int64 disc, int64 a, int64 b, typename _ray, typename _sphere>
    struct Query {
        // found
        static const bool found = true;

        // dist
        static const int64 dist = (-b - Sqrt<disc>::result) / (2*a);

        // pos
        typedef typename VecAdd<
            typename _ray::pos,
            typename VecScale<
                typename _ray::dir, 
                dist
            >::result
        >::result pos;

        // normal
        typedef typename VecSub<
            pos,
            typename _sphere::pos
        >::result normal;
    };

    // Partially Specialize to stop processing of computations
    template <int64 disc, int64 a, int64 b, typename _ray, typename _sphere>
    struct Query<false, disc, a, b, _ray, _sphere> {
        static const bool found = false;
        static const int64 dist = -1;
        typedef Null       pos;
        typedef Null       normal;
    };

    typedef Query<disc>=0, disc, a, b, ray, sphere> query;
public:
    static const int64 dist = query::dist;
    static const bool found = query::found;
    typedef typename query::pos pos;
    typedef typename query::normal normal;
};
