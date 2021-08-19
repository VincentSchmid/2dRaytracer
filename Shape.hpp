#ifndef MathX_h
#define MathX_h

#include "MathX.h"

#endif

#ifndef Ray_h
#define Ray_h

#include "Ray.h"

#endif


struct Surface
{
    Surface(float reflectivity, float transmission, float diffuse, float refractionIndex, MathX::Color color)
    : refractionIndex(refractionIndex)
    , color(color)
    , reflectivity(reflectivity)
    , transmission(transmission)
    , diffuse(diffuse)
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
    float refractionIndex;
    MathX::Color color;
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
