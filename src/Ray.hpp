#ifndef Ray_h
#define Ray_h

#include "helpers.hpp"
#include "wavelength_rgb.hpp"

#include <blaze/Blaze.h>

#include <list>
#include <vector>

#define BUNDLE_SIZE 30


struct LightRay 
{
    LightRay(blaze::StaticVector<float,2UL> direction, blaze::StaticVector<float,2UL> position, float refractionIndex, float intensity, double wave_length_nm, unsigned int bounceCount)
    : direction(direction)
    , position(position)
    , refractionIndex(refractionIndex)
    , intensity(intensity)
    , wave_length_nm(wave_length_nm)
    , bounceCount(bounceCount)
    {
        direction = blaze::normalize(direction);
        nextPosition = position;
        prevDirection = direction;
    }

    blaze::StaticVector<float,2UL> direction; // also referred to as l
    blaze::StaticVector<float,2UL> position; // refered to as p
    float refractionIndex; // refered to as ior or n
    float intensity;
    float wave_length_nm;
    unsigned int bounceCount : 4;
    blaze::StaticVector<float,2UL> nextPosition;
    blaze::StaticVector<float,2UL> prevDirection;
};

std::list<LightRay> createRayBundle(blaze::StaticVector<float,2UL> direction, blaze::StaticVector<float,2UL> position, float refractiveIndex, float intensity)
{
    std::list<LightRay> lightRays = {};

    for (size_t i = 0; i < BUNDLE_SIZE; i++)
    {
        double wavelegth = SHORTEST_VISIBLE_WAVELENGTH + (WAVELENTH_RANGE / BUNDLE_SIZE) * i;
        lightRays.push_front({direction, position, refractiveIndex, intensity / BUNDLE_SIZE, wavelegth, 0});
    }
    
    return lightRays;
}

void reflect(LightRay *ray, blaze::StaticVector<float,2UL> normal)
{
    ray->prevDirection = ray->direction;
    ray->direction -= 2 * blaze::dot(ray->direction, normal) * normal;
    ray->direction = blaze::normalize(ray->direction);
}

void refract(LightRay *ray, blaze::StaticVector<float,2UL> normal, float refractionIndex2)
{
    float roi = ray->refractionIndex / refractionIndex2;
    ray->prevDirection = ray->direction;

    if (blaze::dot(-ray->direction, normal) < 0)
    {
        normal = -normal;
    }
    float c = blaze::dot(-ray->direction, normal);

    float d = 1.0f - roi * roi * (1.0f - c * c);

    // Total Internal Reflection
    // Angle of ray is too shallow to exit medium
    if (d < 0)
    {
        reflect(ray, -normal);
    } else
    {
        ray->direction = roi * ray->direction + (roi * c - sqrt(d)) * normal;
        ray->direction = blaze::normalize(ray->direction);

        ray->refractionIndex = refractionIndex2;
    }
}

void scatter(LightRay *ray, blaze::StaticVector<float,2UL> normal, MathX::Color surfaceColor)
{
    ray->prevDirection = ray->direction;
    ray->direction = blaze::zero<float>(2UL);
}

#endif