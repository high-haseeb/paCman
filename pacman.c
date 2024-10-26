#include <math.h>
#include <raylib.h>
#include <stdio.h>

#define ROWS 19
#define COLS 16
#define CELL_SIZE 40

int score = 0;
const float speed = 0.1;

char pacmanBoard[ROWS][COLS] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '#', '.', '.', '.', 'P', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', ' ', ' ', ' ', ' ', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', ' ', ' ', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '#', '#', '#', '#', '#', '#', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
};

const Color pacmanColor = {.r = 253, .g = 255, .b = 0, .a = 255};
const Color pinkyColor = {.r = 234, .g = 130, .b = 229, .a = 255};
const Color blinkyColor = {.r = 208, .g = 62, .b = 25, .a = 255};
const Color inkyColor = {.r = 70, .g = 191, .b = 238, .a = 255};
const Color clydeColor = {.r = 219, .g = 133, .b = 28, .a = 255};

enum Direction { UP, DOWN, LEFT, RIGHT, IDLE };
enum GhostMode { CHASE, SCATTER, FRIGHTENED };

struct Ghost {
    Vector2 position;
    Color color;
    enum Direction dir;
} Ghost;

struct Pacman {
    Vector2 position;
    Color color;
    enum Direction dir;
} Pacman;

struct Pacman pacman = {
    .position = {.x = 7, .y = 7},
    .color = pacmanColor,
    .dir = IDLE,
};

struct Ghost blinky = {.position = {.x = 7, .y = 13}, .color = blinkyColor, .dir = IDLE};
/* struct Ghost pinky = {.position = {.x = 7, .y = 14}, .color = pinkyColor, .dir = IDLE}; */
/* struct Ghost inky = {.position = {.x = 8, .y = 14}, .color = inkyColor, .dir = idle}; */
/* struct Ghost clyde = {.position = {.x = 9, .y = 14}, .color = clydeColor}; */

void drawBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            Vector2 position = {j * CELL_SIZE, i * CELL_SIZE};
            if (pacmanBoard[i][j] == '#') {
                DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, BLUE);
            } else if (pacmanBoard[i][j] == '.') {
                DrawCircle(position.x + (float)CELL_SIZE / 2, position.y + (float)CELL_SIZE / 2, 5, GREEN);
            }
            DrawRectangle((int)pacman.position.x * CELL_SIZE, (int)pacman.position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, pacman.color);
            DrawRectangle(blinky.position.x * CELL_SIZE, blinky.position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, blinky.color);
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (pacmanBoard[(int)blinky.position.y + i][(int)blinky.position.x + j] == '#')
                        continue;
                    /* DrawRectangle((blinky.position.x + j) * CELL_SIZE, (blinky.position.y + i) * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
                     */
                    DrawLine((blinky.position.x + j) * CELL_SIZE, (blinky.position.y + i) * CELL_SIZE, pacman.position.x * CELL_SIZE,
                             pacman.position.y * CELL_SIZE, RED);
                }
            }
            /* DrawLine(blinky.position.x * CELL_SIZE, blinky.position.y * CELL_SIZE, pacman.position.x * CELL_SIZE, pacman.position.y *
             * CELL_SIZE, RED); */
        }
    }
}

void input(void) {
    int key = GetKeyPressed();
    switch (key) {
    case KEY_W:
        pacman.dir = UP;
        break;
    case KEY_S:
        pacman.dir = DOWN;
        break;
    case KEY_D:
        pacman.dir = RIGHT;
        break;
    case KEY_A:
        pacman.dir = LEFT;
        break;
    }
}

void gameLoop(void) {
    if (pacmanBoard[(int)pacman.position.y][(int)pacman.position.x] == '.') {
        pacmanBoard[(int)pacman.position.y][(int)pacman.position.x] = ' ';
        score++;
    }
    Vector2 tempPosition = pacman.position;
    switch (pacman.dir) {
    case UP:
        pacman.position.y -= speed;
        break;
    case DOWN:
        pacman.position.y += speed;
        break;
    case LEFT:
        pacman.position.x -= speed;
        break;
    case RIGHT:
        pacman.position.x += speed;
        break;
    case IDLE:
        break;
    }
    if (pacmanBoard[(int)pacman.position.y][(int)pacman.position.x] == '#') {
        pacman.dir = IDLE;
        pacman.position = tempPosition;
    }

    // ghost movement logic
    //
    int shortestDistance = INFINITY;
    int si = 0;
    int sj = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (pacmanBoard[(int)blinky.position.y + i][(int)blinky.position.x + j] != '#') {
                int distance = pow(((blinky.position.x + i) - pacman.position.x), 2) + pow((blinky.position.y + j) - pacman.position.y, 2);
                if (distance < shortestDistance) {
                    shortestDistance = distance;
                    si = i;
                    sj = j;
                }
            } else {
                printf("INFO: wall detected \n");
            }
        }
    }
    blinky.position.x = blinky.position.x + si * speed;
    blinky.position.y = blinky.position.y + sj * speed;
}

int main() {
    const int screenWidth = COLS * CELL_SIZE;
    const int screenHeight = ROWS * CELL_SIZE;

    char scoreStr[32];

    InitWindow(screenWidth, screenHeight, "Pacman");
    SetTargetFPS(60);
    Font SF = LoadFont("./assets/SF-Pro-Display-Bold.otf");

    while (!WindowShouldClose()) {
        input();
        BeginDrawing();
        ClearBackground(BLACK);

        float distance = sqrt(pow((blinky.position.x - pacman.position.x), 2) + pow((blinky.position.y - pacman.position.y), 2));
        sprintf(scoreStr, "distance: %f", distance);

        gameLoop();
        drawBoard();
        DrawTextEx(SF, scoreStr, (Vector2){.x = 10, .y = 10}, 24, 1, GREEN);
        EndDrawing();
    }

    UnloadFont(SF);
    CloseWindow();

    return 0;
}
