#ifndef MathX_h
#define MathX_h

#include "MathX.h"

#endif

#ifndef Ray_h
#define Ray_h

#include "Ray.hpp"

#endif


struct Surface
{
    Surface(float reflectivity, float transmission, float diffuse, float (*dispersionFunction)(float))
    : reflectivity(reflectivity)
    , transmission(transmission)
    , diffuse(diffuse)
    , dispersionFunction(dispersionFunction)
    {
        MathX::Vector3 surfaceVector{reflectivity, transmission, diffuse};
        surfaceVector.Normalize();

        this->reflectivity = surfaceVector.X;
        this->transmission = surfaceVector.Y;
        this->diffuse = surfaceVector.Z;
    };

    float reflectivity;
    float transmission;
    float diffuse;
    float (*dispersionFunction)(float); // Cauchy's equation (Wavelength in micro meters)
};


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
