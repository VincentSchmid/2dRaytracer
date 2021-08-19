#ifndef Shape_h
#define Shape_h

#include "Shape.hpp"

#endif

#ifndef rlgl_h
#define rlgl_h

#include "rlgl.h"

#endif

#ifndef helpers_h
#define helpers_h

#include "helpers.hpp"

#endif


class Circle : public Shape
{
    public:
        Circle(MathX::Vector2 position, float size, Surface *surface) 
        : Shape(position, size, surface) {};

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray);
        MathX::Vector2 getNormal(MathX::Vector2 rayPosition);

    private:
        bool collisionEnter(LightRay *ray);
        bool collisionExit(LightRay *ray);
};

void Circle::draw()
{
    DrawCircleCorrected(position.X, position.Y, size, toRayLibColor(surface->color));
}

MathX::Vector2 Circle::getNormal(MathX::Vector2 rayPosition)
{
    MathX::Vector2 normal = rayPosition - position;
    normal.Normalize();

    return normal;
}

bool Circle::collisionEnter(LightRay *ray)
{
    return ray->position.Distance(this->position) > size && ray->nextPosition.Distance(this->position) < size;
}

bool Circle::collisionExit(LightRay *ray)
{
    return ray->position.Distance(this->position) < size && ray->nextPosition.Distance(this->position) > size;
}

bool Circle::isInside(LightRay *ray)
{
    return getNormal(ray->position).Dot(ray->direction) > 0;
}

bool Circle::isColliding(LightRay *ray)
{
    return collisionEnter(ray) || collisionExit(ray);
}
