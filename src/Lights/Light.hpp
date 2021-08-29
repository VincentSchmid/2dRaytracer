#ifndef Light_h
#define Light_h

#include "MathX.h"

#include <list>


class Light
{
    public:
        MathX::Vector2 position;
        float intensity;
        int raycount;
        float refractiveIndex;
        std::list<LightRay> rays;
    
    public:
        Light(MathX::Vector2 position, float intensity, int raycount, float refractiveIndex)
        : position(position)
        , intensity(intensity)
        , raycount(raycount)
        , refractiveIndex(refractiveIndex)
        {};

    protected:
        void createRay(MathX::Vector2 position, MathX::Vector2 direction, float intensity, float refractiveIndex);
};

void Light::createRay(MathX::Vector2 position, MathX::Vector2 direction, float intensity, float refractiveIndex)
{
    std::list<LightRay> rayBundle = {};
    rayBundle = createRayBundle(direction, position, refractiveIndex, intensity);
    rays.insert(rays.end(), rayBundle.begin(), rayBundle.end());
}

#endif