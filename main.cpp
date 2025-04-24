#include "game.h"
#include <iostream>
//#include <windows.h>
using namespace std;

//规则说明√ 撞墙√ 随机生成地图 回放功能(延时播放)√  起始位√ 交互√ 地图保存功能 误输入√ 传送门？障碍物？
//挑战赛（通过改变黑白，以最小的步数让蚂蚁到目标区域）

int main()
{
	introduction();
	Ant ant;
	//该用指针用来读取每一个地图的地址
	Map *head_map=new Map;
	Map *tail_map=new Map;
	sf::RenderWindow window(sf::VideoMode({ 500, 500 }), L"兰顿蚂蚁",sf::Style::Default);
	//// 获取窗口句柄
	//const wchar_t* windowTitle = L"兰顿蚂蚁";
	//HWND hwnd = FindWindow(NULL, windowTitle);
	//if (hwnd != NULL)
	//{
	//	std::cout << "窗口句柄已找到，句柄值: " << hwnd << std::endl;

	//	// 将窗口置于前台
	//	SetForegroundWindow(hwnd);
	//}
	//else
	//{
	//	std::cerr << "无法找到窗口句柄" << std::endl;
	//}



	S_Map s_map;
	S_Ant s_ant;
	//链表的头尾结点
	if (!chooseMap(head_map,ant,s_map,s_ant,window))
	{
		return 0;
	}
	int temp = 0;
	while (window.isOpen())
	{
		// handle events
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				return 0;
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				
				if (keyPressed->code == sf::Keyboard::Key::Escape&&temp==0)
				{
					temp = 1;
					tail_map = head_map;
					int goal_step = 1000;
					Sports_process(goal_step, head_map, ant); //模拟运动
					Map player_map(*head_map);
					//player_try(player_map,tail_map);//玩家尝试
					Show_process(tail_map, ant,s_map,s_ant,window);//展示运动
				}
			}

		}

		// draw the map
		window.clear();
		window.draw(s_map);
		window.draw(s_ant);
		window.display();
	}
	
	//test
    system("pause");
	//tail_map->showMap();//可以正常访问第一个地图
	return 0;
}