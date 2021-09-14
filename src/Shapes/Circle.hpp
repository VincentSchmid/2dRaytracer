#ifndef Circle_h
#define Circle_h

#include "Shape.hpp"
#include "helpers.hpp"
#include "Vector2d.hpp"


class Circle : public Shape
{
    public:
        Circle(Vector2d position, float size, Surface *surface) 
        : Shape(position, size, surface) {};

        void draw();
        bool isColliding(LightRay *ray);
        bool isInside(LightRay *ray);
        Vector2d getNormal(Vector2d rayPosition);

    private:
        bool collisionEnter(LightRay *ray);
        bool collisionExit(LightRay *ray);
};

void Circle::draw()
{
    DrawCircleCorrected(position.x, position.y, size, BLUE);
}

Vector2d Circle::getNormal(Vector2d rayPosition)
{
    Vector2d normal = rayPosition - position;
    return Normalize(normal);
}

bool Circle::collisionEnter(LightRay *ray)
{
    return Distance(ray->position, this->position) > size && Distance(ray->nextPosition, this->position) < size;
}

bool Circle::collisionExit(LightRay *ray)
{
    return Distance(ray->position, this->position) < size && Distance(ray->nextPosition, this->position) > size;
}

bool Circle::isInside(LightRay *ray)
{
    return Dot(getNormal(ray->position), ray->direction) > 0;
}

bool Circle::isColliding(LightRay *ray)
{
    return collisionEnter(ray) || collisionExit(ray);
}

#endif