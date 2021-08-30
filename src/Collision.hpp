#ifndef Collision_h
#define Collision_h

#include "Ray.hpp"
#include "Shape.hpp"
#include "RayRenderer.hpp"

#include "MathX.h"

#include <vector>

#define CUTOFF 0.01f
#define IOR_AIR 1.0f

template<int N>
class Collision
{
    public:
        std::vector<LightRay> rays;

    private:
        std::list<Shape*> shapes;
        int maxBounces;
        RayRenderer<N> *renderer;
    
    public:
        Collision(RayRenderer<N> *renderer, std::vector<LightRay> rays, std::list<Shape*> shapes, int maxBounces)
        : rays(rays)
        , shapes(shapes)
        , renderer(renderer)
        , maxBounces(maxBounces)
        {
            rays.reserve(10000);
        };

        void check();

    private:
        int collide(LightRay *ray, Shape *shape);
        LightRay* createNewRay(const LightRay *ray);
};

template<int N>
void Collision<N>::check()
{
    std::vector<LightRay>::size_type oldSize = rays.size();
    std::list<Shape*>::iterator itShape;

    //#pragma omp parallel
    //#pragma omp single
    //{
        for (auto i = 0; i < oldSize; i++)
        {
            for (itShape = shapes.begin(); itShape != shapes.end(); ++itShape)
            {
                if ((*itShape)->isColliding( &rays[i] ))
                {
                    //#pragma omp task firstprivate(it)
                    collide(&rays[i], (*itShape));
                }
            }
        }
    //#pragma omp taskwait
    //}
}

template<int N>
int Collision<N>::collide(LightRay *ray, Shape *shape)
{
    int numNewRays = 0;
    ray->bounceCount++;

    MathX::Vector2 surfaceNormal = shape->getNormal(ray->position);

    if (ray->bounceCount <= maxBounces && ray->intensity > CUTOFF)
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
LightRay* Collision<N>::createNewRay(const LightRay *ray)
{
    rays.push_back({ray->direction, ray->position, ray->refractionIndex, ray->intensity, ray->wave_length_nm});
    renderer->addRay(&rays.back());
    return &rays.back();
}

#endif