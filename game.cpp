#include "game.h"
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
using namespace std;
sf::Vector2u Prop::map_tileSize = { 100,100 };
sf::Vector2u Prop::prop_tileSize = { 50,50 };

void introduction(sf::Text& Rules)
{
	cout << "欢迎来到兰顿蚂蚁游戏" << endl;
	cout << "兰顿蚂蚁由黑（#）白（O）格子和一只蚂蚁构成，蚂蚁可在平面正方格上移动\n" <<
		"若在白格，则右转90度，将该格改为黑格，并向前移动一步；\n" <<
		"若在黑格，则左转90度，将该格该为白格，并向前移动一步；\n" <<
		"若撞墙，则原地不动，自转180度调头但不改变脚下颜色。\n" <<
		"玩家需要根据蚂蚁的最终蚁行图倒推初始图" << endl;
}

bool if_player_win(Map& player_map, Map*& tail_map)
{
	for (int i = 1; i <= player_map.Width; i++)
	{
		for (int j = 1; j <= player_map.Height; j++)//不能反了！！！
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
	//system("pause");
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


void Show_process(Map* Tail_map, Ant& ant, S_Map& s_map, S_Ant& s_ant, sf::RenderWindow& window)
{
	Map* head_map = Tail_map;
	Map* S_head_map = Tail_map;
	int S_step = 0;
	system("cls");
	std::cout << "\033[?25l";//隐藏光标
	while (true)
	{
		std::cout << "\033[0;0H";//覆盖清屏
		std::cout << "回放功能：" << std::endl;
		head_map->showMap();

		if (S_step == 0)
		{
			window.clear();
			window.draw(s_map);
			window.draw(s_ant);
			window.display();
		}
		s_map.S_showMap(S_head_map, S_step);//S_step=0不运行
		s_ant.S_showAnt(S_head_map);//S_step=0不运行//
		window.clear();
		window.draw(s_map);
		window.draw(s_ant);
		window.display();

		S_head_map = S_head_map->nextMap;
		head_map = head_map->nextMap;
		S_step++;

		if (head_map == NULL)
		{
			break;
		}
		pause(window);
	}
}
int player_try(Map& player_map, Map*& tail_map, S_Map& s_map, S_Ant& s_ant, int x, int y)
{

	cout << x << " " << y << endl;
	cout << "蚂蚁脚下的颜色为：";
	if (player_map.Ant_color == 0)
	{
		std::cout << "白色" << std::endl;
	}
	else if (player_map.Ant_color == 1)
	{
		std::cout << "黑色" << std::endl;
	}

	if (x == Ant::Ant_x && y == Ant::Ant_y)
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
	player_map.showMap();
	s_map.S_showMap(&player_map, 0);
	s_ant.S_showAnt(&player_map);
	if (if_player_win(player_map, tail_map) == true)
	{
		cout << "恭喜你，你赢了！" << endl;
		cout << "按Enter继续..." << endl;
		return 1;
	}
	return 0;
}
int GoldenFingerMode_player_try(Map*& player_map, S_Map& s_map, S_Ant& s_ant, int x, int y, int times)
{
	cout << x << " " << y << endl;
	cout << "蚂蚁脚下的颜色为：";
	if (player_map->Ant_color == 0)
	{
		std::cout << "白色" << std::endl;
	}
	else if (player_map->Ant_color == 1)
	{
		std::cout << "黑色" << std::endl;
	}


	if (player_map->m_map[x][y] == 2)
	{
		std::cout << "熔岩，不可更改" << std::endl;
		return 0;
	}
	else if (player_map->m_map[x][y] == 3)
	{
		std::cout << "大理石，不可更改" << std::endl;
		return 0;
	}
	else if (player_map->m_map[x][y] == 4)
	{
		std::cout << "黑曜石，不可更改" << std::endl;
		return 0;
	}

	if (x == Ant::Ant_x && y == Ant::Ant_y)
	{
		if (player_map->Ant_color == 0)
		{
			player_map->Ant_color = 1;
		}
		else if (player_map->Ant_color == 1)
		{
			player_map->Ant_color = 0;
		}
	}
	else
	{
		if (player_map->m_map[x][y] == 0)
		{
			player_map->m_map[x][y] = 1;
		}
		else if (player_map->m_map[x][y] == 1)
		{
			player_map->m_map[x][y] = 0;
		}
	}
	player_map->showMap();
	s_map.S_showMap(player_map, 0);
	s_ant.S_showAnt(player_map);
	return -1;
}

int GoldenFinger_move(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window)
{
	/*Sleep(500);*/
	if (ant.move(head_map) == -1)
	{
		std::cout << "撞到障碍物了！" << std::endl;
		return -1;
	}

	head_map = head_map->nextMap;
	head_map->showMap();
	s_map.S_showMap(head_map, 0);
	s_ant.S_showAnt(head_map);
	window.clear();
	window.draw(s_map);
	window.draw(s_ant);
	//捡道具
	for (int i = 0; i < prop_list.size(); i++)
	{
		if (head_map->M_ant_x == prop_list[i].getX() && head_map->M_ant_y == prop_list[i].getY())
		{
			int type = prop_list[i].getType();
			prop_list.erase(prop_list.begin() + i);
			for (int i = 0; i < prop_list.size(); i++)
			{
				window.draw(prop_list[i]);
			}
			window.display();
			return type;
		}
	}
	for (int i = 0; i < prop_list.size(); i++)
	{
		window.draw(prop_list[i]);
	}
	window.display();
	return 8;
}

void rocket(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window)//小火箭
{
	sf::Texture rocketTexture;
	if (!rocketTexture.loadFromFile("prop/rocket.png"))
	{
		std::cerr << "Failed to load rocket texture" << std::endl;
		return;
	}
	sf::Sprite rocketSprite(rocketTexture);
	rocketSprite.setOrigin(sf::Vector2f{ 50.f, 50.f });
	rocketSprite.setRotation(head_map->m_degree);
	sf::Vector2f rocketPosition(ant.Ant_x * 100 - 50, ant.Ant_y * 100 - 50);
	rocketSprite.setPosition(rocketPosition);
	while (true)
	{
		switch (ant.direction)//控制速度
		{
		case Direction::UP:
			rocketPosition.y -= 0.08;
			break;
		case Direction::DOWN:
			rocketPosition.y += 0.08;
			break;
		case Direction::LEFT:
			rocketPosition.x -= 0.08;
			break;
		case Direction::RIGHT:
			rocketPosition.x += 0.08;
			break;
		}
		rocketSprite.setPosition(rocketPosition);
		window.draw(s_map);
		window.draw(s_ant);
		for (int i = 0; i < prop_list.size(); i++)
		{
			window.draw(prop_list[i]);
		}
		window.draw(rocketSprite);
		window.display();
		if (rocketPosition.x >= 100 * head_map->Width || rocketPosition.y >= 100 * head_map->Height || rocketPosition.x <= 0 || rocketPosition.y <= 0)
		{
			break;
		}
		if (head_map->m_map[(int)rocketPosition.x / 100 + 1][(int)rocketPosition.y / 100 + 1] == 3 || head_map->m_map[(int)rocketPosition.x / 100 + 1][(int)rocketPosition.y / 100 + 1] == 4)
		{
			head_map->m_map[(int)rocketPosition.x / 100 + 1][(int)rocketPosition.y / 100 + 1] -= 3;
			s_map.S_showMap(head_map, 0);
			window.draw(s_map);
			window.draw(s_ant);
			for (int i = 0; i < prop_list.size(); i++)
			{
				window.draw(prop_list[i]);
			}
			window.draw(rocketSprite);
			window.display();
			break;
		}
	}
}

void big_rocket(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window)//小火箭
{
	sf::Texture big_rocketTexture;
	if (!big_rocketTexture.loadFromFile("prop/big_rocket.png"))
	{
		std::cerr << "Failed to load big_rocket texture" << std::endl;
		return;
	}
	sf::Sprite rocketSprite(big_rocketTexture);
	rocketSprite.setOrigin(sf::Vector2f{ 50.f, 50.f });
	rocketSprite.setRotation(head_map->m_degree);
	sf::Vector2f rocketPosition(ant.Ant_x * 100 - 50, ant.Ant_y * 100 - 50);
	rocketSprite.setPosition(rocketPosition);
	while (true)
	{
		switch (ant.direction)
		{
		case Direction::UP:
			rocketPosition.y -= 0.08;//控制速度
			break;
		case Direction::DOWN:
			rocketPosition.y += 0.08;
			break;
		case Direction::LEFT:
			rocketPosition.x -= 0.08;
			break;
		case Direction::RIGHT:
			rocketPosition.x += 0.08;
			break;
		}
		rocketSprite.setPosition(rocketPosition);
		window.draw(s_map);
		window.draw(s_ant);
		for (int i = 0; i < prop_list.size(); i++)
		{
			window.draw(prop_list[i]);
		}
		window.draw(rocketSprite);
		window.display();
		if (rocketPosition.x >= 100 * head_map->Width || rocketPosition.y >= 100 * head_map->Height || rocketPosition.x <= 0 || rocketPosition.y <= 0)
		{
			break;
		}
		if (head_map->m_map[(int)rocketPosition.x / 100 + 1][(int)rocketPosition.y / 100 + 1] == 3 || head_map->m_map[(int)rocketPosition.x / 100 + 1][(int)rocketPosition.y / 100 + 1] == 4)
		{
			int x = (int)rocketPosition.x / 100 + 1;
			int y = (int)rocketPosition.y / 100 + 1;
			for (int i = x - 1; i <= x + 1; i++)
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					if (i <= 0 || j <= 0 || i > head_map->Height || j > head_map->Width)
					{
						continue;
					}
					else if (head_map->m_map[i][j] == 3 || head_map->m_map[i][j] == 4)
					{
						head_map->m_map[i][j] -= 3;
					}
				}
			}
			s_map.S_showMap(head_map, 0);
			window.draw(s_map);
			window.draw(s_ant);
			for (int i = 0; i < prop_list.size(); i++)
			{
				window.draw(prop_list[i]);
			}
			window.draw(rocketSprite);
			window.display();
			break;
		}
	}
}

