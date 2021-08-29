#ifndef Shape_h
#define Shape_h

#include "MathX.h"
#include "Ray.hpp"
#include "Surface.hpp"


class Shape
{
    public:
        Surface *surface;

    protected:
        MathX::Vector2 position;
        float size;

    public:
        Shape(MathX::Vector2 position, float size, Surface *surface) 
        : position(position)
        , size(size)
        , surface(surface)
        {};

        virtual void draw() = 0;
        virtual bool isColliding(LightRay *ray) = 0;
        virtual bool isInside(LightRay *ray) = 0;
        virtual MathX::Vector2 getNormal(MathX::Vector2 rayPosition) = 0;
};

#endif