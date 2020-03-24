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

//�ƶ����λ�ã�ʵ����(x,y)�����
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
	//������Ϸ���ڴ�С
	char buffer[40];
	sprintf_s(buffer, "mode con cols=%d lines=%d", windows_cols, windows_lines);
	system(buffer);
	
	//���ع��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬

	srand((unsigned int)time(0));//��ʼ���������

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
	cout << "��ǰ�÷֣�" << score;
	Move_Console(73, 8);
	cout << "��ǰ�ٶȣ�" << speed;
	Move_Console(73, 12);
	cout << "��ǰ�ؿ���" << level;
	Move_Console(73, 26);
	cout << "��Ϸ����˵����";
	Move_Console(73, 27);
	cout << "W: ��    S: ��";
	Move_Console(73, 28);
	cout << "A: ��    D: ��";
	Move_Console(73, 32);
	cout << "������Ϸ�ٶȣ�";
	Move_Console(73, 33);
	cout << "+ : �ӿ�";
	Move_Console(73, 34);
	cout << "- : ����";
}


void Game::GetPlaySetting() {
	Move_Console(45, 8);
	cout << "̰����";
	Move_Console(30, 12);
	cout << "�ڿ�ʼ��Ϸǰ��������뷨ת����Ӣ������";
	Move_Console(30, 16);
	cout << "�������ߵ��ƶ��ٶ�(1-10)�� ";
	cin >> speed;
	int cnt = 1;
	while (speed > 10 || speed < 1) {
		Move_Console(30, 15 + 3 * cnt);
		cout << "������1-10֮���������";
		Move_Console(30, 16 + 3 * cnt);
		cout << "�������ߵ��ƶ��ٶ�(1-10)�� ";
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
	cout << "��Ϸ����";
	Move_Console(30, 10);
	cout << "������յ÷�Ϊ��" << score;
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
			cout << "��ϲ�㣬���������а�ǰʮ������������ǳ�: ";
			cin >> ranklist[i].name;
			break;
		}
	}
	Move_Console(42, 17);
	cout << "���а�";
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
	cout << "����1������Ϸ������0�˳���Ϸ: ";
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

