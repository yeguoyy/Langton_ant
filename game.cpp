#include "game.h"
#include <iostream>
using namespace std;


void introduction()
{
	cout << "欢迎来到兰顿蚂蚁游戏" << endl;
	cout << "兰顿蚂蚁由黑（#）白（O）格子和一只蚂蚁构成，蚂蚁可在平面正方格上移动。" << endl
		<< "若在白格，则右转90度，将该格改为黑格，并向前移动一步；" << endl
		<< "若在黑格，则左转90度，将该格该为白格，并向前移动一步；" << endl
		<< "若撞墙，则原地不动，自转180度调头但不改变脚下颜色。" << endl;
	cout << "玩家需要根据蚂蚁的最终蚁行图倒推初始图" << endl;
}

bool if_player_win(Map& player_map, Map*& tail_map)
{
	for (int i = 1; i <= player_map.Height; i++)
	{
		for (int j = 1; j <= player_map.Width; j++)
		{
			if (i == Ant::initial_x && j == Ant::initial_y)
			{
				if (player_map.m_map[i][j] != tail_map->Ant_color)				
					return false;				
			}
			else if (player_map.m_map[i][j] != 0 && player_map.m_map[i][j] != 1)
			{
				if (player_map.Ant_color != tail_map->m_map[i][j])
					return false;
			}
			else
			{
				if (player_map.m_map[i][j] != tail_map->m_map[i][j])			
					return false;
			}
		}
	}
	return true;
}
void Sports_process(int goal_step, Map*& head_map, Ant& ant)
{
	head_map->showMap();
	std::cout << "当前蚂蚁脚下颜色为:";
	if (head_map->Ant_color == 0)
	{
		std::cout << "白色" << std::endl;
	}
	else if (head_map->Ant_color == 1)
	{
		std::cout << "黑色" << std::endl;
	}
	system("pause");
	int step = 0;
	while (true)
	{
		step++;
		ant.move(head_map);
		head_map = head_map->nextMap;
		if (step == goal_step)
		{
			break;
		}
	}
}
void S_showMap(const Map& map, sf::RenderWindow& window,int step)
{
	if (step == 1)
	{

	}
}

void Show_process(int goal_step, Map* Tail_map, Ant& ant)
{
	Map* head_map = Tail_map;
	system("cls");
	std::cout << "\033[?25l";//隐藏光标
	while (true)
	{		
		std::cout << "\033[0;0H";//覆盖清屏
		std::cout << "回放功能：" << std::endl;
		head_map->showMap();
		head_map = head_map->nextMap;
		if (head_map == NULL)
		{
			break;
		}
		std::cout << "当前蚂蚁脚下颜色转换，";
		if (head_map->Ant_color == 0)
		{
			std::cout << "变成了白色" << std::endl;
		}
		else if (head_map->Ant_color == 1)
		{
			std::cout << "变成了黑色" << std::endl;
		}
		system("pause");
	}
}
void player_try(Map& player_map, Map*& tail_map)
{
	while (true)
	{
		system("cls");
		player_map.showMap();
		cout << "蚂蚁脚下的颜色为：";
		if (player_map.Ant_color == 0)
		{
			std::cout << "白色" << std::endl;
		}
		else if (player_map.Ant_color == 1)
		{
			std::cout << "黑色" << std::endl;
		}
		if (if_player_win(player_map, tail_map) == true)
		{
			cout << "恭喜你，你赢了！" << endl;
			system("pause");
			return;
		}
		int x, y;
		cout << "请输入你想改变颜色的坐标：" << endl;
		cin >> x >> y;
		if (x > player_map.Width || y > player_map.Height || x < 0 || y < 0)
		{
			cout << "超出地图范围，请重新输入" << endl;
			cin.clear();
			system("pause");
		}
		else if (x == 0 && y == 0)
		{
			cout << "跳过" << endl;
			system("pause");
			return;
		}
		else if (cin.fail())
		{
			cout << "输入错误,请重新输入" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
		}
		else if (x == Ant::Ant_x && y == Ant::Ant_y)
		{
			if (player_map.Ant_color == 0)
			{
				player_map.Ant_color = 1;
			}
			else if (player_map.Ant_color == 1)
			{

				player_map.Ant_color = 0;
			}
		}
		else
		{
			if (player_map.m_map[x][y] == 0)
			{
				player_map.m_map[x][y] = 1;
			}
			else if (player_map.m_map[x][y] == 1)
			{
				player_map.m_map[x][y] = 0;
			}
		}
		
	}
}