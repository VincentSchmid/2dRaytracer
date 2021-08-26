#ifndef Surface_h
#define Surface_h

#include "MathX.h"
#include <math.h>


struct Surface
{
    Surface(float reflectivity, float transmission, float diffuse, float (*dispersionFunction)(float))
    : reflectivity(reflectivity)
    , transmission(transmission)
    , diffuse(diffuse)
    , dispersionFunction(dispersionFunction)
    {
        MathX::Vector3 surfaceVector{reflectivity, transmission, diffuse};
        surfaceVector.Normalize();

        this->reflectivity = surfaceVector.X;
        this->transmission = surfaceVector.Y;
        this->diffuse = surfaceVector.Z;
    };

    float reflectivity;
    float transmission;
    float diffuse;
    float (*dispersionFunction)(float); // Cauchy's equation (Wavelength in micro meters)
};

struct Surface GLASS = {.40f, .90f, 0.0f, 
        [](float wavelength_um) -> float
        {
            // function from here https://refractiveindex.info/?shelf=3d&book=glass&page=soda-lime-clear
            return 1.5130f - 0.003169f * pow(wavelength_um, 2.0f) + 0.003962f * pow(wavelength_um, -2.0f);
        }
    };

    struct Surface CRAZY_GLASS = {0.0f, 1.0f, 0.0f, 
        [](float wavelength_um) -> float
        {
            // not realistic properties
            return 1.5130f - 0.006069f * pow(wavelength_um, 2.0f) + 0.008062f * pow(wavelength_um, -2.0f);
        }
    };

#endif