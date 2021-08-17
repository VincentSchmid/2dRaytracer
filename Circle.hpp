#ifndef Shape_h
#define Shape_h

#include "Shape.hpp"

#endif

#ifndef rlgl_h
#define rlgl_h

#include "rlgl.h"

#endif


class Circle : public Shape
{
    public:
        Circle(MathX::Vector2 position, float size) 
        : Shape(position, size) {};

        void draw();
        void collide(LightRay *ray);
        bool isColliding(LightRay *ray);

    private:
        bool collisionEnter(LightRay *ray);
        bool collisionExit(LightRay *ray);
};

void Circle::draw()
{
    DrawCircleCorrected(position.X, position.Y, size, BLUE);
}

void Circle::collide(LightRay *ray)
{
    float roi;
    MathX::Vector2 nrml;

    if (collisionEnter(ray))
    {
        roi = 1.49f;
        nrml = ray->position - position;
    } else
    {
        roi = 1.0f;
        nrml = position - ray->position;
    }
    
    nrml.Normalize();
    refract(ray, nrml, roi);
}

bool Circle::collisionEnter(LightRay *ray)
{
    return ray->position.Distance(this->position) > size && ray->nextPosition.Distance(this->position) < size;
}

bool Circle::collisionExit(LightRay *ray)
{
    return ray->position.Distance(this->position) < size && ray->nextPosition.Distance(this->position) > size;
}

bool Circle::isColliding(LightRay *ray)
{
    return collisionEnter(ray) || collisionExit(ray);
}
