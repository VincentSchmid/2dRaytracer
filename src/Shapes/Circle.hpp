#ifndef Circle_h
#define Circle_h

#include "Shape.hpp"
#include "helpers.hpp"


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
    DrawCircleCorrected(position.X, position.Y, size, BLUE);
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

#endif