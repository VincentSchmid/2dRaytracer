#ifndef Linalg_h
#define Linalg_h

#include "Vector2d.hpp"

#include <random>
#include <list>


bool isLineBetweenTwoPoints(Vector2d lineP1, Vector2d lineP2, Vector2d p1, Vector2d p2)
{
    Vector2d AB = lineP2 - lineP1;
    Vector2d AC = p1 - lineP1;
    Vector2d AD = p2 - lineP1;
    
    return Cross(AB, AC) * Cross(AB, AD) < 0;
}

bool isVectorPointingBetweenTwoPoints(Vector2d P1, Vector2d P2, Vector2d position, Vector2d direction)
{
    Vector2d A = P1 - position;
    Vector2d C = P2 - position;

    return Cross(A, direction) * Cross(A, C) >= 0 && Cross(C, direction) * Cross(C, A) >= 0;
}

float distanceToLine(Vector2d point, Vector2d lineP1, Vector2d lineP2)
{
    Vector2d direction = lineP2 - lineP1;
    float orth_intersect = Dot(direction, (point - lineP1) ) / Dot(direction, direction);
    Vector2d intesect_pnt = lineP1 + orth_intersect * direction;

    intesect_pnt = orth_intersect < 0 ? lineP1 : intesect_pnt;
    intesect_pnt = orth_intersect > 1 ? lineP2 : intesect_pnt;

    return Distance(point, intesect_pnt);
}

float randRange(float min, float max)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(min, max); // define the range

    return distr(gen);
}

std::list<Vector2d> getPointsAlongLine(Vector2d A, Vector2d B, int count, bool randomDistribution)
{
    std::list<Vector2d> vectors = {};
    Vector2d direction = B - A;
    direction = Normalize(direction);
    float distanceFromOrigin;

    float width = Distance(A, B);
    float spacing = width / count;

    for (int i = 0; i < count; i++)
    {
        distanceFromOrigin = spacing * i;
        if (randomDistribution)
        {
            distanceFromOrigin = i == 0 ? randRange(0, spacing) : spacing * i + randRange(0, spacing);
        }
        vectors.push_back(A + distanceFromOrigin * direction);
    }
    
    return vectors;
}

std::list<Vector2d> getPointsAlongLine(Vector2d center, Vector2d normal, float width, int count, bool randomDistribution)
{
    normal = Normalize(normal);
    Vector2d left = PerpendicularCounterClockwise(normal);
    Vector2d right = PerpendicularClockwise(normal);

    Vector2d A = center + left * (width / 2.0f);
    Vector2d B = A + right * width;

    return getPointsAlongLine(A, B, count, randomDistribution);
}

#endif