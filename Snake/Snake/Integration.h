#pragma once
#ifndef _INTEGRATION_H
#define _INTEGRATION_H

#include "Food.h"
#include "Snake.h"
#include "Game.h"

bool IsFoodEaten(Snake& snake, Food& food);
void UpdateScore(const Food& food);
#endif 
