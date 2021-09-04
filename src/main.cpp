#include "Ray.hpp"
#include "Collision.hpp"
#include <Shapes/Circle.hpp>
#include <Shapes/Triangle.hpp>
#include <Shapes/Surface.hpp>
#include <Shapes/Line.hpp>
#include <Lights/Directional.hpp>
#include <Lights/PointLight.hpp>
#include "RayProcessor.hpp"
#include "RayRenderer.hpp"
#include "timer.hpp"

#include "raylib.h"

#include <list>
#include <math.h>

#define SCREEN_HEIGHT 900
#define MAX_BOUNCES 6


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

    Line boundary1 = Line({screenWidth/2, 5}, {0, 1}, screenWidth, &ABSORBER);
    Line boundary2 = Line({screenWidth/2, SCREEN_HEIGHT - 5}, {0, -1}, screenWidth, &ABSORBER);
    Line boundary3 = Line({5, SCREEN_HEIGHT/2}, {-1, 0}, SCREEN_HEIGHT, &ABSORBER);
    Line boundary4 = Line({screenWidth - 5, SCREEN_HEIGHT/2}, {1, 0}, SCREEN_HEIGHT, &ABSORBER);

    std::list<Shape*> shapesInScene = {};
    shapesInScene.push_back(&circle);
    shapesInScene.push_back(&triangle);
    shapesInScene.push_back(&boundary1);
    shapesInScene.push_back(&boundary2);
    shapesInScene.push_back(&boundary3);
    shapesInScene.push_back(&boundary4);


    RayRenderer<MAX_BOUNCES> renderer = RayRenderer<MAX_BOUNCES>();

    DirectionalLight lightSource = DirectionalLight({100, 250}, {0.9f, 0.40f}, 10.0f, 1);
    Collision<MAX_BOUNCES> coll = Collision<MAX_BOUNCES>(&renderer, (Light &) lightSource, shapesInScene, (unsigned int) MAX_BOUNCES - 2);
    renderer.addRays(&coll.rays);
    
    SetTargetFPS(60);
    bool go = false;
    double secondsPerFrame = 1.0 / 60.0;
    Timer timer;
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
            timer.reset();
            while (timer.seconds_elapsed() < secondsPerFrame)
            {
                coll.check();
                step(&renderer, &coll.rays, GetFrameTime() * 10.0f);
            }

            if (coll.activeRayCount < 2 * BUNDLE_SIZE)
            {
                lightSource.castRays();
                coll.addRays((Light&)lightSource);
            }
        }

        
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(screenSpaceCamera);

            renderer.drawRays();

            /*
            for each (MathX::Vector2 var in getPointsAlongLine({ 100, 100 }, { 200, 150 }, 2, true))
            {
                DrawCross(var, 10, RED);
            }
            */
            
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
