#ifndef MathX_h
#define MathX_h

#include "MathX.h"

#endif

#ifndef raylib_h
#define raylib_h

#include "raylib.h"

#endif

#include <iostream>
#include <string>


#define SCREEN_HEIGHT 900


void DrawLineCorrected(int x1, int y1, int x2, int y2, Color color)
{
    DrawLine(x1, SCREEN_HEIGHT - y1, x2, SCREEN_HEIGHT - y2, color);
}

void DrawCircleCorrected(int posX, int posY, float radius, Color color)
{
    DrawCircleLines(posX, SCREEN_HEIGHT - posY, radius, BLUE);
}

void Print(std::string text)
{
    std::cout << text << std::endl;
}

void PrintVector(MathX::Vector3 vec, std::string name)
{
    std::cout << name << std::endl;
    vec.Print();
    std::cout << std::endl;
}

void PrintVector(MathX::Vector2 vec, std::string name)
{
    std::cout << name << std::endl;
    vec.Print();
    std::cout << std::endl;
}

void PrintValue(float val, std::string name)
{
    std::cout << name << std::endl;
    std::cout << val << std::endl;
}

Color toRayLibColor(MathX::Color color)
{
    return Color{(unsigned char) color.R, (unsigned char) color.G, (unsigned char) color.B, (unsigned char) color.A};
}

MathX::Color toMathXColor(Color color)
{
    return MathX::Color{color.r, color.g, color.b, color.a};
}
