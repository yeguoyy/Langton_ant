#ifndef ANT_H
#define ANT_H
#include "map.h"

enum Direction { DOWN, LEFT, UP, RIGHT };

class Ant
{
public:
	Direction direction;//���Ϸ���
	static int Ant_x, Ant_y;//��ǰ��������
	static int initial_x, initial_y;//��ʼ����
    Ant();
	void move(Map*&);
};

void Sports_process(int step,Map*&,Ant&);
void Show_process(int step,Map*,Ant&);
#endif 