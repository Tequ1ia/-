#include "Food.h"
using namespace std;

//构造函数
Food::Food(bool big) {
	if (!big) {
		coord.x = (rand() % (Game::windows_cols - 40)) + 1;
		coord.y = (rand() % (Game::windows_lines - 2)) + 1;
		while (coord == Coordinate{ 13, 14 } || coord == Coordinate{ 13, 15 } || coord == Coordinate{ 13, 16 }) {
			coord.x = (rand() % (Game::windows_cols - 40)) + 1;
			coord.y = (rand() % (Game::windows_lines - 2)) + 1;
		}
		step = 0;
		is_big = false;
	}
	else {
		step = 0;
		is_big = true;
		exist = false;
	}
	PrintFood();
}

//在屏幕上输出食物
void Food::PrintFood() {
	if (is_big && exist) {
			Move_Console(coord.x - 1, coord.y - 1);
			cout << "@@@";
			Move_Console(coord.x - 1, coord.y);
			cout << "@@@";
			Move_Console(coord.x - 1, coord.y + 1);
			cout << "@@@";
			Move_Console(73, 16);
			cout << "特殊食物出现中！";
			Move_Console(73, 17);
			cout << "特殊食物将在：45步后消失";
	}
	if (!is_big) {
		Move_Console(coord);
		cout << "@";
	}
}


void Food::ClearBigFood() {
	if (exist) {
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				Coordinate offset = { i, j };
				Move_Console(Coordinate{ i,j } +coord);
				cout << " ";
			}
	}
}

void Food::BigFoodDisappear() {
	if (step == 45) {
		ClearBigFood();
		exist = false;
		Move_Console(73, 16);
		cout << "特殊食物已消失      ";
		Move_Console(73, 17);
		cout << "                           ";
		return;
	}
	if (exist) {
		Move_Console(73, 17);
		cout << "特殊食物将在："<< 45 - step << "步后消失";
		return;
	}
}
