#ifndef MathX_h
#define MathX_h

#include "MathX.h"

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