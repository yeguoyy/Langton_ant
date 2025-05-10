#include "game.h"
#include <iostream>
#include <Windows.h>
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

int GoldenFinger_move(Ant& ant, Map*& head_map, int step, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window)
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
	for (int i = 0; i < step; i++)
	{
		Sleep(500);
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
		for (int i = 0; i < prop_list.size(); i++)
		{
			window.draw(prop_list[i]);
		}
		window.display();
	}
	return 0;
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

Prop::Prop(int x, int y)
{
	m_x = x;
	m_y = y;
}

bool Prop::loadmap(const std::filesystem::path& tileset)
{
	if (!m_tileset.loadFromFile(tileset))//读取Ant纹理
		return false;
	m_prop.setPrimitiveType(sf::PrimitiveType::Triangles);//设置顶点类型
	m_prop.resize(6);//顶点数组的大小为宽度和高度乘积的6倍，因为每个单元格由两个三角形（六个点）组成
	int x = m_x-1;
    int y = m_y-1;
	sf::Vertex* triangles = &m_prop[0];
	triangles[0].position = sf::Vector2f(x * map_tileSize.x+ prop_tileSize.x/2, y * map_tileSize.y+ prop_tileSize.y/2);
	triangles[1].position = sf::Vector2f((x + 1) * map_tileSize.x- prop_tileSize.x/2, y * map_tileSize.y+ prop_tileSize.y/2);
	triangles[2].position = sf::Vector2f(x * map_tileSize.x+ prop_tileSize.x/2, (y + 1) * map_tileSize.y- prop_tileSize.y/2);
	triangles[3].position = sf::Vector2f(x * map_tileSize.x + prop_tileSize.x / 2, (y + 1) * map_tileSize.y - prop_tileSize.y / 2);
	triangles[4].position = sf::Vector2f((x + 1) * map_tileSize.x- prop_tileSize.x/2, y * map_tileSize.y+ prop_tileSize.y/2);
	triangles[5].position = sf::Vector2f((x + 1) * map_tileSize.x- prop_tileSize.x/2, (y + 1) * map_tileSize.y- prop_tileSize.y/2);

	triangles[0].texCoords = sf::Vector2f(0 * prop_tileSize.x, 0 * prop_tileSize.y);
	triangles[1].texCoords = sf::Vector2f((0 + 1) * prop_tileSize.x, 0 * prop_tileSize.y);
	triangles[2].texCoords = sf::Vector2f(0 * prop_tileSize.x, (0 + 1) * prop_tileSize.y);
	triangles[3].texCoords = sf::Vector2f(0 * prop_tileSize.x, (0 + 1) * prop_tileSize.y);
	triangles[4].texCoords = sf::Vector2f((0 + 1) * prop_tileSize.x, 0 * prop_tileSize.y);
	triangles[5].texCoords = sf::Vector2f((0 + 1) * prop_tileSize.x, (0 + 1) * prop_tileSize.y);

	sf::Vector2f position = sf::Vector2f((x + 0.5) * map_tileSize.x, (y + 0.5) * map_tileSize.y);
	this->setOrigin(position);
	this->setPosition(position);
	return true;
}

void Prop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_prop, states);
}