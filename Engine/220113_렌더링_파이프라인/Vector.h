#pragma once
#include <cmath>
#include "Matrix.h"

template<size_t n>
using Vector = Matrix<1, n>;

template<size_t n>
inline float const Dot(Vector<n> const& u, Vector<n> const& v)
{
    return u * Transpose(v);
}

template<size_t n>
inline float const Length(Vector<n> const& v)
{
    return sqrt(Dot(v, v));
}

template<size_t n>
inline Vector<n> const Normalize(Vector<n> const& v)
{
    return v / Length(v);
}

inline Vector<3> const Cross(Vector<3> const& u, Vector<3> const& v)
{
    Vector<3> product = Vector<3>();

    for (size_t i = 0; i < 3; ++i)
    {
        size_t const j = (i + 1) % 3;
        size_t const k = (j + 1) % 3;

        product[i] = u[j] * v[k] - u[k] * v[j];
    }

    return product;
}