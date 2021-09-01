#include "Ray.hpp"
#include "Collision.hpp"
#include <Shapes/Circle.hpp>
#include <Shapes/Triangle.hpp>
#include <Shapes/Surface.hpp>
#include <Shapes/Line.hpp>
#include <Lights/Directional.hpp>
#include <Lights/PointLight.hpp>

#include "raylib.h"

#include <list>
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

    Camera2D screenSpaceCamera = { 0 }; // Smoothing camera
    screenSpaceCamera.zoom = 1.0f;

    float cameraX = 0.0f;
    float cameraY = 0.0f;

    Triangle triangle = Triangle({800, 415}, 200, &GLASS);
    Circle circle = Circle({1200, 355}, 100, &GLASS);

    Line boundary1 = Line({screenWidth/2, -1}, {0, 1}, screenWidth, &ABSORBER);
    Line boundary2 = Line({screenWidth/2, SCREEN_HEIGHT + 1}, {0, -1}, screenWidth, &ABSORBER);
    Line boundary3 = Line({-1, SCREEN_HEIGHT/2}, {-1, 0}, SCREEN_HEIGHT, &ABSORBER);
    Line boundary4 = Line({screenWidth + 1, SCREEN_HEIGHT/2}, {1, 0}, SCREEN_HEIGHT, &ABSORBER);

    std::list<Shape*> shapesInScene = {};
    shapesInScene.push_back(&circle);
    shapesInScene.push_back(&triangle);
    shapesInScene.push_back(&boundary1);
    shapesInScene.push_back(&boundary2);
    shapesInScene.push_back(&boundary3);
    shapesInScene.push_back(&boundary4);


    DirectionalLight lightSource = DirectionalLight({100, 250}, {0.9f, 0.40f}, 10.0f, 21);
    Collision coll = Collision(lightSource, shapesInScene);
    
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
                step(&coll.rays, GetFrameTime() * 10.0f);
            }
        }

        
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(screenSpaceCamera);

            drawRays(&coll.rays);
            
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
