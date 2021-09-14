#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Linalg.hpp"
#include "Ray.hpp"

#include <blaze/Blaze.h>
#include <list>


class DirectionalLight : public Light
{
    private:
        blaze::StaticVector<float,2UL> direction;
        float width;

    public:
        DirectionalLight(blaze::StaticVector<float,2UL> position, blaze::StaticVector<float,2UL> direction, float intensity, float refractiveIndex, float width, int rayCount)
        : Light(position, intensity, rayCount, refractiveIndex)
        , direction(direction)
        , width(width)
        {
            castRays();
        };

        DirectionalLight(blaze::StaticVector<float,2UL> position, blaze::StaticVector<float,2UL> direction, float intensity, float width, int rayCount)
        : DirectionalLight(position, direction, intensity, 1.0f, width, rayCount)
        {};

        DirectionalLight(blaze::StaticVector<float,2UL> position, blaze::StaticVector<float,2UL> direction, float width, int rayCount)
        : DirectionalLight(position, direction, 1.0f, 1.0f, width, rayCount)
        {};

        void castRays();
};

void DirectionalLight::castRays()
{
    rays = {};
    std::list<LightRay> rayBundle = {};
    
    std::list<blaze::StaticVector<float,2UL>> vectors = getPointsAlongLine(position, direction, width, rayCount, true);
    
    for (blaze::StaticVector<float,2UL> vector : vectors)
    {
        createRay(vector, direction, intensity, refractiveIndex);
    }
}

#endif