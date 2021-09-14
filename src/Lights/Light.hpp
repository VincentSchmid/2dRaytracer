#ifndef Light_h
#define Light_h

#include "Vector2d.hpp"

#include <list>


class Light
{
    public:
        Vector2d position;
        float intensity;
        int rayCount;
        float refractiveIndex;
        std::list<LightRay> rays;
    
    public:
        Light(Vector2d position, float intensity, int rayCount, float refractiveIndex)
        : position(position)
        , intensity(intensity)
        , rayCount(rayCount)
        , refractiveIndex(refractiveIndex)
        {};

        virtual void castRays() = 0;

    protected:
        void createRay(Vector2d position, Vector2d direction, float intensity, float refractiveIndex);
};

void Light::createRay(Vector2d position, Vector2d direction, float intensity, float refractiveIndex)
{
    std::list<LightRay> rayBundle = {};
    rayBundle = createRayBundle(direction, position, refractiveIndex, intensity);
    rays.insert(rays.end(), rayBundle.begin(), rayBundle.end());
}

#endif