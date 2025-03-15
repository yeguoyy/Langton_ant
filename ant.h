#pragma once
#include <iostream>

enum Direction { DOWN, LEFT, UP, RIGHT };

class Ant
{
public:
	Direction direction;
    Ant();
	void move(Direction);
};