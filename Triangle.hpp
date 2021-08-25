#ifndef Triangle_h
#define Triangle_h

#include "Shape.hpp"
#include "raylib.h"
#include "helpers.hpp"
#include "MathX.h"
#include "Linalg.hpp"

#include <math.h>
#include <functional>


class Triangle : public Shape
{
    private:
        float a; // length of a side of the triangle
        MathX::Vector2 v1;
        MathX::Vector2 v2;
        MathX::Vector2 v3;
    
    public:
        Triangle(MathX::Vector2 position, float size, Surface *surface) 
        : Shape(position, size, surface) 
        {
            float r = size;
            a = r / (sqrtf(3) / 3.0f);

            MathX::Vector2 p0p1 = MathX::Vector2{sqrtf(3) * r / 2.0f, r / 2};

            v1 = MathX::Vector2{position.X, position.Y + r};
            v2 = MathX::Vector2{position.X - p0p1.X, position.Y - p0p1.Y};
            v3 = MathX::Vector2{position.X + p0p1.X, position.Y - p0p1.Y};
        };

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray);
        MathX::Vector2 getNormal(MathX::Vector2 rayPosition);

    private:
        bool collisionEnter(LightRay *ray);
        bool collisionExit(LightRay *ray);
        float sign(MathX::Vector2 p1, MathX::Vector2 p2, MathX::Vector2 p3);
        bool pointIsInTriangle(MathX::Vector2 pt);
};

void Triangle::draw()
{
    /*
    //normals
    std::function<void(MathX::Vector2, MathX::Vector2, float, Color)> drawNormal = [this](MathX::Vector2 p1, MathX::Vector2 p2, float normalLength, Color color) {
        MathX::Vector2 tmp = p1 + ((p2 - p1) / 2);
        MathX::Vector2 tmpNrml = getNormal(tmp) * normalLength + tmp;
        DrawLineCorrected(tmp.X, tmp.Y, tmpNrml.X, tmpNrml.Y, color);
    };

    drawNormal(v1, v2, 100.0f, RED);
    drawNormal(v1, v3, 100.0f, RED);
    drawNormal(v2, v3, 100.0f, RED);
    */

    DrawTriangleCorrected(v1, v2, v3, BLUE);
}

MathX::Vector2 Triangle::getNormal(MathX::Vector2 rayPosition)
{
    MathX::Vector2 normal;

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
    normal = normal.PerpendicularCounterClockwise();
    normal.Normalize();

    return normal;
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

float Triangle::sign (MathX::Vector2 p1, MathX::Vector2 p2, MathX::Vector2 p3)
{
    return (p1.X - p3.X) * (p2.Y - p3.Y) - (p2.X - p3.X) * (p1.Y - p3.Y);
}

bool Triangle::pointIsInTriangle(MathX::Vector2 pt)
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