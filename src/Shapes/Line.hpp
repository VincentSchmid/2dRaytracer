#ifndef Line_h
#define Line_h

#include "Vector2d.hpp"
#include "helpers.hpp"
#include "Linalg.hpp"

#include <iostream>


class Line : public Shape 
{
    private:
        Vector2d normal;
        Vector2d leftCorner;
        Vector2d rightCorner;

    public:
        Line(Vector2d position, Vector2d normal, float size, Surface *surface) 
        : Shape(position, size, surface)
        , normal(Normalize(normal))
        {
            leftCorner = PerpendicularCounterClockwise(normal) * (size / 2.0f) + position;
            rightCorner = PerpendicularClockwise(normal) * (size / 2.0f) + position;
        };

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray) { return false; };
        Vector2d getNormal(Vector2d rayPosition) { return normal; };
};

void Line::draw()
{
    //Vector2d tmp = normal * 100 + position;
    //DrawLineCorrected(position.x, position.y, tmp.x, tmp.y, DARKGREEN);

    DrawLineCorrected(leftCorner.x, leftCorner.y, rightCorner.x, rightCorner.y, DARKBLUE);
}

bool Line::isColliding(LightRay *ray)
{
    return isLineBetweenTwoPoints(leftCorner, rightCorner, ray->position, ray->nextPosition) && isVectorPointingBetweenTwoPoints(leftCorner, rightCorner, ray->position, ray->direction);
}

#endif