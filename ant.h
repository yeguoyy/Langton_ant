#ifndef ANT_H
#define ANT_H
#include "map.h"

enum Direction { DOWN, LEFT, UP, RIGHT };

class Ant
{
public:
	Direction direction;//蚂蚁方向
	static int Ant_x, Ant_y;//当前蚂蚁坐标
	static int initial_x, initial_y;//初始坐标
    Ant();
	void move(Map*&);
};

void Sports_process(int step,Map*&,Ant&);
void Show_process(int step,Map*,Ant&);
#endif 