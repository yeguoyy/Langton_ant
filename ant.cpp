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
	}//分配内存
	//NewMap->m_map= map->m_map;//复制原图 浅拷贝！！！！
	//因为这个是动态内存分配，这样复制相当于所有的指针都指向同一块内存，所以修改其中一个指针，另一个指针也会改变
	for (int i = 1; i <= NewMap->Width; i++)
	{
		for (int j = 1; j <= NewMap->Height; j++)
		{
			NewMap->m_map[i][j] = map->m_map[i][j];
		}
	}//复制原图

	NewMap->m_map[Ant_x][Ant_y] = map->Ant_color;//将蚂蚁脚下的方块赋给新图
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
	//位置超出边界,掉头并颜色翻转
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
		//颜色翻转和转弯（白右黑左）
		if (NewMap->m_map[Ant_x][Ant_y] == 0) {
			NewMap->Ant_color = 8;//颜色翻转
			if (direction == RIGHT)
			{
				direction = DOWN;
			}
			else {
				direction = (Direction)((int)direction + 1);
			}
		}
		else if (NewMap->m_map[Ant_x][Ant_y] == 8) {
			NewMap->Ant_color = 0;//颜色翻转
			if (direction == DOWN)
			{
				direction = RIGHT;
			}
			else {
				direction = (Direction)((int)direction - 1);
			}
		}
		//前进后位置图标改变
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
	map->nextMap = NewMap;//将新图赋给nextMap
}
void Sports_process(int goal_step, Map*& head_map, Ant& ant)
{
	int step = 0;
	std::cout << "\033[?25l";//隐藏光标
	while (true)
	{
		step++;
		if (step == goal_step)
		{
			break;
		}
		system("pause");
		std::cout << "\033[0;0H";//覆盖清屏
		ant.move(head_map);
		head_map = head_map->nextMap;
		head_map->showMap();
		std::cout << "当前蚂蚁脚下颜色转换，";
		if (head_map->Ant_color == 0)
		{
			std::cout << "变成了白色" << std::endl;
		}
		else if (head_map->Ant_color == 8)
		{
			std::cout << "变成了黑色" << std::endl;
		}
	}
}
