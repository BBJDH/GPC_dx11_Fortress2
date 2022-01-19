#pragma once

#include "Vector.h"

namespace Collision
{
    struct Point final
    {
        Vector<2> Location = { 0, 0 };
    };

    struct Circle final
    {
        float     Diameter = { 0 };
        Vector<2> Location = { 0, 0 };
    };                      
                            
    struct Rectangle final  
    {                       
        Vector<2> Length   = { 0, 0 };
        float     Angle    = { 0 };
        Vector<2> Location = { 0, 0 };
    };

    bool Collide(Point     const & LHS, Circle    const & RHS);
    bool Collide(Point     const & LHS, Rectangle const & RHS);
    bool Collide(Circle    const & LHS, Circle    const & RHS);
    bool Collide(Circle    const & LHS, Rectangle const & RHS);
    bool Collide(Rectangle const & LHS, Rectangle const & RHS);
}