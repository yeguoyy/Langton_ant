#include "game.h"
#include <iostream>
using namespace std;


void introduction(sf::Text &Rules)
{
	cout << "��ӭ��������������Ϸ" << endl;
	cout << "���������ɺڣ�#���ף�O�����Ӻ�һֻ���Ϲ��ɣ����Ͽ���ƽ�����������ƶ�\n"<<
		"���ڰ׸�����ת90�ȣ����ø��Ϊ�ڸ񣬲���ǰ�ƶ�һ����\n" <<
		"���ںڸ�����ת90�ȣ����ø��Ϊ�׸񣬲���ǰ�ƶ�һ����\n" << 
		"��ײǽ����ԭ�ز�������ת180�ȵ�ͷ�����ı������ɫ��\n" <<
	"�����Ҫ�������ϵ���������ͼ���Ƴ�ʼͼ" << endl;
}

bool if_player_win(Map& player_map, Map*& tail_map)
{
	for (int i = 1; i <= player_map.Width; i++)
	{
		for (int j = 1; j <= player_map.Height; j++)//���ܷ��ˣ�����
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
	std::cout << "��ǰ���Ͻ�����ɫΪ:";
	if (head_map->Ant_color == 0)
	{
		std::cout << "��ɫ" << std::endl;
	}
	else if (head_map->Ant_color == 1)
	{
		std::cout << "��ɫ" << std::endl;
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


void Show_process(Map* Tail_map, Ant& ant,S_Map &s_map,S_Ant &s_ant, sf::RenderWindow&window)
{
	Map* head_map = Tail_map;
	Map *S_head_map = Tail_map;
	int S_step=0;
	system("cls");
	std::cout << "\033[?25l";//���ع��
	while (true)
	{		
  		std::cout << "\033[0;0H";//��������
		std::cout << "�طŹ��ܣ�" << std::endl;
		head_map->showMap();

		if (S_step == 0)
		{
			window.clear();
			window.draw(s_map);
			window.draw(s_ant);
			window.display();
		}
		s_map.S_showMap(S_head_map, S_step);//S_step=0������
		s_ant.S_showAnt(S_head_map);//S_step=0������//
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
int player_try(Map& player_map, Map*& tail_map, S_Map& s_map, S_Ant&s_ant, int x,int y)
{
		
		cout <<x << " " << y << endl;
		cout << "���Ͻ��µ���ɫΪ��";
		if (player_map.Ant_color == 0)
		{
			std::cout << "��ɫ" << std::endl;
		}
		else if (player_map.Ant_color == 1)
		{
			std::cout << "��ɫ" << std::endl;
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
			cout << "��ϲ�㣬��Ӯ�ˣ�" << endl;
			cout << "��Enter����..." << endl;
			return 1;
		}
		return 0;
}
int GoldenFingerMode_player_try(Map*& player_map, S_Map& s_map, S_Ant& s_ant, int x, int y,int times)
{
	cout << x << " " << y << endl;
	cout << "���Ͻ��µ���ɫΪ��";
	if (player_map->Ant_color == 0)
	{
		std::cout << "��ɫ" << std::endl;
	}
	else if (player_map->Ant_color == 1)
	{
		std::cout << "��ɫ" << std::endl;
	}


	if (player_map->m_map[x][y] == 2)
	{
		std::cout << "���ң����ɸ���" << std::endl;
        return 0;
	}
	else if (player_map->m_map[x][y] == 3)
	{
		std::cout << "����ʯ�����ɸ���" << std::endl;
		return 0;
	}
	else if (player_map->m_map[x][y] == 4)
	{
		std::cout << "����ʯ�����ɸ���" << std::endl;
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

void pause(sf::RenderWindow& window)
{
	bool paused = true;
	std::cout << "��������ͣ�����ո������..." << std::endl;
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
				sf::sleep(sf::milliseconds(10));//�����ӳ�
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