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
	Coordinate coord;//食物坐标
	bool is_big;//是否为限时大食物
	int step;//食物生成后蛇移动的步数（用于实现限时食物的消失）
public:
	bool exist;//判断大食物目前是否存在
public:
	Food(bool big);//食物类构造函数，bool型参数判断构造的食物对象为普通食物还是大食物
	void PrintFood();//在屏幕上打印食物
	void ClearBigFood();//清楚大食物
	void BigFoodDisappear();//判断大食物是否应该消失
	void NewFood(const Snake& snake);//重新分配食物的坐标
	friend bool IsFoodEaten(Snake &snake, Food &food);//友元函数，判断食物是否被吃
	friend void UpdateScore(const Food& food);//友元函数，传入食物的类型用于计算新分数
};

#endif