#include "game.h"
#include <iostream>
#include <windows.h>
#define goal_step 1000
using namespace std;

//规则说明 撞墙√ 随机生成地图√ 回放功能(延时播放)√  起始位√ 交互√ 地图保存功能 误输入√ 传送门？障碍物！胜利动画 重新开始游戏（重置）
//金手指挑战赛（通过改变黑白，以最小的步数让蚂蚁到目标区域，消灭敌人掉落道具、得分）
//道具：（坦克大战）激光，飞弹，换位（抓取），磁铁，
//事件：（随机盒子）敌人生成，阔图，核弹（大范围洗牌），

int main()
{
	Ant ant;
	//该用指针用来读取每一个地图的地址
	Map* head_map = new Map;
	Map* tail_map = new Map;
	Map player_map;
	
	sf::Font font;
	if (!font.openFromFile("TTC/msyh.ttc"))
	{
		std::cout << "Failed to load font" << std::endl;
		return -1;
	}
	sf::Text Rules(font);
	introduction(Rules);
	sf::RenderWindow window(sf::VideoMode({ 600, 900 }), L"兰顿蚂蚁", sf::Style::Default);
	sf::Texture Start_texture;
	if (!Start_texture.loadFromFile("context/Start_game_cover.png", false, sf::IntRect({ 0, 0 }, { 1024, 1536 })))//sf::IntRect 类是一个简单的实用类型，表示一个矩形。它的构造函数接受矩形的左上角坐标和大小。
		return -1;
	sf::Sprite Start_game_cover(Start_texture);
	sf::Vector2u original_Start_Size = Start_texture.getSize();
	sf::Vector2f scale_Start_Size = { 600.f / original_Start_Size.x, 900.f / original_Start_Size.y };
	Start_game_cover.setScale(scale_Start_Size);

	HCURSOR customCursor1 = LoadCursorFromFile(L"material/Vision Cursor White/pointer.cur");//从文件中加载光标
	HCURSOR customCursor2 = LoadCursorFromFile(L"material/Vision Cursor White/link.cur");//从文件中加载光标
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
	vector<Prop> prop_list;
	//链表的头尾结点
	int process = 0;//0 开始游戏界面，1选择地图并预先运算结果，2展示运动
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
				if (keyPressed->code == sf::Keyboard::Key::Tab)
				{
					process++;
				}

				if (keyPressed->code == sf::Keyboard::Key::Enter && process == 3)
				{
					//player_try(player_map,tail_map);//玩家尝试
					Show_process(tail_map, ant, s_map, s_ant, window);//展示运动
					process++;
				}
			}
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())//可用于判断鼠标是否移动到某点
			{
				if (process == 0)
				{
					//cout << "鼠标坐标：" << mouseMoved->position.x << " " << mouseMoved->position.y << std::endl;
					if (mouseMoved->position.x >= 128 && mouseMoved->position.x <= 475 && mouseMoved->position.y >= 325 && mouseMoved->position.y <= 410)
					{
						
						SetCursor(customCursor2);//暂时设置鼠标指针图标
					}
				}
			}
			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())//鼠标按下
			{
				if (mouseButtonPressed->button == sf::Mouse::Button::Left)
				{
					if (process == 0)
					{
						if (mouseButtonPressed->position.x >= 128 && mouseButtonPressed->position.x <= 475 && mouseButtonPressed->position.y >= 325 && mouseButtonPressed->position.y <= 410)
							process++;
					}
					if (process == 2)
					{
						if(mouseButtonPressed->position.x>=0&&mouseButtonPressed->position.y>=0&& mouseButtonPressed->position.y<=player_map.Height*100&&mouseButtonPressed->position.x<=player_map.Width*100)
							process+=player_try(player_map, tail_map, s_map,s_ant,(int)mouseButtonPressed->position.x/100+1, (int)mouseButtonPressed->position.y/100+1);//玩家尝试		
						//tail_map->showMap();
					}
					if (process <= -2)
					{
						if (mouseButtonPressed->position.x >= 0 && mouseButtonPressed->position.y >= 0 && mouseButtonPressed->position.y <= head_map->Height * 100 && mouseButtonPressed->position.x <= head_map->Width * 100)
						{
								process+=GoldenFingerMode_player_try(head_map, s_map, s_ant, (int)mouseButtonPressed->position.x / 100 + 1, (int)mouseButtonPressed->position.y / 100 + 1,5);
						}
					}
				}
			}
		}

		if (process == 1)
		{
			int choise= chooseMode(head_map, ant, s_map, s_ant, window);
			if (choise==-1)
			{
				return 0;
			}
			else if (choise == 3)
			{
				process=-2;
				tail_map = head_map;
				prop_list.push_back(Prop(5, 5));
				prop_list[0].loadmap("tileMap/Prop.png");
				//Sports_process(goal_step, head_map, ant); //模拟运动
				//player_map.copyMap(*head_map);
			}
			else
			{
				process++;
				tail_map = head_map;
				Sports_process(goal_step, head_map, ant); //模拟运动
				player_map.copyMap(*head_map);
			}
		}
		else if (process == -7)
		{
			if (GoldenFinger_move(ant, head_map, 5, s_map, s_ant,prop_list, window) == -1)//自带show和draw
			{
				process = -1;//-1 结束游戏
                pause(window);
			}
			else
			{
				
				head_map->creatBarLava();
				head_map->creatBarStone();
				s_map.S_showMap(head_map, 0);
				process = -2;
			}
		}
		window.clear();
		// draw the map
		if (process == 0)
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
			for (int i = 0; i < prop_list.size(); i++)
			{
				window.draw(prop_list[i]);
			}
		}
		window.display();
	}

	//test
	system("pause");
	//tail_map->showMap();//可以正常访问第一个地图
	return 0;
}