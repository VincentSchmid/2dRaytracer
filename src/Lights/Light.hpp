#ifndef Light_h
#define Light_h

#include <blaze/Blaze.h>
#include <list>


class Light
{
    public:
        blaze::StaticVector<float,2UL> position;
        float intensity;
        int rayCount;
        float refractiveIndex;
        std::list<LightRay> rays;
    
    public:
        Light(blaze::StaticVector<float,2UL> position, float intensity, int rayCount, float refractiveIndex)
        : position(position)
        , intensity(intensity)
        , rayCount(rayCount)
        , refractiveIndex(refractiveIndex)
        {};

        virtual void castRays() = 0;

    protected:
        void createRay(blaze::StaticVector<float,2UL> position, blaze::StaticVector<float,2UL> direction, float intensity, float refractiveIndex);
};

void Light::createRay(blaze::StaticVector<float,2UL> position, blaze::StaticVector<float,2UL> direction, float intensity, float refractiveIndex)
{
    std::list<LightRay> rayBundle = {};
    rayBundle = createRayBundle(direction, position, refractiveIndex, intensity);
    rays.insert(rays.end(), rayBundle.begin(), rayBundle.end());
}

#endif