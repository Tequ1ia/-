#include "Integration.h"
using namespace std;

bool IsFoodEaten(Snake& snake, Food& food) {
	if (food.is_big) {
		if (!food.exist)
			return false;
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				Coordinate offset = { i, j };
				if (snake.head->coord == food.coord + offset) {
					snake.length += 2;
					snake.AddHead(); snake.AddHead();
					UpdateScore(food);
					UpdateLevel(snake);
					food.ClearBigFood();
					food.exist = false;
					Move_Console(73, 16);
					cout << "                           ";
					Move_Console(73, 17);
					cout << "                           ";
					return true;
				}
			}
		food.step++;
		return false;
	}
	else {
		if (snake.head->coord == food.coord) {
			snake.length++;
			snake.AddHead();
			UpdateScore(food);
			UpdateLevel(snake);
			food.NewFood(snake);
			return true;
		}
		return false;
	}
}


void UpdateScore(const Food& food) {
	if (food.is_big)
		Game::score += 5 * Game::speed * Game::level;
	else
		Game::score += Game::speed * Game::level;
	Move_Console(83, 4);
	cout << Game::score;
}

void UpdateLevel(const Snake& snake) {
	Game::level = snake.length / 10 + 1;
	Move_Console(83, 12);
	cout << Game::level;
}

void Food::NewFood(const Snake& snake) {
	bool flag = true;
	if (is_big) {
		do {
			coord.x = (rand() % (Game::windows_cols - 43)) + 2;
			coord.y = (rand() % (Game::windows_lines - 5)) + 2;
			flag = true;
			for (body* p = snake.head; p != snake.tail; p = p->next)
				if (p->coord == coord) {
					flag = false;
					break;
				}
			if (snake.tail->coord == coord)
				flag = false;
		} while (!flag);
		step = 0;
		exist = true;
	}
	else {
		do {
			coord.x = (rand() % (Game::windows_cols - 40)) + 1;
			coord.y = (rand() % (Game::windows_lines - 2)) + 1;
			flag = true;
			for (body* p = snake.head; p != snake.tail; p = p->next)
				if (p->coord == coord) {
					flag = false;
					break;
				}
			if (snake.tail->coord == coord)
				flag = false;
		} while (!flag);
	}
	PrintFood();
}