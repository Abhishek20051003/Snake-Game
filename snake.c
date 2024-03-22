#include <stdio.h>
#include <conio.h> // For Windows, to use kbhit() and getch() functions
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For usleep() function

#define WIDTH 20
#define HEIGHT 20
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

int gameOver;
int score;
int length;
int headX, headY;
int fruitX, fruitY;
int direction;
int tailX[100], tailY[100];
int lives; // Number of lives

void Setup() {
    gameOver = 0;
    score = 0;
    length = 1;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    direction = RIGHT;
    lives = 3; // Initialize lives to 3
}

// Function to draw the game board
void Draw() {
    system("cls");
    int i, j;
    for (i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == headY && j == headX)
                printf("O"); // Display snake's head
            else if (i == fruitY && j == fruitX)
                printf("*"); // Display fruit
            else {
                int printTail = 0;
                for (int k = 0; k < length; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); // Display snake's body
                        printTail = 1;
                    }
                }
                if (!printTail)
                    printf(" "); // Empty space
            }
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\tLives: %d", score, lives); // Display score and lives
    printf("\n");
}

// Function to handle user input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                direction = LEFT;
                break;
            case 'd':
                direction = RIGHT;
                break;
            case 'w':
                direction = UP;
                break;
            case 's':
                direction = DOWN;
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

// Function to update the game logic
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;
    for (int i = 1; i < length; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (direction) {
        case UP:
            headY--;
            break;
        case DOWN:
            headY++;
            break;
        case LEFT:
            headX--;
            break;
        case RIGHT:
            headX++;
            break;
        default:
            break;
    }
    if (headX >= WIDTH || headX < 0 || headY >= HEIGHT || headY < 0) {
        lives--; // Decrement lives when the snake collides with the walls
        if (lives == 0)
            gameOver = 1; // Game over if lives reach zero
        // Move head to opposite side if it hits the wall
        headX = (headX + WIDTH) % WIDTH;
        headY = (headY + HEIGHT) % HEIGHT;
    }

    for (int i = 0; i < length; i++) {
        if (tailX[i] == headX && tailY[i] == headY) {
            lives--; // Decrease lives when the snake collides with itself
            if (lives == 0)
                gameOver = 1; // Game over if lives reach zero
        }
    }

    if (headX == fruitX && headY == fruitY) {
        score += 1;
        length++;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

// Main function
int main() {
    srand(time(NULL));
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(100000); // Delay of 100 milliseconds (100000 microseconds)
    }
    printf("Game Over!\n");
    return 0;
}
