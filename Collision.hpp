#ifndef Ray_h
#define Ray_h

#include "Ray.h"

#endif

#ifndef MathX_h
#define MathX_h

#include "MathX.h"

#endif

#ifndef Shape_h
#define Shape_h

#include "Shape.hpp"

 #endif

#include <iostream>


class Collision
{
    private:
        std::list<LightRay> *rays;
        Shape *shape;
    
    public:
        Collision(std::list<LightRay> *rays, Shape *shape)
        : rays(rays)
        , shape(shape)
        {};

        void check();
};

void Collision::check()
{
    std::list<LightRay>::iterator it;
    for (it = rays->begin(); it != rays->end(); ++it)
    {
        if (shape->isColliding( &(*it) ))
        {
            shape->collide(&(*it));
        }
    }
}