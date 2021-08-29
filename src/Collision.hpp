#ifndef Collision_h
#define Collision_h

#include "Ray.hpp"
#include <Shapes/Shape.hpp>
#include <Lights/Light.hpp>
#include "RayRenderer.hpp"

#include "MathX.h"


#define CUTOFF 0.01f
#define IOR_AIR 1.0f

template<int N>
class Collision
{
    public:
        std::list<LightRay> rays;

    private:
        std::list<Shape*> shapes;
        unsigned int maxBounces;
        RayRenderer<N> *renderer;
    
    public:
        Collision(RayRenderer<N> *renderer, Light source, std::list<Shape*> shapes, unsigned int maxBounces)
        : renderer(renderer)
        , rays(source.rays)
        , shapes(shapes)
        , maxBounces(maxBounces)
        {};

        void check();

    private:
        int collide(LightRay *ray, Shape *shape);
        LightRay* createNewRay(LightRay *ray);
};

template<int N>
void Collision<N>::check()
{
    std::list<LightRay>::iterator it;
    std::list<Shape*>::iterator itShape;

    for (it = rays.begin(); it != rays.end(); ++it)
    {
        for (itShape = shapes.begin(); itShape != shapes.end(); ++itShape)
        {
            if ((*itShape)->isColliding( &(*it) ))
            {
                collide(&(*it), (*itShape));         
            }
        }
    }
}

template<int N>
int Collision<N>::collide(LightRay *ray, Shape *shape)
{
    int numNewRays = 0;
    ray->bounceCount++;

    MathX::Vector2 surfaceNormal = shape->getNormal(ray->position);

    if (ray->bounceCount < maxBounces && ray->intensity > CUTOFF)
    {
        if (shape->surface->reflectivity > CUTOFF)
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

        if (shape->surface->transmission > CUTOFF)
        {
            ray->intensity *= shape->surface->transmission;
            float refractionIndex = (shape->surface->dispersionFunction)(ray->wave_length_nm / 1000.0f);
            //PrintValue(refractionIndex, "Index of Refraction");
            refract(ray, surfaceNormal, shape->isInside(ray) ? IOR_AIR : refractionIndex);
        }

    } else
    {
        ray->direction = {0, 0};
    }

    return numNewRays;
}

template<int N>
LightRay* Collision<N>::createNewRay(LightRay *ray)
{
    rays.push_front({ray->direction, ray->position, ray->refractionIndex, ray->intensity, ray->wave_length_nm, ray->bounceCount});
    renderer->addRay( &(rays.front()) );
    return &(rays.front());
}

#endif