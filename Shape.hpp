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
    float reflectivity;
    float transmission;
    MathX::Color color;
    float refractionIndex;
};


class Shape
{
    protected:
        Surface surface;
        MathX::Vector2 position;
        float size;

    public:
        Shape(MathX::Vector2 position, float size) 
        : position(position)
        , size(size)
        {};

        virtual void draw() = 0;
        virtual void collide(LightRay *ray) = 0;
        virtual bool isColliding(LightRay *ray) = 0;
};
