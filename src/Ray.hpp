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
        positions = { position, position };
    }

    MathX::Vector2 direction; // also referred to as l
    MathX::Vector2 position; // refered to as p
    float refractionIndex; // refered to as ior or n
    float intensity;
    float wave_length_nm;
    MathX::Vector2 nextPosition;
    MathX::Vector2 prevDirection;
    std::list<MathX::Vector2> positions;
};
    
void step(LightRay &ray, float deltaTime)
{
    MathX::Vector2 delta_pos = ray.direction * (deltaTime / ray.refractionIndex);
    ray.position += delta_pos;
    if (ray.prevDirection != ray.direction)
    {
        ray.prevDirection = ray.direction;
        ray.positions.push_back(ray.position);
    } else
    {
        ray.positions.pop_back();
        ray.positions.push_back(ray.position);
    }
    ray.nextPosition = ray.position + delta_pos;
}

void step(std::vector<LightRay> &rays, float deltaTime)
{
    for (auto i = 0; i < rays.size(); i++)
    {
        step(rays[i], deltaTime);
    }
}

void drawRay(LightRay &ray)
{
    MathX::Vector2 prevPos = ray.positions.front();

    for(MathX::Vector2 pos : ray.positions)
    {
        DrawLineCorrected(prevPos.X, prevPos.Y, pos.X, pos.Y, waveLengthtoRayLibColor(ray.wave_length_nm, ray.intensity * 255.0f));
        prevPos = {pos.X, pos.Y};
    }
}

void drawRays(std::vector<LightRay> &rays)
{
    std::vector<LightRay>::size_type oldSize = rays.size();

    for (auto i = 0; i < oldSize; i++)
    {
        drawRay(rays[i]);
    }
}

std::vector<LightRay> createRayBundle(MathX::Vector2 direction, MathX::Vector2 position, float refractiveIndex, float intensity)
{
    std::vector<LightRay> lightRays = {};
    lightRays.reserve(BUNDLE_SIZE);

    for (size_t i = 0; i < BUNDLE_SIZE; i++)
    {
        double wavelegth = SHORTEST_VISIBLE_WAVELENGTH + (WAVELENTH_RANGE / BUNDLE_SIZE) * i;
        lightRays.push_back({direction, position, refractiveIndex, intensity / BUNDLE_SIZE, wavelegth});
    }
    
    return lightRays;
}

std::vector<LightRay> getDirectionalLightRays(Vector2 position, int width, Vector2 direction, int rayCount, float refractionIndex)
{
    std::vector<LightRay> rayBundle = {};
    std::vector<LightRay> lightRays = {};
    lightRays.reserve(BUNDLE_SIZE * rayCount);
    MathX::Vector2 pos{position.x, position.y};
    MathX::Vector2 dir{direction.x, direction.y};

    float spacing = 1.0f * width / rayCount;
    int isOdd = rayCount % 2;

    dir.Normalize();
    MathX::Vector2 left = dir.PerpendicularCounterClockwise();
    MathX::Vector2 right = dir.PerpendicularClockwise();
    
    for (size_t i = 0; i < isOdd; i++)
    {
        rayBundle = createRayBundle(dir, pos, refractionIndex, 1.0f);
        lightRays.insert(lightRays.end(), rayBundle.begin(), rayBundle.end());
    }
    
    for (int i = 0; i < (rayCount - isOdd) / 2; i++)
    {
        rayBundle = createRayBundle(dir, pos + (left * spacing * (1.0f + i)), refractionIndex, 1.0f);
        lightRays.insert(lightRays.end(), rayBundle.begin(), rayBundle.end());

        rayBundle = createRayBundle(dir, pos + (right * spacing * (1.0f + i)), refractionIndex, 1.0f);
        lightRays.insert(lightRays.end(), rayBundle.begin(), rayBundle.end());
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