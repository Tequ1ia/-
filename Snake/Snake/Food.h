#pragma once
#ifndef _FOOD_H
#define _FOOD_H
#include "Game.h"
#include <stdlib.h>
#include <time.h>

class Snake;
struct body;
class Food {
private:
	Coordinate coord;//ʳ������
	bool is_big;//�Ƿ�Ϊ��ʱ��ʳ��
	int step;//ʳ�����ɺ����ƶ��Ĳ���������ʵ����ʱʳ�����ʧ��
public:
	bool exist;//�жϴ�ʳ��Ŀǰ�Ƿ����
public:
	Food(bool big);//ʳ���๹�캯����bool�Ͳ����жϹ����ʳ�����Ϊ��ͨʳ�ﻹ�Ǵ�ʳ��
	void PrintFood();//����Ļ�ϴ�ӡʳ��
	void ClearBigFood();//�����ʳ��
	void BigFoodDisappear();//�жϴ�ʳ���Ƿ�Ӧ����ʧ
	void NewFood(const Snake& snake);//���·���ʳ�������
	friend bool IsFoodEaten(Snake &snake, Food &food);//��Ԫ�������ж�ʳ���Ƿ񱻳�
	friend void UpdateScore(const Food& food);//��Ԫ����������ʳ����������ڼ����·���
};

#endif