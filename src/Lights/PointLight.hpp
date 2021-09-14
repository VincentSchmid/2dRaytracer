#ifndef pointLight_h
#define pointLight_h

#include "Vector2d.hpp"
#include "Ray.hpp"

#include <math.h>

class PointLight : public Light
{
    public:
        PointLight(Vector2d position, float intensity, int rayCount, float refractiveIndex)
        : Light(position, intensity, rayCount, refractiveIndex)
        {
            std::list<LightRay> rayBundle = {};
            float deltaAngle = 2.0f * PI / rayCount;

            for (int i = 0; i < rayCount; i++)
            {
                Vector2d direction( cos(deltaAngle * i), sin(deltaAngle * i) );

                createRay(position, direction, intensity, refractiveIndex);
            }
        };

        PointLight(Vector2d position, float intensity, int raycount)
        : PointLight(position, intensity, raycount, 1.0f){};

        PointLight(Vector2d position, int raycount)
        : PointLight(position, 1.0f, raycount, 1.0f){};
};

#endif 