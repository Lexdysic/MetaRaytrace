#pragma once

typedef long long int64;

//=============================================================================
// Sqrt
//=============================================================================
template <int64 N>
struct Sqrt {
private:

    // Uses Newton-Raphson to solve for sqrt
    // http://en.wikipedia.org/wiki/Integer_square_root
    template <int64 K, int64 L, bool go>
    struct While {
        static const int64 C = (L+N/L)/2;
        static const int64 result = While<K+1, C, (L-C>=1)>::result;
    };

    // Partial specialization stops recursion
    template <int64 K, int64 L>
    struct While<K, L, false> {
        static const int64 result = (L+N/L)/2;
    };

public:
    static const int64 result = While<0, N, true>::result;
};

// Specialize on simple cases
template <>
struct Sqrt<1> {
    static const int64 result = 1;
};

template <>
struct Sqrt<0> {
    static const int64 result = 0;
};


