#pragma once
#ifndef _GAME_H
#define _GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

struct Coordinate {
	int x;//列坐标
	int y;//行坐标
	bool operator ==(const Coordinate& coord)const;
	Coordinate operator +(const Coordinate& coord)const;
};
enum direction { UP, DOWN, LEFT, RIGHT };
void Move_Console(Coordinate coord);
void Move_Console(int x, int y);
struct Rank {
	std::string name;
	int score;
};

class Food;
class Snake;

class Game {
private:
	static Rank ranklist[10];//储存从文件中读取的历次分数排名
	static int level;//关卡数
	static int score;//得分
	static int speed;//速度
public:
	//游戏窗体的长宽
	static const int windows_cols = 100;
	static const int windows_lines = 40;

	static void GameInit();	//游戏初始化
	static void PrintFixedElement();//打印屏幕上的固定元素，如地图边界和提示语
	static void GetPlaySetting();//获取玩家设置的速度参数
	static bool GameEnd();//游戏结束，在屏幕显示玩家得分，前十排行榜，以及让玩家选择是否继续游戏
	static void ControlGameSpeed();//控制游戏速度
	static void UpdateSpeed(bool is_up);//更新速度
	friend void UpdateScore(const Food& food);//更新分数
	friend void UpdateLevel(const Snake& snake);//更新关卡
};


#endif