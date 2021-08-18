#ifndef raylib_h
#define raylib_h

#include "raylib.h"

#endif

#ifndef Ray_h
#define Ray_h

#include "Ray.hpp"

#endif

#ifndef Mirror_h
#define Mirror_h

#include "Mirror.hpp"

#endif

#ifndef Collision_h
#define Collision_h

#include "Collision.hpp"

#endif

#ifndef Circle_h
#define Circle_h

#include "Circle.hpp"

#endif

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

    Mirror mirror = Mirror({300, 225}, {.70f, .60f}, 200.0f);
    Circle circle = Circle({800, 415}, 400);

    std::list<LightRay> directionalLight =  getDirectionalLightRays( {100, 515}, 600, {1, -.1}, 200, 1);

    Collision coll = Collision(&directionalLight, &circle);
    

    SetTargetFPS(60);
    int i = 0;
    //--------------------------------------------------------------------------------------

    // Main game loop6
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            std::cout << directionalLight.front().positions.size() << std::endl;
        }

        for (size_t i = 0; i < 100; i++)
        {
            coll.check();
            step(&directionalLight, GetFrameTime() * 10);
        }
        
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(screenSpaceCamera);
                drawRays(&directionalLight);
                //mirror.draw();
                circle.draw();
            EndMode2D();

            //DrawText(TextFormat("Light Position: %ix%i", (int)directionalLight.front().position.X, (int)directionalLight.front().position.Y), 10, 10, 20, DARKBLUE);
            //DrawText(TextFormat("Light next Position: %ix%i", (int)directionalLight.front().nextPosition.X, (int)directionalLight.front().nextPosition.Y), 10, 40, 20, DARKBLUE);
            //DrawText(TextFormat("Step Counts: %i", lr.positions.size()), 10, 40, 20, DARKGREEN);
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
