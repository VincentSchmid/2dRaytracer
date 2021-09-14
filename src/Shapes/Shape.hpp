#ifndef Shape_h
#define Shape_h

#include "Vector2d.hpp"
#include "Ray.hpp"
#include "Surface.hpp"


class Shape
{
    public:
        Surface *surface;

    protected:
        Vector2d position;
        float size;

    public:
        Shape(Vector2d position, float size, Surface *surface) 
        : position(position)
        , size(size)
        , surface(surface)
        {};

        virtual void draw() = 0;
        virtual bool isColliding(LightRay *ray) = 0;
        virtual bool isInside(LightRay *ray) = 0;
        virtual Vector2d getNormal(Vector2d rayPosition) = 0;
};

#endif