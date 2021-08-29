#ifndef pointLight_h
#define pointLight_h

#include "MathX.h"
#include "Ray.hpp"

#include <math.h>

class PointLight : public Light
{
    public:
        PointLight(MathX::Vector2 position, float intensity, int rayCount, float refractiveIndex)
        : Light(position, intensity, rayCount, refractiveIndex)
        {
            std::list<LightRay> rayBundle = {};
            MathX::Vector2 direction;
            float deltaAngle = 2.0f * PI / rayCount;

            for (int i = 0; i < rayCount; i++)
            {
                direction.X = cos(deltaAngle * i);
                direction.Y = sin(deltaAngle * i);

                createRay(position, direction, intensity, refractiveIndex);
            }
        };

        PointLight(MathX::Vector2 position, float intensity, int raycount)
        : PointLight(position, intensity, raycount, 1.0f){};

        PointLight(MathX::Vector2 position, int raycount)
        : PointLight(position, 1.0f, raycount, 1.0f){};
};

#endif 