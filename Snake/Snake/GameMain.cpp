#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include "Integration.h"
#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
	bool flag = true;
	while (flag) {
		Game::GameInit();
		Game::GetPlaySetting();
		Game::PrintFixedElement();
		Snake snake;
		Food food(false), bigfood(true);
		int cnt = 0;
		while (true) {
			snake.Move();
			if (!snake.IsAlive())
				break;
			if (IsFoodEaten(snake, food))
				cnt++;
			IsFoodEaten(snake, bigfood);
			if (cnt == 5 && !bigfood.exist) {
				bigfood.NewFood(snake);
				cnt -= 5;
			}
			snake.PrintSnake();
			bigfood.BigFoodDisappear();
			Game::ControlGameSpeed();
		}
		system("cls");
		flag = Game::GameEnd();
	}
	return 0;
}