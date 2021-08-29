#ifndef Linalg_h
#define Linalg_h

#include "MathX.h"


bool isLineBetweenTwoPoints(MathX::Vector2 lineP1, MathX::Vector2 lineP2, MathX::Vector2 p1, MathX::Vector2 p2)
{
    MathX::Vector2 AB = lineP2 - lineP1;
    MathX::Vector2 AC = p1 - lineP1;
    MathX::Vector2 AD = p2 - lineP1;
    
    return AB.Cross(AC) * AB.Cross(AD) < 0;
}

bool isVectorPointingBetweenTwoPoints(MathX::Vector2 P1, MathX::Vector2 P2, MathX::Vector2 position, MathX::Vector2 direction)
{
    MathX::Vector2 A = P1 - position;
    MathX::Vector2 C = P2 - position;

    return A.Cross(direction) * A.Cross(C) >= 0 && C.Cross(direction) * C.Cross(A) >= 0;
}

float distanceToLine(MathX::Vector2 point, MathX::Vector2 lineP1, MathX::Vector2 lineP2)
{
    MathX::Vector2 direction = lineP2 - lineP1;
    float orth_intersect = direction.Dot(point - lineP1) / direction.Dot(direction);
    MathX::Vector2 intesect_pnt = lineP1 + orth_intersect * direction;

    intesect_pnt = orth_intersect < 0 ? lineP1 : intesect_pnt;
    intesect_pnt = orth_intersect > 1 ? lineP2 : intesect_pnt;

    return point.Distance(intesect_pnt);
}

std::list<MathX::Vector2> getPointsAlongLine(MathX::Vector2 A, MathX::Vector2 B, int count)
{
    std::list<MathX::Vector2> vectors = {};
    MathX::Vector2 direction = B - A;
    direction.Normalize();

    float width = A.Distance(B);
    float spacing = width / count;

    for (int i = 0; i < count; i++)
    {
        vectors.push_back(A + (spacing * i) * direction);
    }
    
    return vectors;
}

std::list<MathX::Vector2> getPointsAlongLine(MathX::Vector2 center, MathX::Vector2 normal, float width, int count)
{
    normal.Normalize();
    MathX::Vector2 left = normal.PerpendicularCounterClockwise();
    MathX::Vector2 right = normal.PerpendicularClockwise();

    MathX::Vector2 A = center + left * (width / 2.0f);
    MathX::Vector2 B = A + right * width;

    return getPointsAlongLine(A, B, count);
}

#endif