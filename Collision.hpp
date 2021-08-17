#ifndef Ray_h
#define Ray_h

#include "Ray.h"

#endif

#ifndef MathX_h
#define MathX_h

#include "MathX.h"

#endif

#include <iostream>


class Collision
{
    private:
        std::list<LightRay> *rays;
        Mirror *mirror;
    
    public:
        Collision(std::list<LightRay> *rays, Mirror *mirror)
        : rays(rays)
        , mirror(mirror)
        {};

        void check();
};

void Collision::check()
{
    std::list<LightRay>::iterator it;
    for (it = rays->begin(); it != rays->end(); ++it)
    {
        if (mirror->isColliding( &(*it) ))
        {
            mirror->collide(&(*it));
        }
    }
}