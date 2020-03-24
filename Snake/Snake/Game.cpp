#include "Game.h"
//#include <stdlib.h>
using namespace std;

int Game::speed;
int Game::level = 1;
int Game::score = 0;
Rank Game::ranklist[10];

bool Coordinate::operator ==(const Coordinate& coord)const {
	if (this->x == coord.x && this->y == coord.y)
		return true;
	return false;
}

Coordinate Coordinate::operator+(const Coordinate& coord)const {
	return { coord.x + x, coord.y + y };
}

//移动光标位置，实现在(x,y)处输出
void Move_Console(Coordinate coord) {
	COORD pos = { coord.x, coord.y };
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void Move_Console(int x, int y) {
	COORD pos = { x, y };
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void Game::GameInit() {
	//设置游戏窗口大小
	char buffer[40];
	sprintf_s(buffer, "mode con cols=%d lines=%d", windows_cols, windows_lines);
	system(buffer);
	
	//隐藏光标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

	srand((unsigned int)time(0));//初始化随机种子

	score = 0;
}

void Game::PrintFixedElement() {
	for (int i = 0; i < Game::windows_lines; i++) {
		for (int j = 0; j < Game::windows_cols; j++) {
			if (i == 0 || i == Game::windows_lines - 1 || j == 0 || j == Game::windows_cols - 1 || (i == 22 && j >= Game::windows_cols - 39) || j == Game::windows_cols - 39)
				cout << "#";
			else
				cout << " ";
		}
	}
	Move_Console(73, 4);
	cout << "当前得分：" << score;
	Move_Console(73, 8);
	cout << "当前速度：" << speed;
	Move_Console(73, 12);
	cout << "当前关卡：" << level;
	Move_Console(73, 26);
	cout << "游戏操作说明：";
	Move_Console(73, 27);
	cout << "W: 上    S: 下";
	Move_Console(73, 28);
	cout << "A: 左    D: 右";
	Move_Console(73, 32);
	cout << "调节游戏速度：";
	Move_Console(73, 33);
	cout << "+ : 加快";
	Move_Console(73, 34);
	cout << "- : 减慢";
}


void Game::GetPlaySetting() {
	Move_Console(45, 8);
	cout << "贪吃蛇";
	Move_Console(30, 12);
	cout << "在开始游戏前，请把输入法转换至英文输入";
	Move_Console(30, 16);
	cout << "请设置蛇的移动速度(1-10)： ";
	cin >> speed;
	int cnt = 1;
	while (speed > 10 || speed < 1) {
		Move_Console(30, 15 + 3 * cnt);
		cout << "请输入1-10之间的整数！";
		Move_Console(30, 16 + 3 * cnt);
		cout << "请设置蛇的移动速度(1-10)： ";
		cin >> speed;
		cnt++;
	}
}



void Game::UpdateSpeed(bool is_up) {
	if (is_up && speed != 10)
		speed++;
	if (!is_up && speed != 1)
		speed--;
	Move_Console(83, 8);
	cout << speed << "  ";
}

bool Game::GameEnd() {
	Move_Console(45, 8);
	cout << "游戏结束";
	Move_Console(30, 10);
	cout << "你的最终得分为：" << score;
	for (int i = 0; i < 10; i++)
		ranklist[i] = { "", 0 };
	ifstream infile("rank.txt", ios::in);
	if (!infile) {
		infile.close();
	}
	else {
		int temp;
		string buffer;
		for (int i = 0; i < 10; i++) {
			infile >> buffer >> temp;
			if (infile.eof())
				break;
			ranklist[i] = { buffer, temp };
		}
		infile.close();
	}
	for (int i = 0; i < 10; i++) {
		if (score > ranklist[i].score) {
			for (int j = 9; j > i; j--)
				ranklist[j] = ranklist[j - 1];
			ranklist[i].score = score;
			Move_Console(30, 14);
			cout << "恭喜你，进入了排行榜前十，请输入你的昵称: ";
			cin >> ranklist[i].name;
			break;
		}
	}
	Move_Console(42, 17);
	cout << "排行榜";
	for (int i = 0; i < 10; i++) {
		if (ranklist[i].score == 0)
			break;
		Move_Console(35, 19 + i);
		cout << i + 1 << "\t" << ranklist[i].name << "\t" << ranklist[i].score;
	}
	ofstream outfile("rank.txt", ios::out);
	if (!outfile) {
		cout << "error";
		exit(-1);
	}
	for (int i = 0; i < 10; i++) {
		if (ranklist[i].score == 0)
			break;
		outfile << ranklist[i].name << " " << ranklist[i].score << endl;
	}
	outfile.close();
	Move_Console(30, 30);
	cout << "输入1继续游戏，输入0退出游戏: ";
	int x;
	cin >> x;
	if (x == 1)
		return true;
	else
		return false;
}

void Game::ControlGameSpeed() {
	Sleep(120 - 10 * speed);
}

