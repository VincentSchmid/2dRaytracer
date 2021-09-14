#ifndef Line_h
#define Line_h

#include "helpers.hpp"
#include "Linalg.hpp"

#include <iostream>
#include <blaze/Blaze.h>


class Line : public Shape 
{
    private:
        blaze::StaticVector<float,2UL> normal;
        blaze::StaticVector<float,2UL> leftCorner;
        blaze::StaticVector<float,2UL> rightCorner;

    public:
        Line(blaze::StaticVector<float,2UL> position, blaze::StaticVector<float,2UL> normal, float size, Surface *surface) 
        : Shape(position, size, surface)
        , normal(blaze::norm(normal))
        {
            leftCorner = PerpendicularCounterClockwise(normal) * (size / 2.0f) + position;
            rightCorner = PerpendicularClockwise(normal) * (size / 2.0f) + position;
        };

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray) { return false; };
        blaze::StaticVector<float,2UL> getNormal(blaze::StaticVector<float,2UL> rayPosition) { return normal; };
};

void Line::draw()
{
    //blaze::StaticVector<float,2UL> tmp = normal * 100 + position;
    //DrawLineCorrected(position[0], position[1], tmp[0], tmp[1], DARKGREEN);

    DrawLineCorrected(leftCorner[0], leftCorner[1], rightCorner[0], rightCorner[1], Dark_Blue);
}

bool Line::isColliding(LightRay *ray)
{
    return isLineBetweenTwoPoints(leftCorner, rightCorner, ray->position, ray->nextPosition) && isVectorPointingBetweenTwoPoints(leftCorner, rightCorner, ray->position, ray->direction);
}

#endif