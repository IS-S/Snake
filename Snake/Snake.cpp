
#include <iostream>
#include <conio.h>
#include "Environment.cpp"
#include "windows.h"
#include <thread>
#include <chrono>

using namespace std;
extern bool gameOver = false;
int score = 0;
extern direction direct = STOP;

void gameLogic() {
    Map map;
    Snake snake(map);
    Fruit fruit(map);

    int slowLevel = 400;

    fruit.plantNewFruit(map);
    map.drawFruit(fruit.x, fruit.y);

    while (!gameOver) {
        system("cls");
        snake.move(direct);
        if (map.location[snake.y][snake.x] == '#' || snake.die) {
            gameOver = true;
            break;
        }
        if (snake.x == fruit.x && snake.y == fruit.y) {
            snake.grow();
            fruit.plantNewFruit(map);
            map.drawFruit(fruit.x, fruit.y);
            if (slowLevel > 0) {
                slowLevel = slowLevel - 10;
            }
            score++;
        }

        map.drawSnake(snake.x, snake.y, snake.xt, snake.yt, snake.size, snake.lastTailX, snake.lastTailY, direct);
        cout << *map.location;
        this_thread::sleep_for(chrono::milliseconds(slowLevel));

    }
}

int main()
{

    thread gameControl(gameLogic);
    gameControl.detach();

    while (!gameOver) {
        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                if (direct != DOWN) {
                    direct = UP;
                }
                break;
            case 's':
                if (direct != UP) {
                    direct = DOWN;
                }
                break;
            case 'a':
                if (direct != RIGHT) {
                    direct = LEFT;
                }
                break;
            case 'd':
                if (direct != LEFT) {
                    direct = RIGHT;
                }
                break;
            case 'g':
                gameOver = true;
            }
        }
    }

    system("cls");
    cout << "GAME OVER" << endl << "YOUR SCORE: " << score;
    return 0;
}