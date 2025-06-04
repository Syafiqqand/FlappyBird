#include <raylib.h>
#include <vector>
#include <algorithm>
#include "include/bird.h"
#include "include/pipe.h"
#include "include/pipe_factory.h"
#include "include/game_manager.h"
#include "include/score_manager.h"

Texture2D background;

enum GameOverAction {
    GO_NONE,
    GO_RESTART,
    GO_MAIN_MENU
};

GameOverAction DrawGameOverScreen(int score) {
    // Background semi-transparan
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));

    DrawText(
        "ANDA CUPU !!!",
        GetScreenWidth() / 2 - MeasureText("ANDA CUPU !!!", 40) / 2,
        GetScreenHeight() / 2 - 150,
        40,
        RED
    );

    // Tampilkan skor akhir
    DrawText(
        TextFormat("Total Score: %d", score),
        GetScreenWidth() / 2 - MeasureText(TextFormat("Total Score: %d", score), 30) / 2,
        GetScreenHeight() / 2 - 80,
        30,
        WHITE
    );

    // Tombol Restart
    Rectangle restartBtn = { GetScreenWidth() / 2.0f - 100.0f, GetScreenHeight() / 2.0f, 200.0f, 50.0f };
    bool restartClicked = false;
    
    if (CheckCollisionPointRec(GetMousePosition(), restartBtn)) {
        DrawRectangleRec(restartBtn, BLUE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            restartClicked = true;
        }
    } else {
        DrawRectangleRec(restartBtn, SKYBLUE);
    }
    DrawText("RESTART", restartBtn.x + 50, restartBtn.y + 15, 20, DARKBLUE);

    // Tombol Main Menu
    Rectangle menuBtn = { GetScreenWidth() / 2.0f - 100.0f, GetScreenHeight() / 2.0f + 70, 200.0f, 50.0f };
    bool menuClicked = false;
    
    if (CheckCollisionPointRec(GetMousePosition(), menuBtn)) {
        DrawRectangleRec(menuBtn, GREEN);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            menuClicked = true;
        }
    } else {
        DrawRectangleRec(menuBtn, LIME);
    }
    DrawText("MAIN MENU", menuBtn.x + 40, menuBtn.y + 15, 20, DARKGREEN);

    if (restartClicked) return GO_RESTART;
    if (menuClicked) return GO_MAIN_MENU;
    return GO_NONE;
}

enum MainMenuAction {
    MENU_NONE,
    MENU_PLAY,
    MENU_QUIT
};

