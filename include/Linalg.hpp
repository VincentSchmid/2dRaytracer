#ifndef Linalg_h
#define Linalg_h

#include <blaze/Blaze.h>
#include <random>
#include <list>


bool isLineBetweenTwoPoints(blaze::StaticVector<float,2UL> lineP1, blaze::StaticVector<float,2UL> lineP2, blaze::StaticVector<float,2UL> p1, blaze::StaticVector<float,2UL> p2)
{
    blaze::StaticVector<float,2UL> AB = lineP2 - lineP1;
    blaze::StaticVector<float,2UL> AC = p1 - lineP1;
    blaze::StaticVector<float,2UL> AD = p2 - lineP1;
    
    return ( blaze::cross(AB, AC) * blaze::cross(AB, AD) )[0] < 0;
}

bool isVectorPointingBetweenTwoPoints(blaze::StaticVector<float,2UL> P1, blaze::StaticVector<float,2UL> P2, blaze::StaticVector<float,2UL> position, blaze::StaticVector<float,2UL> direction)
{
    blaze::StaticVector<float,2UL> A = P1 - position;
    blaze::StaticVector<float,2UL> C = P2 - position;

    return ( blaze::cross(A, direction) * blaze::cross(A, C) )[0] >= 0 && ( blaze::cross(C, direction) * blaze::cross(C, A) )[0] >= 0;
}

float Distance(blaze::StaticVector<float,2UL> v1, blaze::StaticVector<float,2UL> v2)
{
    return blaze::abs(blaze::norm(v2 - v1));
}

float distanceToLine(blaze::StaticVector<float,2UL> point, blaze::StaticVector<float,2UL> lineP1, blaze::StaticVector<float,2UL> lineP2)
{
    blaze::StaticVector<float,2UL> direction = lineP2 - lineP1;
    float orth_intersect = blaze::dot(direction, point - lineP1) / blaze::dot(direction, direction);
    blaze::StaticVector<float,2UL> intesect_pnt = lineP1 + orth_intersect * direction;

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

std::list<blaze::StaticVector<float,2UL>> getPointsAlongLine(blaze::StaticVector<float,2UL> A, blaze::StaticVector<float,2UL> B, int count, bool randomDistribution)
{
    std::list<blaze::StaticVector<float,2UL>> vectors = {};
    blaze::StaticVector<float,2UL> direction = B - A;
    direction = blaze::normalize(direction);
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

blaze::StaticVector<float,2UL> PerpendicularClockwise(blaze::StaticVector<float,2UL> vector)
{
    float tmp = vector[0];
    vector[0] = vector[1];
    vector[1] = -tmp;

    return vector;
}

blaze::StaticVector<float,2UL> PerpendicularCounterClockwise(blaze::StaticVector<float,2UL> vector)
{
    float tmp = vector[0];
    vector[0] = -vector[1];
    vector[1] = tmp;

    return vector;
}

std::list<blaze::StaticVector<float,2UL>> getPointsAlongLine(blaze::StaticVector<float,2UL> center, blaze::StaticVector<float,2UL> normal, float width, int count, bool randomDistribution)
{
    normal = blaze::normalize(normal);
    blaze::StaticVector<float,2UL> left = PerpendicularCounterClockwise(normal);
    blaze::StaticVector<float,2UL> right = PerpendicularClockwise(normal);

    blaze::StaticVector<float,2UL> A = center + left * (width / 2.0f);
    blaze::StaticVector<float,2UL> B = A + right * width;

    return getPointsAlongLine(A, B, count, randomDistribution);
}

#endif