#include "game.h"
#include <iostream>
#include <windows.h>
using namespace std;

//规则说明 撞墙√ 随机生成地图√ 回放功能(延时播放)√  起始位√ 交互 地图保存功能 误输入√ 传送门？障碍物？
//挑战赛（通过改变黑白，以最小的步数让蚂蚁到目标区域）

int main()
{
	Ant ant;
	//该用指针用来读取每一个地图的地址
	Map* head_map = new Map;
	Map* tail_map = new Map;
	sf::Font font;
	if (!font.openFromFile("msyh.ttc"))
	{
		std::cout << "Failed to load font" << std::endl;
		return -1;
	}
	sf::Text Rules(font);
	introduction(Rules);
	sf::RenderWindow window(sf::VideoMode({ 600, 900 }), L"兰顿蚂蚁", sf::Style::Default);
	sf::Texture Start_texture;
	if (!Start_texture.loadFromFile("Start_game_cover.png", false, sf::IntRect({ 0, 0 }, { 1024, 1536 })))//sf::IntRect 类是一个简单的实用类型，表示一个矩形。它的构造函数接受矩形的左上角坐标和大小。
		return -1;
	sf::Sprite Start_game_cover(Start_texture);
	sf::Vector2u original_Start_Size = Start_texture.getSize();
	sf::Vector2f scale_Start_Size = { 600.f / original_Start_Size.x, 900.f / original_Start_Size.y };
	Start_game_cover.setScale(scale_Start_Size);

	HCURSOR customCursor1 = LoadCursorFromFile(L"pointer.cur");//从文件中加载光标
	HCURSOR customCursor2 = LoadCursorFromFile(L"link.cur");//从文件中加载光标
	if (!customCursor1 || !customCursor2) {
		DWORD dwError = GetLastError();
		MessageBox(NULL, L"Failed to load custom cursor", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
	HWND hwnd = FindWindow(NULL, L"兰顿蚂蚁");//获取窗口句柄
	if (!hwnd) {
		MessageBox(NULL, L"Failed to find window", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
	//设置鼠标指针图标
	SetClassLongPtr(hwnd, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(customCursor1));//永久设置鼠标指针图标
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
				if (keyPressed->code == sf::Keyboard::Key::Escape && temp == 2)
				{
					temp++;
					tail_map = head_map;
					int goal_step = 1000;
					Sports_process(goal_step, head_map, ant); //模拟运动
					Map player_map(*head_map);
					//player_try(player_map,tail_map);//玩家尝试
					Show_process(tail_map, ant, s_map, s_ant, window);//展示运动
				}
			}
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())//可用于判断鼠标是否移动到某点
			{
				if (temp == 0)
				{
					if (mouseMoved->position.x >= 87 && mouseMoved->position.x <= 514 && mouseMoved->position.y >= 658 && mouseMoved->position.y <= 784)
					{
						SetCursor(customCursor2);//暂时设置鼠标指针图标
					}
				}
			}
			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())//鼠标按下
			{
					if (mouseButtonPressed->button == sf::Mouse::Button::Left)
					{
						//std::cout << "the Left button was pressed" << std::endl;
						if (mouseButtonPressed->position.x >= 87 && mouseButtonPressed->position.x <= 514 && mouseButtonPressed->position.y >= 658 && mouseButtonPressed->position.y <= 784)
							temp++;
					}
				}

			}

			if (temp == 1)
			{
				if (!chooseMap(head_map, ant, s_map, s_ant, window))
				{
					return 0;
				}
				temp++;
			}
			window.clear();
			// draw the map
			if (temp == 0)
			{
				/*sf::Vector2i globalPosition = sf::Mouse::getPosition();
				cout << "globalPosition.x: " << globalPosition.x << std::endl;
				cout << "globalPosition.y: " << globalPosition.y << std::endl;*/
				window.draw(Start_game_cover);
			}
			else
			{
				window.draw(s_map);
				window.draw(s_ant);
			}
			window.display();
		}

		//test
		system("pause");
		//tail_map->showMap();//可以正常访问第一个地图
		return 0;
	}