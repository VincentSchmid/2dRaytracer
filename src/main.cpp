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
#include <array>

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

    Camera2D screenSpaceCamera = { 0 }; // Smoothing camera
    screenSpaceCamera.zoom = 1.0f;

    float cameraX = 0.0f;
    float cameraY = 0.0f;

    Triangle triangle = Triangle({800, 415}, 200, &CRAZY_GLASS);
    Circle circle = Circle({1200, 355}, 100, &CRAZY_GLASS);

    std::list<Shape*> shapesInScene = {};
    shapesInScene.push_back(&circle);
    shapesInScene.push_back(&triangle);

    std::list<LightRay> directionalLight =  getDirectionalLightRays( {100, 250}, 2, {.9, .40}, 21, 1.0f);

    Collision coll = Collision(&directionalLight, shapesInScene);
    

    SetTargetFPS(60);
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
                step(coll.rays, GetFrameTime() * 10.0f);
            }
        }

        
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(screenSpaceCamera);
                drawRays(coll.rays);
                
                std::list<Shape*>::iterator it;

                for (it = shapesInScene.begin(); it != shapesInScene.end(); ++it)
                {
                    (*it)->draw();
                }
                
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