MainMenuAction DrawMainMenu() {
    // Background
    ClearBackground(SKYBLUE);
    
    // Judul game
    DrawText(
        "FLAPPY BIRD",
        GetScreenWidth() / 2 - MeasureText("FLAPPY BIRD", 40) / 2,
        GetScreenHeight() / 4,
        40,
        WHITE
    );

    // Tombol Play
    Rectangle playBtn = { GetScreenWidth() / 2.0f - 100.0f, GetScreenHeight() / 2.0f, 200.0f, 50.0f };
    bool playClicked = false;
    
    if (CheckCollisionPointRec(GetMousePosition(), playBtn)) {
        DrawRectangleRec(playBtn, GREEN);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            playClicked = true;
        }
    } else {
        DrawRectangleRec(playBtn, LIME);
    }
    DrawText("PLAY", playBtn.x + 80, playBtn.y + 15, 20, BLACK);

    // Tombol Quit
    Rectangle quitBtn = { GetScreenWidth() / 2.0f - 100.0f, GetScreenHeight() / 2.0f + 70, 200.0f, 50.0f };
    bool quitClicked = false;
    
    if (CheckCollisionPointRec(GetMousePosition(), quitBtn)) {
        DrawRectangleRec(quitBtn, RED);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            quitClicked = true;
        }
    } else {
        DrawRectangleRec(quitBtn, MAROON);
    }
    DrawText("QUIT", quitBtn.x + 80, quitBtn.y + 15, 20, BLACK);

    if (playClicked) return MENU_PLAY;
    if (quitClicked) return MENU_QUIT;
    return MENU_NONE;
}

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Flappy Bird");
    background = LoadTexture("Bg Design Pattern.png");
    if (background.id == 0) {
        TraceLog(LOG_WARNING, "BACKGROUND TEXTURE FAILED TO LOAD!");
    }
    SetTargetFPS(60);

    // Load texture untuk burung
    Texture2D birdTexture = LoadTexture("Char.png");
    if (birdTexture.id == 0) {
        TraceLog(LOG_ERROR, "FAILED TO LOAD BIRD TEXTURE!");
        const char* errorMsg = "Failed to load bird texture!";
    }
    
    Bird bird;
    bird.SetTexture(birdTexture); 

    GameManager gameManager;
    ScoreManager scoreManager;
    gameManager.Attach(&scoreManager);
    gameManager.SetState(MENU); 

    std::vector<Pipe> pipes;
    const int pipeSpawnInterval = 150;
    int frameCounter = 0;

    while (!WindowShouldClose()) {
        // --- Phase 1: Input ---
        if (gameManager.GetState() == PLAYING) {
            if (IsKeyPressed(KEY_SPACE)) {
                bird.Jump();
            }
        }

        // --- Phase 2: Update ---
        if (gameManager.GetState() == PLAYING) {
            bird.Update();
            frameCounter++;

            // Spawn pipa baru secara berkala
            if (frameCounter % pipeSpawnInterval == 0) {
                pipes.push_back(PipeFactory::CreatePipe(screenWidth, screenHeight));
            }

            // Update semua pipa
            for (auto& pipe : pipes) {
                pipe.Update();

                // Cek apakah burung melewati pipa (untuk skor)
                if (!pipe.passed && pipe.upper.x + pipe.upper.width < bird.GetRect().x) {
                    gameManager.AddScore(1);
                    pipe.passed = true;
                }

                // Cek tabrakan
                if (bird.CheckCollision(pipe)) {
                    gameManager.SetState(GAME_OVER);
                }
            }

            // Hapus pipa yang sudah keluar dari layar
            pipes.erase(
                std::remove_if(pipes.begin(), pipes.end(),
                    [](const Pipe& pipe) { return pipe.IsOffScreen(); }
                ),
                pipes.end()
            );
        }

        // --- Phase 3: Render ---
        BeginDrawing();
            if (gameManager.GetState() == MENU) {
                MainMenuAction menuAction = DrawMainMenu();
                
                // Jika tombol Play diklik, mulai permainan
                if (menuAction == MENU_PLAY) {
                    gameManager.Reset();
                    bird = Bird();
                    bird.SetTexture(birdTexture); // Set ulang texture
                    pipes.clear();
                    frameCounter = 0;
                }
                // Jika tombol Quit diklik, keluar dari game
                else if (menuAction == MENU_QUIT) {
                    break;
                }
            }
            else {
                // Gambar background
                DrawTexture(background, 0, 0, WHITE);
            
                // Gambar burung hanya jika game sedang berjalan
                if (gameManager.GetState() == PLAYING) {
                    bird.Draw();
                }
                
                // Gambar pipa
                for (const auto& pipe : pipes) {
                    pipe.Draw();
                }
                
                // Gambar skor
                scoreManager.Draw();

                if (gameManager.GetState() == GAME_OVER) {
                    GameOverAction gameOverAction = DrawGameOverScreen(gameManager.GetScore());
                    
                    if (gameOverAction == GO_RESTART) {
                        // Reset game
                        gameManager.Reset();
                        bird = Bird();
                        bird.SetTexture(birdTexture); // Set ulang texture
                        pipes.clear();
                        frameCounter = 0;
                    }
                    else if (gameOverAction == GO_MAIN_MENU) {
                        // Kembali ke main menu
                        gameManager.SetState(MENU);
                    }
                }
            }
        EndDrawing();
    }

    UnloadTexture(birdTexture);
    UnloadTexture(background);
    CloseWindow();
    return 0;
}