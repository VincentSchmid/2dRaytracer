#ifndef raylib_h
#define raylib_h

#include "raylib.h"

#endif

#ifndef MathX_h
#define MathX_h

#include "MathX.h"

#endif

#ifndef list_h
#define list_h

#include <list>

#endif

#ifndef helpers_h
#define helpers_h

#include "helpers.hpp"

#endif


struct LightRay 
{
    LightRay(MathX::Vector2 direction, MathX::Vector2 position, float refractionIndex)
    : direction(direction)
    , position(position)
    , refractionIndex(refractionIndex)
    {
        direction.Normalize();
        nextPosition = position;
        prevDirection = direction;
        positions = { position, position };
    }

    MathX::Vector2 direction; // also referred to as l
    MathX::Vector2 position; // refered to as p
    float refractionIndex; // refered to as ior or n
    MathX::Vector2 nextPosition;
    MathX::Vector2 prevDirection;
    std::list<MathX::Vector2> positions;
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

    std::list<MathX::Vector2>::iterator it;

    for (it = std::next(ray->positions.begin()); it != ray->positions.end(); ++it)
    {
        DrawLineCorrected(prevPos.X, prevPos.Y, it->X, it->Y, WHITE);
        prevPos = {it->X, it->Y};
    }
}

void drawRays(std::list<LightRay> *rays)
{
    std::list<LightRay>::iterator it;

    for (it = rays->begin(); it != rays->end(); ++it)
    {
        drawRay(&(*it));
    }
}

std::list<LightRay> getDirectionalLightRays(Vector2 position, int width, Vector2 direction, int rayCount, float refractionIndex)
{
    std::list<LightRay> lightRays = {};
    MathX::Vector2 pos{position.x, position.y};
    MathX::Vector2 dir{direction.x, direction.y};

    float spacing = 1.0f * width / rayCount;
    int isOdd = rayCount % 2;

    dir.Normalize();
    MathX::Vector2 left = dir.PerpendicularCounterClockwise();
    MathX::Vector2 right = dir.PerpendicularClockwise();
    
    for (size_t i = 0; i < isOdd; i++)
    {
        lightRays.push_front({dir, pos, refractionIndex});
    }
    
    for (int i = 0; i < (rayCount - isOdd) / 2; i++)
    {
        lightRays.push_front({dir, pos + (left * spacing * (1.0f + i)), refractionIndex});
        lightRays.push_front({dir, pos + (right * spacing * (1.0f + i)), refractionIndex});
    }
        
    return lightRays;
}

void reflect(LightRay *ray, MathX::Vector2 normal)
{
    ray->prevDirection = ray->direction;
    ray->direction -= 2 * ray->direction.Dot(normal) * normal;
    ray->direction.Normalize();
}

void refract(LightRay *ray, MathX::Vector2 normal, float refractionIndex1, float refractionIndex2)
{
    float roi = refractionIndex1 / refractionIndex2;
    ray->prevDirection = ray->direction;
    float c = normal.Dot(ray->direction);

    float d = 1.0f - roi * roi * (1.0f - c * c);

    // Total Internal Reflection
    // Angle of ray is too shallow to exit medium
    if (d < 0)
    {
        reflect(ray, -normal);
    } else
    {
        // if the ray is inside the lense the normal needs to be reversed for the direction calculation
        float normal_direction = c > 0 ? -1.0f : 1.0f;

        ray->direction = roi * ray->direction + (roi * c - sqrt(d)) * (normal_direction * normal);
        ray->direction.Normalize();
        ray->refractionIndex = refractionIndex2;
    }
}
