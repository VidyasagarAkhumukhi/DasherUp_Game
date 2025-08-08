#include "raylib.h";

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float RunningTime;
};

int main()
{
    const int windowWidth{1024};
    int windowHeight{720};

    InitWindow(windowWidth, windowHeight, "Dasher");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{3'500};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula.
    AnimData nebulaData{
        {0.0, 0.0, (nebula.width / 8.0), (nebula.width / 8.0)}, // Rectrangle Rec
        {windowWidth, windowHeight - nebula.height / 8},        // Vector2 pos
        {0},                                                    // int frame
        {(1.0 / 12.0)},                                         // float updateTime
        {0.0}                                                   // float runningTime
    };

    AnimData nebula2Data{
        {0.0, 0.0, (nebula.width / 8.0), (nebula.width / 8.0)}, // Rectrangle Rec
        {windowWidth + 300, ((nebula.height / 8) * 3)},         // Vector2 pos
        {0},                                                    // int frame
        {(1.0 / 16.0)},                                         // float updateTime
        {0.0}                                                   // float runningTime
    };

    // nebulaOne velocity(pixels per second)
    int nebOneVel{-200}, nebTwoVel{-300}, nebThreeVel{-225};

    // special compound variable Texture2D by raylib to save textures in variables.
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = (scarfy.width / 6);
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = (windowWidth / 3) - (scarfyData.rec.width / 2);
    scarfyData.pos.y = (windowHeight - scarfyData.rec.height);
    scarfyData.frame = 0;
    scarfyData.updateTime = (1.0 / 12.0);
    scarfyData.RunningTime = 0.0;

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
        if (scarfyData.pos.y >= (windowHeight - scarfyData.rec.height))
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

        if (IsKeyPressed(KEY_SPACE) && (scarfyData.pos.y >= (0 + scarfyData.rec.height))) // stops scarfy from escaping the upper bounds
        {
            velocity += jumpVel;
        };

        // updating nebula position
        nebulaData.pos.x += nebOneVel * dT;
        nebula2Data.pos.x += nebTwoVel * dT;

        // updating scarfy position
        scarfyData.pos.y += velocity * dT;

        if (!isInAir)
        {
            // updating the running time
            scarfyData.RunningTime += dT;
            if (scarfyData.RunningTime >= scarfyData.updateTime)
            {
                scarfyData.RunningTime = 0.0;
                // update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;

                scarfyData.frame++;

                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        nebulaData.RunningTime += dT;
        if (nebulaData.RunningTime >= nebulaData.updateTime)
        {
            nebulaData.RunningTime = 0.0;
            nebula2Data.RunningTime = 0.0;
            // updating animation frame for nebula
            nebulaData.rec.x = nebulaData.frame * nebulaData.rec.width;
            nebula2Data.rec.x = nebulaData.frame * nebulaData.rec.width;

            nebulaData.frame++;

            if (nebulaData.frame > 7)
            {
                nebulaData.frame = 0;
            }
        }

        // Draw nebulaOne
        DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
        DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, RED);

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
};