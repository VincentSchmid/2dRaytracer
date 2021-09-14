#ifndef pointLight_h
#define pointLight_h

#include "Ray.hpp"

#include <blaze/Blaze.h>
#include <math.h>

class PointLight : public Light
{
    public:
        PointLight(blaze::StaticVector<float,2UL> position, float intensity, int rayCount, float refractiveIndex)
        : Light(position, intensity, rayCount, refractiveIndex)
        {
            std::list<LightRay> rayBundle = {};
            blaze::StaticVector<float,2UL> direction;
            float deltaAngle = 2.0f * PI / rayCount;

            for (int i = 0; i < rayCount; i++)
            {
                direction[0] = cos(deltaAngle * i);
                direction[1] = sin(deltaAngle * i);

                createRay(position, direction, intensity, refractiveIndex);
            }
        };

        PointLight(blaze::StaticVector<float,2UL> position, float intensity, int raycount)
        : PointLight(position, intensity, raycount, 1.0f){};

        PointLight(blaze::StaticVector<float,2UL> position, int raycount)
        : PointLight(position, 1.0f, raycount, 1.0f){};
};

#endif 