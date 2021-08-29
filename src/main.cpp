#include "Ray.hpp"
#include "Collision.hpp"
#include <Shapes/Circle.hpp>
#include <Shapes/Triangle.hpp>
#include <Shapes/Surface.hpp>
#include <Lights/Directional.hpp>
#include <Lights/PointLight.hpp>
#include "RayProcessor.hpp"
#include "RayRenderer.hpp"

#include "raylib.h"

#include <list>
#include <math.h>

#define SCREEN_HEIGHT 900
#define MAX_BOUNCES 5


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

    Triangle triangle = Triangle({800, 415}, 200, &GLASS);
    Circle circle = Circle({1200, 355}, 100, &GLASS);

    std::list<Shape*> shapesInScene = {};
    shapesInScene.push_back(&circle);
    shapesInScene.push_back(&triangle);

    RayRenderer<MAX_BOUNCES> renderer = RayRenderer<MAX_BOUNCES>();

    DirectionalLight lightSource = DirectionalLight({100, 250}, {0.9f, 0.40f}, 10.0f, 21);
    Collision<5> coll = Collision<5>(&renderer, lightSource, shapesInScene, MAX_BOUNCES);
    renderer.addRays(&coll.rays);
    
    SetTargetFPS(60);
    bool go = false;
    //--------------------------------------------------------------------------------------

    // Main game loop
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
                step(&renderer, &coll.rays, GetFrameTime() * 10.0f);
            }
        }

        
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(screenSpaceCamera);

            renderer.drawRays();
            
            for (Shape* shape : shapesInScene)
            {
                shape->draw();
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
