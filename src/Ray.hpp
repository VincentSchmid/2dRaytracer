#ifndef Ray_h
#define Ray_h

#include "MathX.h"
#include "helpers.hpp"
#include "wavelength_rgb.hpp"

#include <list>
#include <vector>

#define BUNDLE_SIZE 30


struct LightRay 
{
    LightRay(MathX::Vector2 direction, MathX::Vector2 position, float refractionIndex, float intensity, double wave_length_nm)
    : direction(direction)
    , position(position)
    , refractionIndex(refractionIndex)
    , intensity(intensity)
    , wave_length_nm(wave_length_nm)
    {
        direction.Normalize();
        nextPosition = position;
        prevDirection = direction;
        positions.assign(2, position);
        positions.reserve(6);
    }

    MathX::Vector2 direction; // also referred to as l
    MathX::Vector2 position; // refered to as p
    float refractionIndex; // refered to as ior or n
    float intensity;
    float wave_length_nm;
    MathX::Vector2 nextPosition;
    MathX::Vector2 prevDirection;
    std::vector<MathX::Vector2> positions;
};
    
void step(LightRay *ray, float deltaTime)
{
    MathX::Vector2 delta_pos = ray->direction * (deltaTime / ray->refractionIndex);
    ray->position += delta_pos;
    if (ray->prevDirection != ray->direction)
    {
        ray->prevDirection = ray->direction;
        ray->positions.push_back(ray->position);
    } else
    {
        ray->positions.pop_back();
        ray->positions.push_back(ray->position);
    }
    ray->nextPosition = ray->position + delta_pos;
}

void step(std::list<LightRay> *rays, float deltaTime)
{
    std::list<LightRay>::iterator it;

    for (it = rays->begin(); it != rays->end(); ++it)
    {
        step(&(*it), deltaTime);
    }
}

void drawRay(LightRay *ray)
{
    MathX::Vector2 prevPos = ray->positions.front();

    for (auto currPos : ray->positions)
    {
        DrawLineCorrected(prevPos.X, prevPos.Y, currPos.X, currPos.Y, waveLengthtoRayLibColor(ray->wave_length_nm, ray->intensity * 255.0f));
        prevPos = {currPos.X, currPos.Y};
    }
}

void drawRays(std::list<LightRay> *rays)
{
    for (LightRay ray : *rays)
    {
        drawRay(&ray);
    }
}

std::list<LightRay> createRayBundle(MathX::Vector2 direction, MathX::Vector2 position, float refractiveIndex, float intensity)
{
    std::list<LightRay> lightRays = {};

    for (size_t i = 0; i < BUNDLE_SIZE; i++)
    {
        double wavelegth = SHORTEST_VISIBLE_WAVELENGTH + (WAVELENTH_RANGE / BUNDLE_SIZE) * i;
        lightRays.push_front({direction, position, refractiveIndex, intensity / BUNDLE_SIZE, wavelegth});
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