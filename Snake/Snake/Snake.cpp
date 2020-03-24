#include "Snake.h"
using namespace std;
//构造函数
Snake::Snake() {
	head = new body;
	body* p = new body;
	tail = new body;
	head->coord = { 13, 14 };
	p->coord = { 13, 15 };
	tail->coord = { 13, 16 };
	head->next = p;
	p->next = tail;
	dir = UP;
	length = 3;
	PrintSnake();
}

//使蛇朝着蛇头方向伸长一个单位
void Snake::AddHead() {
	body* p = new body;
	p->coord = head->coord;
	switch (dir) {
	case UP: p->coord.y--; break;
	case DOWN: p->coord.y++; break;
	case RIGHT: p->coord.x++; break;
	case LEFT: p->coord.x--; break;
	}
	p->next = head;
	head = p;
}

//删除蛇尾
void Snake::DelTail() {
	body* p = head;
	while (p->next != tail)
		p = p->next;
	delete tail;
	tail = p;
}

//在屏幕上打印蛇
void Snake::PrintSnake() {
	for (body* p = head; p != tail; p = p->next) {
		Move_Console(p->coord);
		cout << "#";
	}
	Move_Console(tail->coord);
	cout << "#";
}

//通过键盘获取输入，用以改变蛇头方向
void Snake::ListenKeyBoard() {
	char c;
	if (_kbhit()) {
		c = _getch();
		if (c == 'w' || c == 'W') {
			if (dir != DOWN)
				dir = UP;
			return;
		}
		if (c == 's' || c == 'S') {
			if (dir != UP)
				dir = DOWN;
			return;
		}
		if (c == 'a' || c == 'A') {
			if (dir != RIGHT)
				dir = LEFT;
			return;
		}
		if (c == 'd' || c == 'D') {
			if (dir != LEFT)
				dir = RIGHT;
			return;
		}
		if (c == '=') {
			Game::UpdateSpeed(true);
			return;
		}
		if (c == '-') {
			Game::UpdateSpeed(false);
			return;
		}
	}
}

//移动函数 使蛇头朝着所指方向前进一个单位 同时删除尾巴
void Snake::Move() {
	ListenKeyBoard();
	AddHead();
	Move_Console(tail->coord);
	cout << ' ';
	DelTail();
}


//判断是否吃到自己
bool Snake::IsSelfEaten() {
	body* p = head->next;
	while (true) {
		if (head->coord == p->coord)
			return true;
		if (p == tail)
			return false;
		p = p->next;
	}
}

//判断是否撞墙
bool Snake::IsHitWall() {
	if (head->coord.x == 0 || head->coord.x == Game::windows_cols - 39)
		return true;
	if (head->coord.y == 0 || head->coord.y == Game::windows_lines - 1)
		return true;
	return false;
}

//判断是否存活
bool Snake::IsAlive() {
	if (IsSelfEaten() || IsHitWall())
		return false;
	return true;
}
