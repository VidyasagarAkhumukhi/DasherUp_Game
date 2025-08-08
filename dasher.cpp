#include "raylib.h";

int main()
{
    const int windowWidth{1024};
    int windowHeight{720};

    InitWindow(windowWidth, windowHeight, "Dasher");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{2'500};

    // special compound variable Texture2D by raylib to save textures in variables.
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = (scarfy.width / 6);
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = (windowWidth / 3) - (scarfyRec.width / 2);
    scarfyPos.y = (windowHeight - scarfyRec.height);

    // jump velocity (pixels/sec)
    const int jumpVel{-600};

    // int posY{windowHeight - scarfyRec.height};
    int velocity{0};

    SetTargetFPS(180);

    while (!WindowShouldClose())
    {
        // start Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // delta time (time since last frame)
        const float dt{GetFrameTime()};

        // performing ground check
        if (scarfyPos.y >= (windowHeight - scarfyRec.height))
        {
            // scarfy is on the ground
            velocity = 0;
        }
        else
        {
            // scarfy is in the air
            //  apply gravity
            velocity += gravity * dt;
        }

        if (IsKeyPressed(KEY_SPACE) && (scarfyPos.y >= (0 + scarfyRec.height))) // stops scarfy from escaping the upper bounds
        {
            velocity += jumpVel;
        };

        // updating position
        scarfyPos.y += velocity * dt;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
};