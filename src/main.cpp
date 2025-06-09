#include <raylib.h>
#include <vector>
#include <algorithm>
#include "include/bird.h"
#include "include/pipe.h"
#include "include/pipe_factory.h"
#include "include/game_manager.h"
#include "include/score_manager.h"

// ------------------------------------
// Variabel global untuk background & obstacle
// ------------------------------------
Texture2D background;
Texture2D obstacleTexture;

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
    if (menuClicked)   return GO_MAIN_MENU;
    return GO_NONE;
}

enum MainMenuAction {
    MENU_NONE,
    MENU_PLAY,
    MENU_QUIT
};

MainMenuAction DrawMainMenu() {
    // Gambar background
    DrawTexture(background, 0, 0, WHITE);

    // Judul game
    DrawText(
        "Petualangan si kepala kotak",
        GetScreenWidth() / 2 - MeasureText("Petualangan si kepala kotak", 40) / 2,
        GetScreenHeight() / 3,
        40,
        BLACK
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
    const int screenWidth  = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Flappy Bird");
    SetTargetFPS(60);

    // Load background
    background = LoadTexture("Bg Design Pattern.png");
    if (background.id == 0) {
        TraceLog(LOG_WARNING, "BACKGROUND TEXTURE FAILED TO LOAD!");
    }

    // Variabel untuk scrolling background
    float bgScrollX = 0.0f;
    const float bgScrollSpeed = 1.0f; 

    // Load spritesheet obstacle
    obstacleTexture = LoadTexture("SpriteSheet Obstacle rev.png");
    if (obstacleTexture.id == 0) {
        TraceLog(LOG_ERROR, "Gagal load obstacle spritesheet!");
    }

    // Load texture untuk burung
    Texture2D birdTexture = LoadTexture("Char.png");
    if (birdTexture.id == 0) {
        TraceLog(LOG_ERROR, "FAILED TO LOAD BIRD TEXTURE!");
    }

    Bird bird;
    bird.SetTexture(birdTexture);

    GameManager gameManager;
    ScoreManager scoreManager;
    gameManager.Attach(&scoreManager);
    gameManager.SetState(MENU);

    float pipeTextureWidth = 250.0f;   // <-- Ubah saja nilainya (contoh: 80.0f)

    int spawnTimer = PipeFactory::GetRandomSpawnInterval();

    std::vector<Pipe> pipes;

    while (!WindowShouldClose()) {
        // Scrolling BG
        if (gameManager.GetState() == PLAYING) {
            // Update scrolling background
            bgScrollX -= bgScrollSpeed;
            if (bgScrollX <= -background.width) {
                bgScrollX = 0;
            }
        }
        
        // --- Input ---
        if (gameManager.GetState() == PLAYING) {
            if (IsKeyPressed(KEY_SPACE)) {
                bird.Jump();
            }
        }

        // --- Update ---
        if (gameManager.GetState() == PLAYING) {
            bird.Update();

            // Turunkan spawnTimer
            spawnTimer--;
            if (spawnTimer <= 0) {
                // Ketika waktunya spawn, buat pipa baru
                pipes.push_back(
                PipeFactory::CreatePipe(
                    screenWidth,
                    screenHeight,
                    obstacleTexture,
                    PipeFactory::GetMinGapHeight(),
                    PipeFactory::GetMaxGapHeight(),
                    pipeTextureWidth
                )
            );
                // Reset spawnTimer dengan interval acak lagi
                spawnTimer = PipeFactory::GetRandomSpawnInterval();
            }

            // Update semua pipa & cek tabrakan
            for (auto& pipe : pipes) {
                pipe.Update();
                if (bird.CheckCollision(pipe)) {
                    gameManager.SetState(GAME_OVER);
                }
            }

            // Hapus pipa yang keluar layar
            for (size_t i = 0; i < pipes.size(); ) {
                if (pipes[i].IsOffScreen()) {
                    // Setiap pipa keluar layar +1 score
                    gameManager.Notify(1);
                    // Hapus pipa dari vektor
                    pipes.erase(pipes.begin() + i);
                    // Jangan i++ karena elemen berikutnya sudah bergeser ke index i
                } else {
                    i++;
                }
            }
        }

        // --- Render ---
        BeginDrawing();
            if (gameManager.GetState() == MENU) {
                MainMenuAction menuAction = DrawMainMenu();
                if (menuAction == MENU_PLAY) {
                    gameManager.Reset();
                    bird = Bird();
                    bird.SetTexture(birdTexture);
                    pipes.clear();
                    // Reset spawnTimer juga
                    spawnTimer = PipeFactory::GetRandomSpawnInterval();
                } else if (menuAction == MENU_QUIT) {
                    break;
                }
            }
            else {
                // Gambar background 
                if (gameManager.GetState() == PLAYING) {
                    // Gambar background dua kali untuk efek looping
                    DrawTexture(background, bgScrollX, 0, WHITE);
                    DrawTexture(background, bgScrollX + background.width, 0, WHITE);
                } else {
                    // State GAME_OVER: background statis
                    DrawTexture(background, 0, 0, WHITE);
                }

                if (gameManager.GetState() == PLAYING) {
                    bird.Draw();
                    for (auto& pipe : pipes) {
                        pipe.Draw();
                    }
                    scoreManager.Draw();
                }
                

                if (gameManager.GetState() == GAME_OVER) {
                    
                    GameOverAction gameOverAction = DrawGameOverScreen( scoreManager.GetScore() );

                    if (gameOverAction == GO_RESTART) {
                        gameManager.Reset();
                        scoreManager.Reset();
                        bird = Bird();
                        bird.SetTexture(birdTexture);
                        pipes.clear();
                        spawnTimer = PipeFactory::GetRandomSpawnInterval();
                    } else if (gameOverAction == GO_MAIN_MENU) {
                        gameManager.SetState(MENU);
                    }
                }
            }
        EndDrawing();
    }

    // Unload semua texture sebelum exit
    UnloadTexture(birdTexture);
    UnloadTexture(obstacleTexture);
    UnloadTexture(background);

    CloseWindow();
    return 0;
}
