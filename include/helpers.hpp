#ifndef helpers_h
#define helpers_h

#include "MathX.h"
#include "wavelength_rgb.hpp"

#include <iostream>
#include <string>

#include "raylib.h"

#define SCREEN_HEIGHT 900


void DrawLineCorrected(int x1, int y1, int x2, int y2, Color color)
{
    DrawLine(x1, SCREEN_HEIGHT - y1, x2, SCREEN_HEIGHT - y2, color);
}

void DrawCircleCorrected(int posX, int posY, float radius, Color color)
{
    DrawCircleLines(posX, SCREEN_HEIGHT - posY, radius, BLUE);
}

void DrawTriangleCorrected(MathX::Vector2 v1, MathX::Vector2 v2, MathX::Vector2 v3, Color color)
{
    Vector2 cv1 = Vector2{v1.X, SCREEN_HEIGHT - v1.Y};
    Vector2 cv2 = Vector2{v2.X, SCREEN_HEIGHT - v2.Y};
    Vector2 cv3 = Vector2{v3.X, SCREEN_HEIGHT - v3.Y};

    DrawTriangleLines(cv1, cv2, cv3, color);
}

void DrawCross(MathX::Vector2 pos, float size, Color color)
{
    DrawLineCorrected(pos.X - size/2, pos.Y, pos.X + size/2, pos.Y, color);
    DrawLineCorrected(pos.X, pos.Y - size/2, pos.X, pos.Y + size/2, color);
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

Color waveLengthtoRayLibColor(float waveLength, float alpha)
{
    rgb color = convert_wave_length_nm_to_rgb((double) waveLength);
    return Color{(unsigned char) color.red, (unsigned char) color.green, (unsigned char) color.blue, (unsigned char) alpha};
}

Color toRayLibColor(MathX::Color color)
{
    return Color{(unsigned char) color.R, (unsigned char) color.G, (unsigned char) color.B, (unsigned char) color.A};
}

MathX::Color toMathXColor(Color color)
{
    return MathX::Color{color.r, color.g, color.b, color.a};
}

#endif