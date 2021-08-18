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
    float roi1, roi2;
    MathX::Vector2 nrml = ray->position - position;
    nrml.Normalize();

    if (nrml.Dot(ray->direction) > 0)
    {
        // entering
        roi1 = 1.0f;
        roi2 = 1.4f;
    } else
    {
        /*
        PrintVector(ray->position, "ray_pos");
        PrintVector(ray->direction, "ray_dir");
        PrintVector(position, "lense pos");
        PrintVector(nrml, "surface normal");
        */

       // exiting
        roi1 = 1.4f;
        roi2 = 1.0f;
    }
    
    refract(ray, nrml, roi1, roi2);
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
