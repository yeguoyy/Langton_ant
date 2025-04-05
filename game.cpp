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

void player_try(Map& player_map)
{
	while(true)
	{
		system("cls");
		player_map.showMap();
		cout << "蚂蚁脚下的颜色为：";
		if (player_map.Ant_color == 0)
		{
			std::cout << "白色" << std::endl;
		}
		else if (player_map.Ant_color == 8)
		{
			std::cout << "黑色" << std::endl;
		}
		int x, y;
        cout << "请输入你想改变颜色的坐标：" << endl;
        cin >> x >> y;
        if (x > player_map.Width || y > player_map.Height|| x <= 0 || y <= 0)
        {
            cout << "超出地图范围" << endl;
			cin.clear();
        }
		else if (cin.fail())
		{
			cout << "输入错误" << endl;
            cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
            if (player_map.m_map[x][y] == 0)
            {
                player_map.m_map[x][y] = 8;
            }
            else if (player_map.m_map[x][y] == 8)
            {
                player_map.m_map[x][y] = 0;
            }
		}
	}
}