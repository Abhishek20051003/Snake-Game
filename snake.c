#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
int lives;

void Setup() {
    gameOver = 0;
    score = 0;
    length = 1;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    direction = RIGHT;
    lives = 3;
}

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
                printf("O"); 
            else if (i == fruitY && j == fruitX)
                printf("*");
            else {
                int printTail = 0;
                for (int k = 0; k < length; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        printTail = 1;
                    }
                }
                if (!printTail)
                    printf(" ");
            }
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\tLives: %d", score, lives);
    printf("\n");
}

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
        lives--;
        if (lives == 0)
            gameOver = 1;
        headX = (headX + WIDTH) % WIDTH;
        headY = (headY + HEIGHT) % HEIGHT;
    }

    for (int i = 0; i < length; i++) {
        if (tailX[i] == headX && tailY[i] == headY) {
            lives--;
            if (lives == 0)
                gameOver = 1;
        }
    }

    if (headX == fruitX && headY == fruitY) {
        score += 1;
        length++;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

int main() {
    srand(time(NULL));
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(100000);
    }
    printf("Game Over!\n");
    return 0;
}
