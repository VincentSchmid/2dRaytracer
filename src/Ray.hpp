#ifndef Ray_h
#define Ray_h

#include "helpers.hpp"
#include "wavelength_rgb.hpp"

#include "MathX.h"

#include <list>
#include <vector>

#define BUNDLE_SIZE 30


struct LightRay 
{
    LightRay(MathX::Vector2 direction, MathX::Vector2 position, float refractionIndex, float intensity, double wave_length_nm, unsigned int bounceCount)
    : direction(direction)
    , position(position)
    , refractionIndex(refractionIndex)
    , intensity(intensity)
    , wave_length_nm(wave_length_nm)
    , bounceCount(bounceCount)
    {
        direction.Normalize();
        nextPosition = position;
        prevDirection = direction;
    }

    MathX::Vector2 direction; // also referred to as l
    MathX::Vector2 position; // refered to as p
    float refractionIndex; // refered to as ior or n
    float intensity;
    float wave_length_nm;
    unsigned int bounceCount : 4;
    MathX::Vector2 nextPosition;
    MathX::Vector2 prevDirection;
};

std::list<LightRay> createRayBundle(MathX::Vector2 direction, MathX::Vector2 position, float refractiveIndex, float intensity)
{
    std::list<LightRay> lightRays = {};

    for (size_t i = 0; i < BUNDLE_SIZE; i++)
    {
        double wavelegth = SHORTEST_VISIBLE_WAVELENGTH + (WAVELENTH_RANGE / BUNDLE_SIZE) * i;
        lightRays.push_front({direction, position, refractiveIndex, intensity / BUNDLE_SIZE, wavelegth, 0});
    }
    
    return lightRays;
}

void reflect(LightRay *ray, MathX::Vector2 normal)
{
    ray->prevDirection = ray->direction;
    ray->direction -= 2 * ray->direction.Dot(normal) * normal;
    ray->direction.Normalize();
}

void refract(LightRay *ray, MathX::Vector2 normal, float refractionIndex2)
{
    float roi = ray->refractionIndex / refractionIndex2;
    ray->prevDirection = ray->direction;

    if (-ray->direction.Dot(normal) < 0)
    {
        normal = -normal;
    }

    float c = -ray->direction.Dot(normal);

    float d = 1.0f - roi * roi * (1.0f - c * c);

    // Total Internal Reflection
    // Angle of ray is too shallow to exit medium
    if (d < 0)
    {
        reflect(ray, -normal);
    } else
    {
        ray->direction = roi * ray->direction + (roi * c - sqrt(d)) * normal;
        ray->direction.Normalize();
        ray->refractionIndex = refractionIndex2;
    }
}

void scatter(LightRay *ray, MathX::Vector2 normal, MathX::Color surfaceColor)
{
    ray->prevDirection = ray->direction;
    ray->direction.Zero();
}

#endif