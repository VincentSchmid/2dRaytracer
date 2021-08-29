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
};

#endif