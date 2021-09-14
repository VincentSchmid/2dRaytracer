#ifndef Ray_h
#define Ray_h

#include "helpers.hpp"
#include "wavelength_rgb.hpp"

#include "Vector2d.hpp"

#include <list>
#include <vector>

#define BUNDLE_SIZE 30


struct LightRay 
{
    LightRay(Vector2d direction, Vector2d position, float refractionIndex, float intensity, double wave_length_nm, unsigned int bounceCount)
    : direction(direction)
    , position(position)
    , refractionIndex(refractionIndex)
    , intensity(intensity)
    , wave_length_nm(wave_length_nm)
    , bounceCount(bounceCount)
    {
        direction = Normalize(direction);
        nextPosition = position;
        prevDirection = direction;
    }

    Vector2d direction; // also referred to as l
    Vector2d position; // refered to as p
    float refractionIndex; // refered to as ior or n
    float intensity;
    float wave_length_nm;
    unsigned int bounceCount : 4;
    Vector2d nextPosition;
    Vector2d prevDirection;
};

std::list<LightRay> createRayBundle(Vector2d direction, Vector2d position, float refractiveIndex, float intensity)
{
    std::list<LightRay> lightRays = {};

    for (size_t i = 0; i < BUNDLE_SIZE; i++)
    {
        double wavelegth = SHORTEST_VISIBLE_WAVELENGTH + (WAVELENTH_RANGE / BUNDLE_SIZE) * i;
        lightRays.push_front({direction, position, refractiveIndex, intensity / BUNDLE_SIZE, wavelegth, 0});
    }
    
    return lightRays;
}

void reflect(LightRay *ray, Vector2d normal)
{
    ray->prevDirection = ray->direction;
    ray->direction -= 2 * Dot(ray->direction, normal) * normal;
    Normalize(ray->direction);
}

void refract(LightRay *ray, Vector2d normal, float refractionIndex2)
{
    float roi = ray->refractionIndex / refractionIndex2;
    ray->prevDirection = ray->direction;

    if (-Dot(ray->direction, normal) < 0)
    {
        normal = -normal;
    }

    float c = -Dot(ray->direction, normal);

    float d = 1.0f - roi * roi * (1.0f - c * c);

    // Total Internal Reflection
    // Angle of ray is too shallow to exit medium
    if (d < 0)
    {
        reflect(ray, -normal);
    } else
    {
        ray->direction = roi * ray->direction + (roi * c - sqrt(d)) * normal;
        Normalize(ray->direction);
        ray->refractionIndex = refractionIndex2;
    }
}

void scatter(LightRay *ray, Vector2d normal, MathX::Color surfaceColor)
{
    ray->prevDirection = ray->direction;
    ray->direction = Zero();
}

#endif