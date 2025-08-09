#include "raylib.h";

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float RunningTime;
};

// func to check if scarfy is on ground
bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

// func for updating scarfys animation frame
AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // update running time
    data.RunningTime += deltaTime;
    if (data.RunningTime >= data.updateTime)
    {
        data.RunningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

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
        nebulae[i].rec.height = (nebula.height / 8.0);
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

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{0};

    SetTargetFPS(180);

    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);

        bgX -= 20 * dT;
        if (bgX <= -background.width * 2)
        {
            bgX = 0.0;
        }

        // draw the background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 4.8, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 4.8, WHITE);

        // performing ground check
        if (isOnGround(scarfyData, windowDimensions[1]))
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

        // updating scarfys animation frame
        if (!isInAir)
        {
            // updating the running time
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Draw nebulaOne
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);

    CloseWindow();
};