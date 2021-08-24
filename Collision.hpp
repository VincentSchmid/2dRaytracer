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

 #define CUTOFF 0.01f
 #define IOR_AIR 1.0f


class Collision
{
    public:
        std::list<LightRay> *rays;

    private:
        Shape *shape;
    
    public:
        Collision(std::list<LightRay> *rays, Shape *shape)
        : rays(rays)
        , shape(shape)
        {};

        void check();

    private:
        int collide(LightRay *ray, Shape *shape);
        LightRay* createNewRay(LightRay *ray);
};

void Collision::check()
{
    std::list<LightRay>::iterator it;
    for (it = rays->begin(); it != rays->end(); ++it)
    {
        if (shape->isColliding( &(*it) ))
        {
            collide(&(*it), shape);         
        }
    }
}

int Collision::collide(LightRay *ray, Shape *shape)
{
    int numNewRays = 0;
    MathX::Vector2 surfaceNormal = shape->getNormal(ray->position);

    if (shape->surface->reflectivity > CUTOFF && ray->intensity > CUTOFF)
    {
        LightRay *reflectedRay = createNewRay(ray);
        reflectedRay->intensity *= shape->surface->reflectivity;
        numNewRays++;
        reflect(reflectedRay, surfaceNormal);
    }

    /*
    if (shape->surface->diffuse > CUTOFF && ray->intensity > CUTOFF)
    {
        LightRay *scatteredRay = createNewRay(ray);
        scatteredRay->intensity *= shape->surface->diffuse;
        numNewRays++;
        scatter(scatteredRay, surfaceNormal, shape->surface->color);
    }
    */

    if (shape->surface->transmission > CUTOFF && ray->intensity > CUTOFF)
    {
        ray->intensity *= shape->surface->transmission;
        float refractionIndex = (shape->surface->dispersionFunction)(ray->wave_length_nm / 1000.0f);
        //PrintValue(refractionIndex, "Index of Refraction");
        refract(ray, surfaceNormal, shape->isInside(ray) ? IOR_AIR : refractionIndex);
    }

    //ray->direction = {0, 0};

    return numNewRays;
}

LightRay* Collision::createNewRay(LightRay *ray)
{
    rays->push_front({ray->direction, ray->position, ray->refractionIndex, ray->intensity, ray->wave_length_nm});
    return &(rays->front());
}
