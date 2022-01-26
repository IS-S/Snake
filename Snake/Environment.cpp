#include <iostream>
using namespace std;

enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class Map
{
public:
	const static int width = 62, height = 22;
	char location[height][width + 1] = { '0' };
	Map()
	{

		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
					location[j][i] = { '#' };
					if (i == width - 1) {
						location[j][i + 1] = { '\n' };
					}

				}
				else {
					location[j][i] = { ' ' };
				}
			}

		}
		location[height - 1][width] = { '\0' };
	}
	void drawSnake(int x, int y, int* xt, int* yt, int size, int lastTailX, int lastTailY, direction path)
	{
		location[y][x] = { '0' };
		for (int i = size; i >= 0; i--)
		{
			location[yt[i]][xt[i]] = { '0' };
		}
		if (path != STOP) {
			location[lastTailY][lastTailX] = { ' ' };
		}

	}
	void drawFruit(int x, int y)
	{
		location[y][x] = { 'X' };
	}
	~Map() {
	}

};

class Fruit
{
public:
	int x, y, random, randomCounter;
	bool fruitPlanted;
	Fruit(Map& map) {
		fruitPlanted = false;
		while (!fruitPlanted) {
			random = rand() % ((map.width - 2) * (map.height - 2));
			randomCounter = 0;
			for (int j = 1; j < map.height - 1; j++) {
				for (int i = 1; i < map.width - 1; i++) {
					if (map.location[j][i] == ' ') {
						if (randomCounter == random) {
							x = i;
							y = j;
							fruitPlanted = true;
						}
						randomCounter++;
					}
				}
			}
		}
	}
	void plantNewFruit(Map& map) {
		fruitPlanted = false;
		while (!fruitPlanted) {
			random = rand() % ((map.width - 2) * (map.height - 2));
			randomCounter = 0;
			for (int j = 1; j < map.height - 1; j++) {
				for (int i = 1; i < map.width - 1; i++) {
					if (map.location[j][i] == ' ') {
						if (randomCounter == random) {
							x = i;
							y = j;
							fruitPlanted = true;
						}
						randomCounter++;
					}
				}
			}
		}
	}
	~Fruit() {

	}
};

class Snake
{
public:
	int x, y, size, arrSize, lastTailX, lastTailY;
	int* xt;
	int* yt;
	bool die = false, needSkip = false;
	Snake(Map& map)
	{
		arrSize = map.width * map.height;
		y = map.height / 2 + 1;
		x = map.width / 2 + 1;
		size = 0;
		xt = new int[arrSize];
		yt = new int[arrSize];
		xt[size] = x;
		yt[size] = y;
	}
	Snake()
	{
		x = 1;
		y = 1;
		int xt[100];
		int yt[100];
	}
	void move(direction path) {

		switch (path)
		{
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		}

		lastTailX = xt[0];
		lastTailY = yt[0];

		for (int i = 0; i < size + 1; i++)
		{
			xt[i] = xt[i + 1];
			yt[i] = yt[i + 1];
			if (xt[i] == x && yt[i] == y) {
				die = true;
			}
			if (i == size) {
				xt[i] = x;
				yt[i] = y;
			}
		}


	}
	void grow()
	{
		size++;
		xt[size] = x;
		yt[size] = y;
		for (int i = size + 1; i > 0; i--) {
			xt[i] = xt[i - 1];
			yt[i] = yt[i - 1];
		}

	}
	~Snake() {
		delete[] xt;
		delete[] yt;
	}
};

