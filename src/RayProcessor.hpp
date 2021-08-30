#ifndef RayProcessor_h
#define RayProcessor_h

#include "RayRenderer.hpp"
#include "Ray.hpp"

template<int N>
void step(RayRenderer<N> *renderer, LightRay *ray, float deltaTime)
{
    MathX::Vector2 delta_pos = ray->direction * (deltaTime / ray->refractionIndex);
    ray->position += delta_pos;

    ray->prevDirection = (ray->prevDirection != ray->direction) ? ray->direction : ray->prevDirection;
        
    renderer->addPosition(ray);

    ray->nextPosition = ray->position + delta_pos;
}

template<int N>
void step(RayRenderer<N> *renderer, std::vector<LightRay> *rays, float deltaTime)
{
    for (LightRay ray : *rays)
    {
        step(renderer, &ray, deltaTime);
    }
}

#endif