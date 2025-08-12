# Dasher

Dasher is a fast-paced 2D side-scrolling runner built with C++ and the Raylib library. The game features a player character, "Scarfy," who must run and jump to navigate a challenging course of oncoming obstacles to reach the finish line. This project showcases several key game development concepts, including sprite animation, parallax scrolling, and procedural level generation.

![gameplay](<img src="textures/Dasher.gif" width="50%" height="50%"/>)

<img src="textures/Dasher.gif" width="50%" height="50%"/>

## 🎮 Gameplay & Controls

- **Objective**: Guide Scarfy to the finish line by navigating a series of hazardous nebulae. You'll need to jump over low obstacles and run underneath high ones.
- **Controls**:
  - `SPACEBAR` - Jump
- **Win Condition**: Reach the end of the level.
- **Lose Condition**: The game is over if Scarfy collides with a nebula.

## ✨ Key Features

- **Custom Sprite Animation**: Both the player and the obstacles are animated using sprite sheets. A custom data structure (`AnimData`) and update function (`updateAnimData`) handle frame timing and updates.
- **Physics-Based Jumping**: Player movement is governed by velocity and a constant gravitational force, creating a satisfying and familiar jump mechanic.
- **Parallax Scrolling Background**: The game features three layers of background scenery that scroll at different speeds, creating a convincing illusion of depth.
- **Procedural Obstacle Placement**: Obstacles are dynamically generated with alternating vertical positions (high and low), creating a rhythmic pattern that challenges the player's timing and reflexes.
- **Optimized Collision Detection**: Collision is handled using Raylib's `CheckCollisionRecs` function, with manually adjusted hitboxes to ensure fairness and a better "feel" during gameplay.

## 🛠️ Technical Overview

This project is built from the ground up in C++ with the Raylib framework and demonstrates several important programming techniques.

- **Language/Framework**: C++ with the [Raylib](https://www.raylib.com/) library.
- **Data Structures**: The `AnimData` struct is used to efficiently manage state (position, frame, timing) for any animated object, demonstrating effective data-oriented design.
- **Procedural Generation**: The obstacle course is generated in a loop, using the modulo operator (`i % 2`) to create a predictable yet challenging high-low pattern. This is a fundamental technique in creating dynamic levels.
- **Frame-Rate Independence**: All movement and physics calculations use `delta time` (via `GetFrameTime()`) to ensure the game runs consistently at any frame rate.
- **Resource Management**: The program correctly loads all `Texture2D` assets at the start and unloads them using `UnloadTexture()` before closing to prevent memory leaks.
- **Game Loop Architecture**: The core `while` loop maintains a clean separation between the game logic/update phase and the rendering phase (`BeginDrawing()` / `EndDrawing()`).

## ⚙️ How to Build and Run

### Prerequisites

You need to have a C++ compiler (like g++ or Clang) and the [Raylib](https://www.raylib.com/) library installed on your system.

### Compilation

Navigate to the project directory in your terminal and compile the source file. The exact command may vary based on your operating system.

**Example for Linux/macOS:**

```bash
g++ dasher.cpp -o dasher -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

**Example for Windows (MinGW):**

```bash
g++ dasher.cpp -o dasher.exe -lraylib -lopengl32 -lgdi32 -lwinmm

```
