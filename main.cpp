#ifndef raylib_h
#define raylib_h

#include "raylib.h"

#endif

#include "Ray.hpp"
#include "Collision.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Surface.hpp"

#include <math.h>

#define SCREEN_HEIGHT 900


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = SCREEN_HEIGHT;

    const int virtualScreenWidth = 1600;
    const int virtualScreenHeight = SCREEN_HEIGHT;

    const float virtualRatio = (float)screenWidth/(float)virtualScreenWidth;

    InitWindow(screenWidth, screenHeight, "Light Ray Simulation");

    Camera2D worldSpaceCamera = { 0 };  // Game world camera
    worldSpaceCamera.zoom = 1.0f;

    Camera2D screenSpaceCamera = { 0 }; // Smoothing camera
    screenSpaceCamera.zoom = 1.0f;

    float cameraX = 0.0f;
    float cameraY = 0.0f;

    struct Surface glass = {0.0f, 1.0f, 0.0f, 
        [](float wavelength_um) -> float
        { 
            // function from here https://refractiveindex.info/?shelf=3d&book=glass&page=soda-lime-clear
            return 1.5130f - 0.003169f * pow(wavelength_um, 2.0f) + 0.003962f * pow(wavelength_um, -2.0f);
        }
    };

    struct Surface crazyGlass = {0.0f, 1.0f, 0.0f, 
        [](float wavelength_um) -> float
        { 
            // not realistic properties
            return 1.5130f - 0.006069f * pow(wavelength_um, 2.0f) + 0.008062f * pow(wavelength_um, -2.0f);
        }
    };

    Circle circle = Circle({800, 415}, 200, &glass);
    Triangle triangle = Triangle({800, 415}, 200, &crazyGlass);

    std::list<LightRay> directionalLight =  getDirectionalLightRays( {100, 250}, 2, {.9, .40}, 101, 1.0f);

    Collision coll = Collision(&directionalLight, &triangle);
    

    SetTargetFPS(60);
    int i = 0;
    bool go = false;
    //--------------------------------------------------------------------------------------

    // Main game loop6
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            go = true;
            //std::cout << coll.rays->front().positions.size() << std::endl;
        }

        if (go)
        {
            for (size_t i = 0; i < 100; i++)
            {
                coll.check();
                step(coll.rays, GetFrameTime() * 10);
            }
        }

        
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(screenSpaceCamera);
                drawRays(coll.rays);
                //mirror.draw();
                triangle.draw();
            EndMode2D();

            //DrawText(TextFormat("Light Position: %ix%i", (int)directionalLight.front().position.X, (int)directionalLight.front().position.Y), 10, 10, 20, DARKBLUE);
            //DrawText(TextFormat("Light next Position: %ix%i", (int)directionalLight.front().nextPosition.X, (int)directionalLight.front().nextPosition.Y), 10, 40, 20, DARKBLUE);
            //DrawText(TextFormat("Ray Count: %i", coll.rays->size()), 10, 40, 20, DARKGREEN);
            DrawFPS(GetScreenWidth() - 95, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
