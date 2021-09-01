#ifndef Line_h
#define Line_h

#include "MathX.h"
#include "helpers.hpp"
#include "Linalg.hpp"

#include <iostream>


class Line : public Shape 
{
    private:
        MathX::Vector2 normal;
        MathX::Vector2 leftCorner;
        MathX::Vector2 rightCorner;

    public:
        Line(MathX::Vector2 position, MathX::Vector2 normal, float size, Surface *surface) 
        : Shape(position, size, surface)
        , normal(normal.Normalize())
        {
            leftCorner = normal.PerpendicularCounterClockwise() * (size / 2.0f) + position;
            rightCorner = normal.PerpendicularClockwise() * (size / 2.0f) + position;
        };

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray) { return false; };
        MathX::Vector2 getNormal(MathX::Vector2 rayPosition) { return normal; };
};

void Line::draw()
{
    //MathX::Vector2 tmp = normal * 100 + position;
    //DrawLineCorrected(position.X, position.Y, tmp.X, tmp.Y, DARKGREEN);

    DrawLineCorrected(leftCorner.X, leftCorner.Y, rightCorner.X, rightCorner.Y, Dark_Blue);
}

bool Line::isColliding(LightRay *ray)
{
    return isLineBetweenTwoPoints(leftCorner, rightCorner, ray->position, ray->nextPosition) && isVectorPointingBetweenTwoPoints(leftCorner, rightCorner, ray->position, ray->direction);
}

#endif