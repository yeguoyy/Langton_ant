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

#endif 