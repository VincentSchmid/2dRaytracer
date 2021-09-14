#ifndef Triangle_h
#define Triangle_h

#include "Shape.hpp"
#include "raylib.h"
#include "helpers.hpp"
#include "Linalg.hpp"

#include <math.h>
#include <functional>
#include <blaze/Blaze.h>


class Triangle : public Shape
{
    private:
        float a; // length of a side of the triangle
        blaze::StaticVector<float,2UL> v1;
        blaze::StaticVector<float,2UL> v2;
        blaze::StaticVector<float,2UL> v3;
    
    public:
        Triangle(blaze::StaticVector<float,2UL> position, float size, Surface *surface) 
        : Shape(position, size, surface)
        {
            float r = size;
            a = r / (sqrtf(3) / 3.0f);

            blaze::StaticVector<float,2UL> p0p1 = blaze::StaticVector<float,2UL>{sqrtf(3) * r / 2.0f, r / 2};

            v1 = blaze::StaticVector<float,2UL>{position[0], position[1] + r};
            v2 = blaze::StaticVector<float,2UL>{position[0] - p0p1[0], position[1] - p0p1[1]};
            v3 = blaze::StaticVector<float,2UL>{position[0] + p0p1[0], position[1] - p0p1[1]};
        };

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray);
        blaze::StaticVector<float,2UL> getNormal(blaze::StaticVector<float,2UL> rayPosition);

    private:
        bool collisionEnter(LightRay *ray);
        bool collisionExit(LightRay *ray);
        float sign(blaze::StaticVector<float,2UL> p1, blaze::StaticVector<float,2UL> p2, blaze::StaticVector<float,2UL> p3);
        bool pointIsInTriangle(blaze::StaticVector<float,2UL> pt);
};

void Triangle::draw()
{
    /*
    //normals
    auto drawNormal = [this](blaze::StaticVector<float,2UL> p1, blaze::StaticVector<float,2UL> p2, float normalLength, Color color) {
        blaze::StaticVector<float,2UL> tmp = p1 + ((p2 - p1) / 2);
        blaze::StaticVector<float,2UL> tmpNrml = getNormal(tmp) * normalLength + tmp;
        DrawLineCorrected(tmp[0], tmp[1], tmpNrml[0], tmpNrml[1], color);
    };

    drawNormal(v1, v2, 100.0f, RED);
    drawNormal(v1, v3, 100.0f, RED);
    drawNormal(v2, v3, 100.0f, RED);
    */

    DrawTriangleCorrected(v1, v2, v3, BLUE);
}

blaze::StaticVector<float,2UL> Triangle::getNormal(blaze::StaticVector<float,2UL> rayPosition)
{
    blaze::StaticVector<float,2UL> normal;

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

    return blaze::normalize(normal);
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

float Triangle::sign (blaze::StaticVector<float,2UL> p1, blaze::StaticVector<float,2UL> p2, blaze::StaticVector<float,2UL> p3)
{
    return (p1[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p3[1]);
}

bool Triangle::pointIsInTriangle(blaze::StaticVector<float,2UL> pt)
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