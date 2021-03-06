#pragma once

#include "MetaMath.h"

//=============================================================================
// Vector
//=============================================================================
template <int _x, int _y, int _z>
struct Vector {
    static const int x = _x;
    static const int y = _y;
    static const int z = _z;
};


//=============================================================================
// VecAdd
//=============================================================================
template <typename v1, typename v2>
struct VecAdd {
    typedef Vector<
        v1::x + v2::x,
        v1::y + v2::y,
        v1::z + v2::z
    > result;
};


//=============================================================================
// VecSub
//=============================================================================
template <typename v1, typename v2>
struct VecSub {
    typedef Vector<
        v1::x - v2::x,
        v1::y - v2::y,
        v1::z - v2::z
    > result;
};


//=============================================================================
// VecMult
//=============================================================================
template <typename v1, typename v2>
struct VecMult {
    typedef Vector<
        v1::x * v2::x,
        v1::y * v2::y,
        v1::z * v2::z
    > result;
};


//=============================================================================
// VecDiv
//=============================================================================
template <typename v1, typename v2>
struct VecDiv {
    typedef Vector<
        v1::x / v2::x,
        v1::y / v2::y,
        v1::z / v2::z
    > result;
};


//=============================================================================
// VecScale
//=============================================================================
template <typename v, int num, int den = 1>
struct VecScale {
    typedef Vector<
        v::x * num / den,
        v::y * num / den,
        v::z * num / den
    > result;
};


//=============================================================================
// VecDot
//=============================================================================
template <typename v1, typename v2>
struct VecDot {
    static const int result = 
        v1::x * v2::x +
        v1::y * v2::y +
        v1::z * v2::z;
};


//=============================================================================
// VecLenSq
//=============================================================================
template <typename v>
struct VecLenSq {
    static const int result = VecDot<v, v>::result;
};


//=============================================================================
// VecLen
//=============================================================================
template <typename v>
struct VecLen {
    static const int result = Sqrt<VecLenSq<v>::result>::result;
};