#define _USE_MATH_DEFINES

#include "Collision.h"

bool Collision::Collide(Point const & LHS, Circle const & RHS)
{
    return Length(LHS.Location - RHS.Location) <= RHS.Diameter / 2;
}

bool Collision::Collide(Point const & LHS, Rectangle const & RHS)
{
    if(RHS.Angle != 0)
    {
        return false;
    }
    else
    {
        Vector<2> const distance = LHS.Location - RHS.Location;

        return abs(distance[0]) <= RHS.Length[0] / 2 and abs(distance[1]) <= RHS.Length[1] / 2;
    }
}

bool Collision::Collide(Circle const & LHS, Circle const & RHS)
{
    return Collide
    (
         Point {                              LHS.Location },
        Circle { LHS.Diameter + RHS.Diameter, RHS.Location }
    );
}

bool Collision::Collide(Circle const & LHS, Rectangle const & RHS)
{
    Vector<2> const min = RHS.Location - RHS.Length / 2;
    Vector<2> const max = RHS.Location + RHS.Length / 2;

    if(RHS.Angle != 0)
    {
        return false;
    }
    else if
    (
        min[0] <= LHS.Location[0] and LHS.Location[0] <= max[0] or
        min[1] <= LHS.Location[1] and LHS.Location[1] <= max[1]
    )
    {
        return Collide
        (
                Point {                                                         LHS.Location },
            Rectangle { RHS.Length + Vector<2>(1, 1) * LHS.Diameter, RHS.Angle, RHS.Location }
        );
    }
    else
    {
        if(RHS.Location[0] < LHS.Location[0])
        {
            if(RHS.Location[1] < LHS.Location[1]) return Collide(Point { Vector<2>(max[0], max[1]) }, LHS);
            if(LHS.Location[1] < RHS.Location[1]) return Collide(Point { Vector<2>(max[0], min[1]) }, LHS);
        }
        else
        {
            if(RHS.Location[1] < LHS.Location[1]) return Collide(Point { Vector<2>(min[0], max[1]) }, LHS);
            if(LHS.Location[1] < RHS.Location[1]) return Collide(Point { Vector<2>(min[0], min[1]) }, LHS);
        }
    }
}

bool Collision::Collide(Rectangle const & LHS, Rectangle const & RHS)
{
    if(abs(LHS.Angle - RHS.Angle) < 0.1f)
    {
        return false;
    }
    else if(LHS.Angle == 0 and RHS.Angle == 0)
    {
        return Collide
        (
                Point {                             LHS.Location },
            Rectangle { LHS.Length + RHS.Length, 0, RHS.Location }
        );
    }
    else
    {
        Vector<2> const distance = LHS.Location - RHS.Location;

        if(Length(LHS.Length + RHS.Length) / 2 < Length(distance))
            return false;

        float constexpr radian = 3.141592653f / 180.0f;

        Vector<2> const axes[4]
        {
            {  cos(LHS.Angle * radian), sin(LHS.Angle * radian) },
            { -sin(LHS.Angle * radian), cos(LHS.Angle * radian) },
            {  cos(RHS.Angle * radian), sin(RHS.Angle * radian) },
            { -sin(RHS.Angle * radian), cos(RHS.Angle * radian) }
        };

        Vector<2> const vectors[4]
        {
            axes[0] * (LHS.Length[0] / 2),
            axes[1] * (LHS.Length[1] / 2),
            axes[2] * (RHS.Length[0] / 2),
            axes[3] * (RHS.Length[1] / 2)
        };

        for(int i = 0; i < 4; ++i)
        {
            float sum = 0;

            for(int j = 0; j < 4; ++j)
                sum += abs(Dot(axes[i], vectors[j]));

            if(sum < abs(Dot(axes[i], distance)))
                return false;
        }

        return true;
    }
}


