#pragma once
#ifndef _GAME_H
#define _GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

struct Coordinate {
	int x;//������
	int y;//������
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
	static Rank ranklist[10];//������ļ��ж�ȡ�����η�������
	static int level;//�ؿ���
	static int score;//�÷�
	static int speed;//�ٶ�
public:
	//��Ϸ����ĳ���
	static const int windows_cols = 100;
	static const int windows_lines = 40;

	static void GameInit();	//��Ϸ��ʼ��
	static void PrintFixedElement();//��ӡ��Ļ�ϵĹ̶�Ԫ�أ����ͼ�߽����ʾ��
	static void GetPlaySetting();//��ȡ������õ��ٶȲ���
	static bool GameEnd();//��Ϸ����������Ļ��ʾ��ҵ÷֣�ǰʮ���а��Լ������ѡ���Ƿ������Ϸ
	static void ControlGameSpeed();//������Ϸ�ٶ�
	static void UpdateSpeed(bool is_up);//�����ٶ�
	friend void UpdateScore(const Food& food);//���·���
	friend void UpdateLevel(const Snake& snake);//���¹ؿ�
};


#endif