void GoldenFinger_moveProcess(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window, int step, int& process)
{
	for (int j = 1; j <= step; j++)
	{
		//先输出一遍
		s_map.S_showMap(head_map, 0);
		s_ant.S_showAnt(head_map);
		window.draw(s_map);
		window.draw(s_ant);
		for (int i = 0; i < prop_list.size(); i++)
		{
			window.draw(prop_list[i]);
		}
		window.display();
		auto start = std::chrono::steady_clock::now(); // 获取起始时间
		auto end = start + std::chrono::milliseconds(500); // 设置目标时间（5秒后）
		while (std::chrono::steady_clock::now() < end)
		{
			while (const std::optional event = window.pollEvent())
			{
				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
				{
					if (keyPressed->code == sf::Keyboard::Key::Space)
					{
						cout << "按下了空格" << endl;
						rocket(ant, head_map, s_map, s_ant, prop_list, window);
					}
					else if (keyPressed->code == sf::Keyboard::Key::LShift)
					{
						cout << "按下了LShift" << endl;
						big_rocket(ant, head_map, s_map, s_ant, prop_list, window);
					}
				}

			}
			std::cout << "Looping..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 暂停100毫秒，避免CPU占用过高
		}
		int temp = GoldenFinger_move(ant, head_map, s_map, s_ant, prop_list, window);//5 步
		if (temp == -1)//自带show和draw
		{
			process = -1;//-1 结束游戏
			pause(window);
			return;
		}
		else
		{
			if (temp == 0)
			{
				cout << "你拾取了火箭弹！！！" << endl;
			}
			else if (temp == 1)
			{
				cout << "你拾取了激光指示器！！！" << endl;
			}
			if (j == 5)
			{
				head_map->creatBarLava();
				head_map->creatBarStone();
				s_map.S_showMap(head_map, 0);
				process = -2;
			}
		}
	}
}

void pause(sf::RenderWindow& window)
{
	bool paused = true;
	std::cout << "程序已暂停，按空格键继续..." << std::endl;
	while (paused)
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				return;
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->code == sf::Keyboard::Key::Space)
				{
					paused = false;
					break;
				}
				sf::sleep(sf::milliseconds(10));//短暂延迟
			}
		}
	}
}
sf::Angle Way_to_Degree(Direction direction)
{
	switch (direction) {
	case UP:
		return sf::degrees(0.0f);
	case RIGHT:
		return sf::degrees(90.0f);
	case DOWN:
		return sf::degrees(180.0f);
	case LEFT:
		return sf::degrees(270.0f);
	}
}

