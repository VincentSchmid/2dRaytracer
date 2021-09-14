#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Linalg.hpp"
#include "Ray.hpp"
#include "Vector2d.hpp"

#include <list>


class DirectionalLight : public Light
{
    private:
        Vector2d direction;
        float width;

    public:
        DirectionalLight(Vector2d position, Vector2d direction, float intensity, float refractiveIndex, float width, int rayCount)
        : Light(position, intensity, rayCount, refractiveIndex)
        , direction(direction)
        , width(width)
        {
            castRays();
        };

        DirectionalLight(Vector2d position, Vector2d direction, float intensity, float width, int rayCount)
        : DirectionalLight(position, direction, intensity, 1.0f, width, rayCount)
        {};

        DirectionalLight(Vector2d position, Vector2d direction, float width, int rayCount)
        : DirectionalLight(position, direction, 1.0f, 1.0f, width, rayCount)
        {};

        void castRays();
};

void DirectionalLight::castRays()
{
    rays = {};
    std::list<LightRay> rayBundle = {};
    
    std::list<Vector2d> vectors = getPointsAlongLine(position, direction, width, rayCount, true);
    
    for (Vector2d vector : vectors)
    {
        createRay(vector, direction, intensity, refractiveIndex);
    }
}

#endif