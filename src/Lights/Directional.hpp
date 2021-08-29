#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Linalg.hpp"
#include "Ray.hpp"
#include "MathX.h"

#include <list>


class DirectionalLight : public Light
{
    private:
        MathX::Vector2 direction;
        float width;

    public:
        DirectionalLight(MathX::Vector2 position, MathX::Vector2 direction, float intensity, float refractionIndex, float width, int rayCount)
        : Light(position, intensity, rayCount, refractionIndex)
        , direction(direction)
        , width(width)
        {
            std::list<LightRay> rayBundle = {};
            std::list<MathX::Vector2> vectors = getPointsAlongLine(position, direction, width, rayCount);
            
            for (MathX::Vector2 vector : vectors)
            {
                rayBundle = createRayBundle(direction, vector, refractionIndex, intensity);
                rays.insert(rays.end(), rayBundle.begin(), rayBundle.end());
            }
        };

        DirectionalLight(MathX::Vector2 position, MathX::Vector2 direction, float intensity, float width, int rayCount)
        : DirectionalLight(position, direction, intensity, 1.0f, width, rayCount)
        {};

        DirectionalLight(MathX::Vector2 position, MathX::Vector2 direction, float width, int rayCount)
        : DirectionalLight(position, direction, 1.0f, 1.0f, width, rayCount)
        {};
};

#endif