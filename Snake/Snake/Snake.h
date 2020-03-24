#pragma once
#ifndef _SNAKE_H
#define _SNAKE_H
#include "Game.h"
#include "Food.h"
#include <conio.h>

class Food;
//��������
struct body {
	Coordinate coord;
	body* next;
};

class Snake {
private:
	body* head;//��������ͷ�ڵ�
	body* tail;//��������β���
	direction dir;//��ͷ����
	int length;//�����ȣ����ڼ���ؿ�����
public:
	Snake();
	void AddHead();//����ͷ�巨
	void DelTail();//ɾ��β���
	void PrintSnake();//��ӡ��
	void ListenKeyBoard();//��ȡ��������
	void Move();//�ƶ�һ��
	bool IsSelfEaten();//�Ƿ�Ե��Լ�
	bool IsHitWall();//�Ƿ�ײǽ
	bool IsAlive();//�Ƿ���
	friend void Food::NewFood(const Snake& snake);
	friend bool IsFoodEaten(Snake &snake, Food &food);
	friend void UpdateLevel(const Snake& snake);
};

#endif 
