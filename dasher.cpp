#include "raylib.h";

int main()
{
    const int windowWidth{1024};
    int windowHeight{720};

    InitWindow(windowWidth, windowHeight, "Dasher");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{3'500};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaOneRec{0.0, 0.0, (nebula.width / 8.0), (nebula.height / 8.0)};
    // Braced initialization OR
    // nebulaOneRec.x = 0;
    // nebulaOneRec.y = 0;
    // nebulaOneRec.width = (nebula.width / 8);
    // nebulaOneRec.height = (nebula.height / 8);
    // vector positioning for nebulas
    Vector2 nebulaOnePos{windowWidth, windowHeight - nebulaOneRec.height};

    Rectangle nebulaTwoRec{0.0, (nebula.height - (nebula.height - nebulaOneRec.height)), (nebula.width / 8), (nebula.height / 8)};
    // nebulaTwoRec.width = (nebula.width / 8);
    // nebulaTwoRec.height = (nebula.height / 8);
    // nebulaTwoRec.x = 0;
    // nebulaTwoRec.y = (nebula.height - (nebula.height - nebulaOneRec.height));
    // vector positioning for nebulas
    Vector2 nebulaTwoPos{windowWidth, windowHeight - (windowHeight / 1.5)};

    Rectangle nebulaThreeRec{0.0, (nebula.height - (nebula.height - (nebulaOneRec.height) * 2)), (nebula.width / 8), (nebula.height / 8)};
    Vector2 nebulaThreePos{windowWidth, 0};

    // nebulaOne velocity(pixels per second)
    int nebOneVel{-200}, nebTwoVel{-300}, nebThreeVel{-225};

    // special compound variable Texture2D by raylib to save textures in variables.
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = (scarfy.width / 6);
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    // vector positioning for scarfy
    Vector2 scarfyPos;
    scarfyPos.x = (windowWidth / 3) - (scarfyRec.width / 2);
    scarfyPos.y = (windowHeight - scarfyRec.height);

    // animation frame
    int frame{};
    // amount of time before we update the animation frame
    const float updateTime{(1.0 / 12.0)};
    float runningTime{};

    // jump velocity (pixels/sec)
    const int jumpVel{-1200};

    // int posY{windowHeight - scarfyRec.height};
    int velocity{0};

    // is scarfy in air
    bool isInAir{};

    SetTargetFPS(180);

    while (!WindowShouldClose())
    {
        // start Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // performing ground check
        if (scarfyPos.y >= (windowHeight - scarfyRec.height))
        {
            isInAir = false;
            // scarfy is on the ground
            velocity = 0;
        }
        else
        {
            isInAir = true;
            // scarfy is in the air
            //  apply gravity
            velocity += gravity * dT;
        }

        if (IsKeyPressed(KEY_SPACE) && (scarfyPos.y >= (0 + scarfyRec.height))) // stops scarfy from escaping the upper bounds
        {
            velocity += jumpVel;
        };

        // updating nebula position
        nebulaOnePos.x += nebOneVel * dT;
        nebulaTwoPos.x += nebTwoVel * dT;
        nebulaThreePos.x += nebThreeVel * dT;

        // updating scarfy position
        scarfyPos.y += velocity * dT;

        if (!isInAir)
        {
            // updating the running time
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;

                frame++;

                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // Draw nebulaOne
        DrawTextureRec(nebula, nebulaOneRec, nebulaOnePos, WHITE);
        DrawTextureRec(nebula, nebulaTwoRec, nebulaTwoPos, WHITE);
        DrawTextureRec(nebula, nebulaThreeRec, nebulaThreePos, WHITE);

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
};