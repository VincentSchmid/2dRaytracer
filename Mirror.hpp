#ifndef MathX_h
#define MathX_h

#include "MathX.h"

#endif

#ifndef rlgl_h
#define rlgl_h

#include "rlgl.h"

#endif

#include <iostream>

#ifndef helpers_h
#define helpers_h

#include "helpers.hpp"

#endif

class Mirror
{
    private:
        MathX::Vector2 position;
        MathX::Vector2 normal;
        MathX::Vector2 leftCorner;
        MathX::Vector2 rightCorner;
        float size;

    public:
        Mirror(MathX::Vector2 position, MathX::Vector2 normal, float size) 
        : position(position)
        , normal(normal.Normalize())
        , size(size)
        {
            leftCorner = normal.PerpendicularCounterClockwise() * (size / 2.0f) + position;
            rightCorner = normal.PerpendicularClockwise() * (size / 2.0f) + position;

            leftCorner.Print();
            rightCorner.Print();
        };

        void draw();
        void collide(LightRay *ray);
        bool isColliding(LightRay *ray);

    private:
        float getDistance(MathX::Vector2 point);
        bool isPassingThrough(MathX::Vector2 firstPoint, MathX::Vector2 secondPoint);
        bool isPointingAtMirror(MathX::Vector2 position, MathX::Vector2 direction);
};

void Mirror::draw()
{
    //MathX::Vector2 tmp = normal * 100 + position;
    //DrawLineCorrected(position.X, position.Y, tmp.X, tmp.Y, DARKGREEN);
    DrawLineCorrected(leftCorner.X, leftCorner.Y, rightCorner.X, rightCorner.Y, Dark_Blue);
}

void Mirror::collide(LightRay *ray)
{  
    refract(ray, normal, 1.0f, 1.33f);
}

bool Mirror::isColliding(LightRay *ray)
{
    return isPassingThrough(ray->position, ray->nextPosition) && isPointingAtMirror(ray->position, ray->direction);
}

float Mirror::getDistance(MathX::Vector2 point)
{
    MathX::Vector2 direction = rightCorner - leftCorner;
    float orth_intersect = direction.Dot(point - leftCorner) / direction.Dot(direction);
    MathX::Vector2 intesect_pnt = leftCorner + orth_intersect * direction;

    intesect_pnt = orth_intersect < 0 ? leftCorner : intesect_pnt;
    intesect_pnt = orth_intersect > 1 ? rightCorner : intesect_pnt;

    return point.Distance(intesect_pnt);
}

bool Mirror::isPassingThrough(MathX::Vector2 C, MathX::Vector2 D)
{
    MathX::Vector2 AB = rightCorner - leftCorner;
    MathX::Vector2 AC = C - leftCorner;
    MathX::Vector2 AD = D - leftCorner;
    
    return AB.Cross(AC) * AB.Cross(AD) < 0;
}

bool Mirror::isPointingAtMirror(MathX::Vector2 position, MathX::Vector2 direction)
{
    MathX::Vector2 A = leftCorner - position;
    MathX::Vector2 C = rightCorner - position;

    return A.Cross(direction) * A.Cross(C) >= 0 && C.Cross(direction) * C.Cross(A) >= 0;
}
