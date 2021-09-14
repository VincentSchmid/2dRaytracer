#ifndef Circle_h
#define Circle_h

#include "Shape.hpp"
#include "helpers.hpp"

#include <blaze/Blaze.h>


class Circle : public Shape
{
    public:
        Circle(blaze::StaticVector<float,2UL> position, float size, Surface *surface) 
        : Shape(position, size, surface) {};

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray);
        blaze::StaticVector<float,2UL> getNormal(blaze::StaticVector<float,2UL> rayPosition);

    private:
        bool collisionEnter(LightRay *ray);
        bool collisionExit(LightRay *ray);
};

void Circle::draw()
{
    DrawCircleCorrected(position[0], position[1], size, BLUE);
}

blaze::StaticVector<float,2UL> Circle::getNormal(blaze::StaticVector<float,2UL> rayPosition)
{
    blaze::StaticVector<float,2UL> normal = rayPosition - position;
    normal = blaze::normalize(normal);

    return normal;
}

bool Circle::collisionEnter(LightRay *ray)
{
    return blaze::sqrNorm(ray->position - this->position) > (size * size) && blaze::sqrNorm(ray->nextPosition - this->position) < (size * size);
}

bool Circle::collisionExit(LightRay *ray)
{
    return blaze::sqrNorm(ray->position - this->position) < (size * size) && blaze::sqrNorm(ray->nextPosition - this->position) > (size * size);
}

bool Circle::isInside(LightRay *ray)
{
    return blaze::dot(getNormal(ray->position), ray->direction) > 0;
}

bool Circle::isColliding(LightRay *ray)
{
    return collisionEnter(ray) || collisionExit(ray);
}

#endif