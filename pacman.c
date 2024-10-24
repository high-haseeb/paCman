

#include <raylib.h>

#define ROWS 19
#define COLS 16
#define CELL_SIZE 40

void drawBoard(char pacmanBoard[ROWS][COLS]){
   for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
       Vector2 position = {j * CELL_SIZE , i * CELL_SIZE};
       if (pacmanBoard[i][j] == '#') {
         DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, BLUE);
       }
       else if (pacmanBoard[i][j] == '.') {
         DrawCircle(position.x + CELL_SIZE / 2, position.y + CELL_SIZE / 2, 5, YELLOW);
       }
       else if (pacmanBoard[i][j] == 'Q') {
         DrawText("Q", position.x + CELL_SIZE / 4, position.y + CELL_SIZE / 4, CELL_SIZE / 2, RED);
       }
     }
   }
}

int main(){
    const int screenWidth = COLS * CELL_SIZE;
    const int screenHeight = ROWS * CELL_SIZE;

     InitWindow(screenWidth , screenHeight , "Pacman");
     SetTargetFPS(60);
      int qx = 7;
      int qy = 7;
      int score = 0;
     char pacmanBoard[ROWS][COLS] = {
       {'#' , '#' , '#' , '#' , '#' ,'#' ,'#' ,'#' , '#' , '#' ,'#' , '#' , '#' , '#' , '#' , '#'},
       {'#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '#', '.', '.', '#' },
       {'#' , '.' , '.' , '#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '#', '.', '.', '#' },
       {'#' , '.' , '.' , '#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '#', '.', '.', '#' },
       {'#' , '.' , '.' , '#' , '.' , '.' , '.' , 'Q' , '.' , '.' , '.' , '.', '#', '.', '.', '#' },
       {'#' , '.' , '.' , '#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '#', '.', '.', '#' },
       {'#' , '.' , '.' , '#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '#', '.', '.', '#' },
       {'#' , '.' , '.' , '#' , '#' , '#' , '#' , '#' , '#' , '#' , '#' , '#', '#', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '#' , '#' , ' ' , ' ' , '#' , '#' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '#' , ' ' , ' ' , ' ' , ' ' , '#' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '#' , ' ' , ' ' , ' ' , ' ' , '#' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '#' , '#' , '#' , '#' , '#' , '#' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '.', '.', '.', '#' },
       {'#' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.' , '.', '.', '.', '.', '#' },
       {'#' , '#' , '#' , '#' , '#' ,'#' ,'#' ,'#' , '#' , '#' ,'#' , '#' , '#' , '#' , '#' , '#' },
    };
    while (!WindowShouldClose()) {
  
     if (IsKeyPressed(KEY_W) && pacmanBoard[qy - 1][qx] != '#') {
       //if (); 
       pacmanBoard[qy][qx] = ' ';
       qy--;
     }
     if (IsKeyPressed(KEY_S) && pacmanBoard[qy + 1][qx] != '#') {
       pacmanBoard[qy][qx] = ' ';
       qy++;
     }
     if (IsKeyPressed(KEY_A) && pacmanBoard[qy][qx - 1] != '#') {
       pacmanBoard[qy][qx] = ' ';
       qx--;
     }
     if (IsKeyPressed(KEY_D) && pacmanBoard[qy][qx + 1] != '#') {
       pacmanBoard[qy][qx] = ' ';
       qx++;
     }
       pacmanBoard[qy][qx] = 'Q';
      BeginDrawing();
      ClearBackground(BLACK);
      drawBoard(pacmanBoard);
      EndDrawing();
    }
    CloseWindow();
    return 0;
}
