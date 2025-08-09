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
    // window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 1200; // width
    windowDimensions[1] = 720;  // height

    InitWindow(windowDimensions[0], windowDimensions[1], "Dasher");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{3'500};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // AnimData for nebula using array .

    // number of nebulae and its positions
    const int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = (nebula.width / 8.0);
        nebulae[i].rec.height = (nebula.width / 8.0);
        nebulae[i].frame = 0;
        nebulae[i].updateTime = (1.0 / 16.0);
        nebulae[i].RunningTime = 0.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;

        int positionY{i};
        // the positions are different for the nebulas
        nebulae[i].pos.y = windowDimensions[1] - ((nebula.height / 8) * (1 + positionY));
        positionY += 1;
    }

    // nebulaOne velocity(pixels per second)
    int nebOneVel{-200};

    // special compound variable Texture2D by raylib to save textures in variables.
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = (scarfy.width / 6);
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = (windowDimensions[0] / 3) - (scarfyData.rec.width / 2);
    scarfyData.pos.y = (windowDimensions[1] - scarfyData.rec.height);
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
        if (scarfyData.pos.y >= (windowDimensions[1] - scarfyData.rec.height))
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

        if (IsKeyPressed(KEY_SPACE) && (scarfyData.pos.y >= (scarfyData.rec.height))) // stops scarfy from escaping the upper bounds
        {
            velocity += jumpVel;
        };

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // updating nebula position
            nebulae[i].pos.x += nebOneVel * dT;
        }

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

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].RunningTime += dT;
            if (nebulae[i].RunningTime >= nebulae[i].updateTime)
            {
                nebulae[i].RunningTime = 0.0;
                // updating animation frame for nebula
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;

                nebulae[i].frame++;

                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Draw nebulaOne
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, RED);
        }

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
};