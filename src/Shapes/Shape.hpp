#ifndef Shape_h
#define Shape_h

#include "Ray.hpp"
#include "Surface.hpp"

#include <blaze/Blaze.h>


class Shape
{
    public:
        Surface *surface;

    protected:
        blaze::StaticVector<float,2UL> position;
        float size;

    public:
        Shape(blaze::StaticVector<float,2UL> position, float size, Surface *surface) 
        : position(position)
        , size(size)
        , surface(surface)
        {};

        virtual void draw() = 0;
        virtual bool isColliding(LightRay *ray) = 0;
        virtual bool isInside(LightRay *ray) = 0;
        virtual blaze::StaticVector<float,2UL> getNormal(blaze::StaticVector<float,2UL> rayPosition) = 0;
};

#endif