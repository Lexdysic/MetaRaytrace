
#pragma once

//=============================================================================
// Null
//=============================================================================
struct Null {};


//=============================================================================
// static_assert
//=============================================================================
template <bool cond> struct StaticAssert;
template <> struct StaticAssert<true> {};

#define compile_assert(expr) StaticAssert<(expr) != 0> ASSERT ## __LINE__


//=============================================================================
// Min
//=============================================================================
template <int a, int b>
struct Min {
    static const int result = a < b ? a : b;
};


//=============================================================================
// Max
//=============================================================================
template <int a, int b>
struct Max {
    static const int result = a > b ? a : b;
};


//=============================================================================
// Clamp
//=============================================================================
template <int x, int min, int max>
struct Clamp {
    static const int result = Max<Min<x, max>::result, min>::result;
};


//=============================================================================
// If - Returns one of two types based on Cond
//=============================================================================
template <bool Cond, typename T, typename F>
struct If {
    typedef T result;
};

template <typename T, typename F>
struct If<false, T, F> {
    typedef F result;
};


//=============================================================================
// TypelistNode
//=============================================================================
template <typename _H, typename _T>
struct TypelistNode {
    typedef _H head;
    typedef _T tail;
};


//=============================================================================
// Typelist
//=============================================================================
template <
    typename _0 = Null, typename _1 = Null, typename _2 = Null, typename _3 = Null, typename _4 = Null,
    typename _5 = Null, typename _6 = Null, typename _7 = Null, typename _8 = Null, typename _9 = Null
>
struct Typelist {
private:
    typedef typename Typelist<_1, _2, _3, _4, _5, _6, _7, _8>::head tail;
public:
    typedef TypelistNode<_0, tail> head;
};

// Specialization to stop recursion
template <>
struct Typelist<
    Null, Null, Null, Null, Null,
    Null, Null, Null, Null, Null
>
{
    typedef Null head;
};



