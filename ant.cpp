#include "ant.h"
#include <iostream>


Ant::Ant() {
	direction = DOWN;
	Ant_x = 5;
	Ant_y = 5;
}

void Ant::move(Map*& map)
{
	Map* NewMap = new Map;
	NewMap->Height = map->Height;
	NewMap->Width = map->Width;
	NewMap->m_map = new int* [NewMap->Width + 1];
	for (int i = 1; i <= NewMap->Width; i++) 
	{
		NewMap->m_map[i] = new int[NewMap->Height + 1];
	}//�����ڴ�
	//NewMap->m_map= map->m_map;//����ԭͼ ǳ������������
	//��Ϊ����Ƕ�̬�ڴ���䣬���������൱�����е�ָ�붼ָ��ͬһ���ڴ棬�����޸�����һ��ָ�룬��һ��ָ��Ҳ��ı�
	for (int i = 1; i <= NewMap->Width; i++)
	{
		for (int j = 1; j <= NewMap->Height; j++)
		{
			NewMap->m_map[i][j] = map->m_map[i][j];
		}
	}//����ԭͼ

	NewMap->m_map[Ant_x][Ant_y] = map->Ant_color;//�����Ͻ��µķ��鸳����ͼ
	int new_x=Ant_x;
	int new_y=Ant_y;

	switch (direction) {
	case DOWN:
		new_y++;
		break;
	case LEFT:
		new_x--;
		break;
	case RIGHT:
		new_x++;
		break;
	case UP:
		new_y--;
		break;
	}
	//λ�ó����߽�,��ͷ����ɫ��ת
	if (new_x < 1 || new_x > NewMap->Width || new_y < 1 || new_y > NewMap->Height)
	{
		switch(direction)
		{
		case UP:
			direction = DOWN;
			NewMap->m_map[Ant_x][Ant_y] = 2;
			break;
		case DOWN:
            direction = UP;
			NewMap->m_map[Ant_x][Ant_y] = 1;
			break;
		case LEFT:
            direction = RIGHT;
			NewMap->m_map[Ant_x][Ant_y] = 4;
			break;
		case RIGHT:
            direction = LEFT;
			NewMap->m_map[Ant_x][Ant_y] = 3;
			break;
		}
	}
	else {
		Ant_x=new_x;
        Ant_y=new_y;
		//��ɫ��ת��ת�䣨���Һ���
		if (NewMap->m_map[Ant_x][Ant_y] == 0) {
			NewMap->Ant_color = 8;//��ɫ��ת
			if (direction == RIGHT)
			{
				direction = DOWN;
			}
			else {
				direction = (Direction)((int)direction + 1);
			}
		}
		else if (NewMap->m_map[Ant_x][Ant_y] == 8) {
			NewMap->Ant_color = 0;//��ɫ��ת
			if (direction == DOWN)
			{
				direction = RIGHT;
			}
			else {
				direction = (Direction)((int)direction - 1);
			}
		}
		//ǰ����λ��ͼ��ı�
		switch (direction) {
		case UP:
			NewMap->m_map[Ant_x][Ant_y] = 1;
			break;
		case DOWN:
			NewMap->m_map[Ant_x][Ant_y] = 2;
			break;
		case LEFT:
			NewMap->m_map[Ant_x][Ant_y] = 3;
			break;
		case RIGHT:
			NewMap->m_map[Ant_x][Ant_y] = 4;
			break;
		}
	}
	map->nextMap = NewMap;//����ͼ����nextMap
}
void Sports_process(int goal_step, Map*& head_map, Ant& ant)
{
	int step = 0;
	std::cout << "\033[?25l";//���ع��
	while (true)
	{
		step++;
		if (step == goal_step)
		{
			break;
		}
		system("pause");
		std::cout << "\033[0;0H";//��������
		ant.move(head_map);
		head_map = head_map->nextMap;
		head_map->showMap();
		std::cout << "��ǰ���Ͻ�����ɫת����";
		if (head_map->Ant_color == 0)
		{
			std::cout << "����˰�ɫ" << std::endl;
		}
		else if (head_map->Ant_color == 8)
		{
			std::cout << "����˺�ɫ" << std::endl;
		}
	}
}
