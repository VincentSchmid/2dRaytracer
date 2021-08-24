#ifndef MathX_h
#define MathX_h

#include "MathX.h"

#endif


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