#ifndef ANT_H
#define ANT_H
#include "map.h"

enum Direction { DOWN, LEFT, UP, RIGHT };

class Ant
{
public:
	Direction direction;//���Ϸ���
	int Ant_x, Ant_y;//��ǰ��������
    Ant();
	void move(Map*&);
};

void Sports_process(int step,Map*&,Ant&);
#endif 