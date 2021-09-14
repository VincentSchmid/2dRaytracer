#ifndef Triangle_h
#define Triangle_h

#include "Shape.hpp"
#include "raylib.h"
#include "helpers.hpp"
#include "Vector2d.hpp"
#include "Linalg.hpp"

#include <math.h>
#include <functional>


class Triangle : public Shape
{
    private:
        float sideLength; // length of a side of the triangle
        Vector2d v1;
        Vector2d v2;
        Vector2d v3;
    
    public:
        Triangle(Vector2d position, float size, Surface *surface) 
        : Shape(position, size, surface)
        {
            float r = size;
            sideLength = r / (sqrtf(3) / 3.0f);

            Vector2d p0p1 = Vector2d(sqrtf(3) * r / 2.0f, r / 2);

            v1 = Vector2d(position.x, position.y + r);
            v2 = Vector2d(position.x - p0p1.x, position.y - p0p1.y);
            v3 = Vector2d(position.x + p0p1.x, position.y - p0p1.y);
        };

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray);
        Vector2d getNormal(Vector2d rayPosition);

    private:
        bool collisionEnter(LightRay *ray);
        bool collisionExit(LightRay *ray);
        float sign(Vector2d p1, Vector2d p2, Vector2d p3);
        bool pointIsInTriangle(Vector2d pt);
};

void Triangle::draw()
{
    /*
    //normals
    auto drawNormal = [this](Vector2d p1, Vector2d p2, float normalLength, Color color) {
        Vector2d tmp = p1 + ((p2 - p1) / 2);
        Vector2d tmpNrml = getNormal(tmp) * normalLength + tmp;
        DrawLineCorrected(tmp.x, tmp.y, tmpNrml.x, tmpNrml.y, color);
    };

    drawNormal(v1, v2, 100.0f, RED);
    drawNormal(v1, v3, 100.0f, RED);
    drawNormal(v2, v3, 100.0f, RED);
    */

    DrawTriangleCorrected(v1, v2, v3, BLUE);
}

Vector2d Triangle::getNormal(Vector2d rayPosition)
{
    Vector2d normal;

    float d1 = distanceToLine(rayPosition, v1, v2);
    float d2 = distanceToLine(rayPosition, v1, v3);
    float d3 = distanceToLine(rayPosition, v2, v3);

    float dmin = d1 < d2 ? d1 : d2;
    dmin = dmin < d3 ? dmin : d3;

    if (dmin == d1)
    {
        normal = v1 - v2;
    }

    else if (dmin == d2)
    {
        normal = v3 - v1;
    }

    else if (dmin == d3)
    {
        normal = v2 - v3;
    }
    normal = PerpendicularCounterClockwise(normal);

    return Normalize(normal);
}

bool Triangle::collisionEnter(LightRay *ray)
{
    return !pointIsInTriangle(ray->position) && pointIsInTriangle(ray->nextPosition);
}

bool Triangle::collisionExit(LightRay *ray)
{
    return pointIsInTriangle(ray->position) && !pointIsInTriangle(ray->nextPosition);
}

bool Triangle::isInside(LightRay *ray)
{
    return pointIsInTriangle(ray->position);
}

bool Triangle::isColliding(LightRay *ray)
{
    return collisionEnter(ray) || collisionExit(ray);
}

float Triangle::sign (Vector2d p1, Vector2d p2, Vector2d p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Triangle::pointIsInTriangle(Vector2d pt)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

#endif