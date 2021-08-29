#ifndef RayRenderer_h
#define RayRenderer_h

#include "Ray.hpp"

#include "raylib.h"

#include <vector>
#include <array>
#include <list>
#include <unordered_map>
#include <cstdint>


struct rayMoment
{
    unsigned char alpha;
    Vector2 position;
};

template<int N>
struct rayEntry
{
    unsigned int bounces : 4;
    int wave_length_nm;
    std::array<rayMoment, N> moments;
};

class myequal {
public:
   bool operator()(const uintptr_t pntr1, const uintptr_t pntr2) const{
      return pntr1 == pntr2;
   }
};

template<int N>
class RayRenderer
{
    private:
        std::unordered_map<LightRay *, rayEntry<N> *> entryReferences;
        std::vector<rayEntry<N>> rays;

    public:
        RayRenderer(){};
        void addRay(LightRay *ray);
        void addRays(std::list<LightRay> *rays);
        void addPosition(LightRay *ray);
        void drawRays();
};

template<int N>
void RayRenderer<N>::addRay(LightRay *ray)
{
    Vector2 position = {ray->position.X, ray->position.Y};
    rayMoment newMoment{ray->intensity * 255, position};
    rayEntry<N> newEntry{ ray->bounceCount, ray->wave_length_nm, {newMoment, newMoment} };
    rays.push_back(newEntry);

    auto test = &rays.back();

    entryReferences.insert( {ray, &rays.back()} );
}

template<int N>
void RayRenderer<N>::addRays(std::list<LightRay> *rays)
{
    std::list<LightRay>::iterator it;

    for (it = rays->begin(); it != rays->end(); ++it)
    {
        std::cout << &(*it) << "\n";
        addRay(&(*it));
    }
}

template<int N>
void RayRenderer<N>::addPosition(LightRay *ray)
{
    auto test = entryReferences.find( ray );
    rayEntry<N> *entry = entryReferences.find( ray )->second;

    entry->bounces = ray->bounceCount;
    Vector2 position = {ray->position.X, ray->position.Y};
    rayMoment newMoment{ray->intensity * 255, position};
    entry->moments[entry->bounces + 1] = newMoment;
}

template<int N>
void RayRenderer<N>::drawRays()
{
    for (int i = 0; i < rays.size(); i++)
    {
        Color rayColor = waveLengthtoRayLibColor(rays[i].wave_length_nm, 1.0f);

        for (int j = 1; j < rays[i].bounces + 1; j++)
        {
            Vector2 prevPos = rays[i].moments[j-1].position;
            Vector2 curPos = rays[i].moments[j].position;
            rayColor.a = rays[i].moments[j].alpha;

            DrawLineCorrected(prevPos.x, prevPos.y, curPos.x, curPos.y, rayColor);
        }
    }
}

#endif