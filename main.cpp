#include "game.h"
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

#define goal_step 100
using namespace std;

//规则说明√ 撞墙√ 随机生成地图√ 回放功能(延时播放)√  起始位√ 交互√ 误输入√ 传送门？障碍物！胜利动画 重新开始游戏（重置）
//金手指挑战赛（通过改变黑白，以最小的步数让蚂蚁到目标区域，消灭敌人掉落道具、得分）
//道具：（坦克大战）激光√，大小飞弹√，换位（抓取），磁铁，钩爪√
//事件：（随机盒子）敌人生成，阔图，核弹（大范围洗牌），

int main()
{
	srand(time(NULL));
	Ant ant;
	//该用指针用来读取每一个地图的地址
	Map* head_map = new Map;
	Map* tail_map = new Map;
	Map player_map;
	
	sf::RenderWindow window(sf::VideoMode({ 800, 1200 }), L"兰顿蚂蚁", sf::Style::Default);
	sf::Texture Start_texture;
	if (!Start_texture.loadFromFile("context/Start_game_cover.png", false, sf::IntRect({ 0, 0 }, { 1024, 1536 })))//sf::IntRect 类是一个简单的实用类型，表示一个矩形。它的构造函数接受矩形的左上角坐标和大小。
		return -1;
	sf::Sprite Start_game_cover(Start_texture);
	sf::Vector2u original_Start_Size = Start_texture.getSize();
	sf::Vector2f scale_Start_Size = { 800.f / original_Start_Size.x, 1200.f / original_Start_Size.y };
	Start_game_cover.setScale(scale_Start_Size);//设置缩放

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
	sf::VertexArray line(sf::PrimitiveType::LineStrip, 6);
	//链表的头尾结点
	int process = 0;//0 开始游戏界面，1选择地图并预先运算结果，2展示运动
	int if_line = 0;
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
				if (keyPressed->code == sf::Keyboard::Key::Escape)//退出游戏
				{
					process = 4;
				}

				if (keyPressed->code == sf::Keyboard::Key::Enter && process == 3)//回放功能
				{
					//player_try(player_map,tail_map);//玩家尝试
					Show_process(tail_map, ant, s_map, s_ant, window);//展示运动
					process++;
				}
				if (keyPressed->code == sf::Keyboard::Key::U && process <= -2)
				{
					if (ant.num_LaserPointer > 0)
					{
						if_line += 3;
						ant.num_LaserPointer--;
						cout << "激光指示器充电成功！！！" << endl;
						cout << "当前激光指示器电量：" << if_line << endl;
					}
					else
					{
                        cout << "激光指示器用完了！！！" << endl;
						cout << "快去地图中拾取吧 >_<" <<endl;
					}
				}
				if (keyPressed->code == sf::Keyboard::Key::L && process <= -2)
				{
					if (ant.num_falcula > 0)
					{
						sf::Vector2f Position = s_ant.getPosition();
						falcula(ant, head_map, s_map, s_ant, prop_list, window, Position);
						ant.num_falcula--;
					}
					else
					{
						cout << "钩爪用完了！！！" << endl;
						cout << "快去地图中拾取吧 >_<" << endl;
					}
				}
				if (keyPressed->code == sf::Keyboard::Key::Enter && process <= -2)
				{
					cout << "成功跳过操作..." << endl;
					process = -7;
				}
			}
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())//可用于判断鼠标是否移动到某点
			{
				if (process == 0)
				{
					//cout << "鼠标坐标：" << mouseMoved->position.x << " " << mouseMoved->position.y << std::endl;
					if (mouseMoved->position.x >= 160 && mouseMoved->position.x <= 642 && mouseMoved->position.y >= 423 && mouseMoved->position.y <= 555)
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
						if (mouseButtonPressed->position.x >= 160 && mouseButtonPressed->position.x <= 642 && mouseButtonPressed->position.y >= 423 && mouseButtonPressed->position.y <= 555)
							process++;
					}
					if (process == 2)
					{
						if (mouseButtonPressed->position.x >= 0 && mouseButtonPressed->position.y >= 0 && mouseButtonPressed->position.y <= player_map.Height * 100 && mouseButtonPressed->position.x <= player_map.Width * 100)
							process += player_try(player_map, tail_map, s_map, s_ant, (int)mouseButtonPressed->position.x / 100 + 1, (int)mouseButtonPressed->position.y / 100 + 1);//玩家尝试		
						
					}
					if (process <= -2)
					{
						
						if (mouseButtonPressed->position.x >= 0 && mouseButtonPressed->position.y >= 0 && mouseButtonPressed->position.y <= head_map->Height * 100 && mouseButtonPressed->position.x <= head_map->Width * 100)
						{
							process += GoldenFingerMode_player_try(ant,head_map, s_map, s_ant, (int)mouseButtonPressed->position.x / 100 + 1, (int)mouseButtonPressed->position.y / 100 + 1,if_line);
							cout <<"剩余操作次数："<<(process+7)<<"次"<<endl;
							cout<< "按Enter可跳过" << endl;
						}
						Confirm_line(line, *head_map);//计算路径坐标
						
					}
				}
			}
		}

		if (process == 1)
		{
			int choise = chooseMode(head_map, ant, s_map, s_ant, window);
			if (choise == -1)
			{
				return 0;
			}
			else if (choise == 3)
			{
				process = -2;//加入循环
				cout << "黑左白右" << endl;
				cout << "请您点击黑白格子改变蚂蚁的运动轨迹不要让它撞上障碍物！！" << endl;
				tail_map = head_map;
				prop_list.push_back(Prop(5, 5, 0));//创建道具
				prop_list[prop_list.size() - 1].loadmap("tileMap/Prop.png");
			}
			else if (choise == 4)
			{
				process = 4;
			}
			else
			{
				//普通模式
				process++;
				tail_map = head_map;
				Sports_process(goal_step, head_map, ant); //模拟运动
				player_map.copyMap(*head_map);
			}
		}
		else if (process == -7)
		{
			
			GoldenFinger_moveProcess(ant, head_map, s_map, s_ant, prop_list, window,5,process,if_line);//5 步
			if (if_line > 0)//每个回合扣一格电
				if_line--;
			ant.Rounds += 1;
			cout << "激光指示器剩余电量:" << if_line << endl;
			cout << "黑左白右"<<endl;
			cout << "请您点击黑白格子改变蚂蚁的运动轨迹不要让它撞上障碍物！！" << endl;
			Confirm_line(line, *head_map);
		}
		else if (process == 4)//游戏结束重新回到主界面
		{
			delete head_map;
			head_map = new Map;
			ant = Ant();
			player_map = Map();
			for  (int i = 0; i < prop_list.size(); i++)
			{
				prop_list.erase(prop_list.begin() + i);
			}
			if_line = 0;
			process = 0;
			window.setSize(sf::Vector2u(800,1200));//改变窗口大小要注意改变视图中心点
			sf::View view = window.getDefaultView();
			view.setSize(sf::Vector2f(800,1200));
			view.setCenter(sf::Vector2f(400,600)); // 设置视图中心点
			window.setView(view);
			s_map= S_Map();
			s_ant = S_Ant();
			sf::Image image;
			if (!image.loadFromFile("context/Start_game_cover.png"))//普通模式
			{
				system("pause");
				return -1;
			}
			Start_texture.update(image);
			window.clear();
			window.draw(Start_game_cover);
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
			if (if_line!=0)//剩余次数不为0就show线
			window.draw(line);
		}
		window.display();
	}

	system("pause");
	return 0;
}