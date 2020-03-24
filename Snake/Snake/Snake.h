#pragma once
#ifndef _SNAKE_H
#define _SNAKE_H
#include "Game.h"
#include "Food.h"
#include <conio.h>

class Food;
//蛇身链表
struct body {
	Coordinate coord;
	body* next;
};

class Snake {
private:
	body* head;//蛇身链表头节点
	body* tail;//蛇身链表尾结点
	direction dir;//蛇头方向
	int length;//蛇身长度（用于计算关卡数）
public:
	Snake();
	void AddHead();//链表头插法
	void DelTail();//删除尾结点
	void PrintSnake();//打印蛇
	void ListenKeyBoard();//获取键盘输入
	void Move();//移动一次
	bool IsSelfEaten();//是否吃到自己
	bool IsHitWall();//是否撞墙
	bool IsAlive();//是否存活
	friend void Food::NewFood(const Snake& snake);
	friend bool IsFoodEaten(Snake &snake, Food &food);
	friend void UpdateLevel(const Snake& snake);
};

#endif 
