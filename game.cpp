#include "game.h"
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
using namespace std;
sf::Vector2u Prop::map_tileSize = { 100,100 };
sf::Vector2u Prop::prop_tileSize = { 50,50 };


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
	////��ʾ�𰸵�ͼ
	//head_map->showMap();
	//std::cout << "��ǰ���Ͻ�����ɫΪ:";
	//if (head_map->Ant_color == 0)
	//{
	//	std::cout << "��ɫ" << std::endl;
	//}
	//else if (head_map->Ant_color == 1)
	//{
	//	std::cout << "��ɫ" << std::endl;
	//}
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
	std::cout << "\033[?25l";//���ع��
	while (true)
	{
		std::cout << "\033[0;0H";//������ƶ�����0��0��
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
int player_try(Map& player_map, Map*& tail_map, S_Map& s_map, S_Ant& s_ant, int x, int y)
{
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
	s_map.S_showMap(&player_map, 0);
	s_ant.S_showAnt(&player_map);
	if (if_player_win(player_map, tail_map) == true)
	{
		cout << "��ϲ�㣬��Ӯ�ˣ�" << endl;//��ͨģʽʤ��
		cout << "��Enter����..." << endl;
		return 1;
	}
	return 0;
}
int GoldenFingerMode_player_try(const Ant& ant, Map*& player_map, S_Map& s_map, S_Ant& s_ant, int x, int y, int& if_line)
{
	std::cout << "\033[0;0H";//�ƶ���굽(0,0)
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
	cout << "�������" << endl;
	cout << "��������ڰ׸��Ӹı����ϵ��˶��켣��Ҫ����ײ���ϰ����" << endl;
	cout << "�������������" << ant.num_rocket << endl;
	cout << "��������������" << ant.num_big_rocket << endl;
	cout << "��צ����������" << ant.num_falcula << endl;
	cout << "����ָʾ������������" << ant.num_LaserPointer << endl;
	cout << "����ָʾ��ʣ�����:" << if_line << endl;
	s_map.S_showMap(player_map, 0);
	s_ant.S_showAnt(player_map);
	return -1;
}

int GoldenFinger_move(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window)
{
	
	if (ant.move(head_map) == -1)
	{
		std::cout << "ײ���ϰ����ˣ�" << std::endl;
		return -1;
	}

	head_map = head_map->nextMap;
	s_map.S_showMap(head_map, 0);
	s_ant.S_showAnt(head_map);
	window.clear();
	window.draw(s_map);
	window.draw(s_ant);
	//�����
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
			switch (type)
			{
			case 0:
				ant.num_rocket++;
				break;
			case 1:
				ant.num_big_rocket++;
				break;
			case 2:
				ant.num_LaserPointer++;
				break;
			case 3:
				ant.num_falcula++;
				break;
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
void GoldenFinger_moveProcess(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window, int step, int& process, int& if_line, int& best_source, int& best_roundsNum, int& best_destroyNum)
{
	for (int j = 1; j <= step; j++)
	{
		//�����һ��
		s_map.S_showMap(head_map, 0);
		s_ant.S_showAnt(head_map);
		window.draw(s_map);
		window.draw(s_ant);
		for (int i = 0; i < prop_list.size(); i++)
		{
			window.draw(prop_list[i]);
		}
		window.display();
		if (j == 1)system("cls");
		//auto start = std::chrono::steady_clock::now(); // ��ȡ��ʼʱ��
		//auto end = start + std::chrono::milliseconds(500); // ����Ŀ��ʱ�䣨0.5���
		/*while (std::chrono::steady_clock::now() < end)*/

		//�ȴ�����
		system("cls");
		cout << "�������������" << ant.num_rocket << endl;
		cout << "��������������" << ant.num_big_rocket << endl;
		cout << "��צ����������" << ant.num_falcula << endl;
		cout << "����ָʾ������������" << ant.num_LaserPointer << endl;
		
		for (int i = 0; i < 50; i++)
		{
			sf::Vector2f Position = s_ant.getPosition();
			while (const std::optional event = window.pollEvent())
			{
				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
				{
					if (keyPressed->code == sf::Keyboard::Key::J)
					{
						cout << "С������䣡" << endl;
						if (ant.num_rocket > 0)
						{
							rocket(ant, head_map, s_map, s_ant, prop_list, window, Position);
							ant.num_rocket--;
						}
						else
						{
							cout << "С��������ˣ�����" << endl;
							cout << "��ȥ��ͼ��ʰȡ�� >_<" << endl;
						}
					}
					else if (keyPressed->code == sf::Keyboard::Key::K)
					{
						cout << "�������䣡" << endl;
						if (ant.num_big_rocket > 0)
						{
							big_rocket(ant, head_map, s_map, s_ant, prop_list, window, Position);
							ant.num_big_rocket--;
						}
						else
						{
							cout << "���������ˣ�����" << endl;
							cout << "��ȥ��ͼ��ʰȡ�� >_<" << endl;
						}

					}
					else if (keyPressed->code == sf::Keyboard::Key::U)
					{
						//cout << "������U" << endl;
						if (ant.num_LaserPointer > 0)
						{
							if_line += 3;
							cout << "����ָʾ�����ɹ�������" << endl;
							cout << "��ǰ����ָʾ��������" << if_line << endl;
							ant.num_LaserPointer--;
						}
						else
						{
							cout << "����ָʾ�������ˣ�����" << endl;
							cout << "��ȥ��ͼ��ʰȡ�� >_<" << endl;
						}
					}
					else if (keyPressed->code == sf::Keyboard::Key::L)
					{
						if (ant.num_falcula > 0)
						{
							falcula(ant, head_map, s_map, s_ant, prop_list, window, Position);
							ant.num_falcula--;
						}
						else
						{
							cout << "��צ�����ˣ�����" << endl;
							cout << "��ȥ��ͼ��ʰȡ�� >_<" << endl;
						}
					}
				}
			}
			//std::cout << "Looping..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1)); // ��ͣ1���룬����CPUռ�ù���
			switch (ant.direction)
			{
			case Direction::UP:
				Position.y -= 2;
				break;
			case Direction::DOWN:
				Position.y += 2;
				break;
			case Direction::LEFT:
				Position.x -= 2;
				break;
			case Direction::RIGHT:
				Position.x += 2;
				break;
			}
			s_ant.setPosition(Position);
			window.draw(s_map);
			window.draw(s_ant);
			for (int i = 0; i < prop_list.size(); i++)
			{
				window.draw(prop_list[i]);
			}
			window.display();
		}
		int temp = GoldenFinger_move(ant, head_map, s_map, s_ant, prop_list, window);
		if (j == step)
		{
			system("cls");
			cout << "�������" << endl;
			cout << "��������ڰ׸��Ӹı����ϵ��˶��켣��Ҫ����ײ���ϰ����" << endl;
			cout << "�������������" << ant.num_rocket << endl;
			cout << "��������������" << ant.num_big_rocket << endl;
			cout << "��צ����������" << ant.num_falcula << endl;
			cout << "����ָʾ������������" << ant.num_LaserPointer << endl;
			cout << "����ָʾ��ʣ�����:" << if_line << endl;
			cout << "ʣ�����������5��" << endl;
			cout << "��Enter������" << endl;
		}
		if (temp == -1)//�Դ�show��draw
		{
			process = 4;//4 ������Ϸ
			ant.Rounds++;
			gameOver_GoldenFinger(window, s_map, s_ant, prop_list, ant, best_source, best_roundsNum, best_destroyNum);//��ʾ��Ϸ��������
			return;
		}
		else
		{
			if (temp == 0)
			{
				cout << "��ʰȡ�˻����������" << endl;
			}
			else if (temp == 1)
			{
				cout << "��ʰȡ�˴�����������" << endl;
			}
			else if (temp == 2)
			{
				cout << "��ʰȡ�˼���ָʾ��������" << endl;
			}
			else if (temp == 3)
			{
				cout << "��ʰȡ�˹�צ������" << endl;
			}
			if (j == step)
			{
				head_map->creatBarLava();
				head_map->creatBarStone();
				//��������
				creatProp(prop_list, *head_map, rand() % 4);
				s_map.S_showMap(head_map, 0);
				process = -2;
			}
		}
	}
}

void rocket(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window, sf::Vector2f Position)//С���
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
		switch (ant.direction)//�����ٶ�
		{
		case Direction::UP:
			rocketPosition.y -= 0.09;
			break;
		case Direction::DOWN:
			rocketPosition.y += 0.09;
			break;
		case Direction::LEFT:
			rocketPosition.x -= 0.09;
			break;
		case Direction::RIGHT:
			rocketPosition.x += 0.09;
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
		//���
		//������ͼ
		if (rocketPosition.x >= 100 * head_map->Width || rocketPosition.y >= 100 * head_map->Height || rocketPosition.x <= 0 || rocketPosition.y <= 0)
		{
			break;
		}
		//�����ϰ���
		if (head_map->m_map[(int)rocketPosition.x / 100 + 1][(int)rocketPosition.y / 100 + 1] == 3 || head_map->m_map[(int)rocketPosition.x / 100 + 1][(int)rocketPosition.y / 100 + 1] == 4)
		{
			head_map->m_map[(int)rocketPosition.x / 100 + 1][(int)rocketPosition.y / 100 + 1] -= 3;
			ant.DestroyedStones++;
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

void big_rocket(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window, sf::Vector2f Position)//С���
{
	sf::Texture big_rocketTexture;
	if (!big_rocketTexture.loadFromFile("prop/big_rocket.png"))//����ͼƬ
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
			rocketPosition.y -= 0.08;//�����ٶȣ���������
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
		//���
		//������ͼ
		if (rocketPosition.x >= 100 * head_map->Width || rocketPosition.y >= 100 * head_map->Height || rocketPosition.x <= 0 || rocketPosition.y <= 0)
		{
			break;
		}
		//�����ϰ���
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
						ant.DestroyedStones++;
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

void Confirm_line(sf::VertexArray& line, Map head_map)
{
	line[0].position = sf::Vector2f(head_map.M_ant_x * 100 - 50, head_map.M_ant_y * 100 - 50);
	for (int i = 1; i <= 5; i++)
	{

		if (head_map.m_degree == sf::degrees(0.f))
		{
			head_map.M_ant_y -= 1;
		}
		else if (head_map.m_degree == sf::degrees(90.f))
		{
			head_map.M_ant_x += 1;
		}
		else if (head_map.m_degree == sf::degrees(180.f))
		{
			head_map.M_ant_y += 1;
		}
		else if (head_map.m_degree == sf::degrees(270.f))
		{
			head_map.M_ant_x -= 1;
		}
		if (head_map.M_ant_x < 1 || head_map.M_ant_x > head_map.Width || head_map.M_ant_y < 1 || head_map.M_ant_y > head_map.Height)
		{
			for (int j = i; j <= 5; j++)
			{
				line[j].position = line[i].position;
			}
			break;
		}
		line[i].color = sf::Color::Red;
		line[i].position = sf::Vector2f(head_map.M_ant_x * 100 - 50, head_map.M_ant_y * 100 - 50);
		if (head_map.m_map[head_map.M_ant_x][head_map.M_ant_y] == 0) {
			head_map.m_map[head_map.M_ant_x][head_map.M_ant_y] = 1;
			if (head_map.m_degree == sf::degrees(270.f))
			{
				head_map.m_degree = sf::degrees(0.f);
			}
			else
			{
				head_map.m_degree += sf::degrees(90.f);
			}
		}
		else if (head_map.m_map[head_map.M_ant_x][head_map.M_ant_y] == 1) {
			head_map.m_map[head_map.M_ant_x][head_map.M_ant_y] = 0;
			if (head_map.m_degree == sf::degrees(0.f))
			{
				head_map.m_degree = sf::degrees(270.f);
			}
			else if (head_map.m_degree == sf::degrees(270.f))
			{

				head_map.m_degree = sf::degrees(180.f);
			}
			else
			{
				head_map.m_degree -= sf::degrees(90.f);
			}
		}
		else
		{
			for (int j = i; j <= 5; j++)
			{
				line[j].position = line[i].position;
			}
			break;
		}
	}
}

void falcula(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, vector<Prop>& prop_list, sf::RenderWindow& window, sf::Vector2f Position)
{
	cout << "��צʰȡ��..." << endl;
	sf::Texture falculaTexture;
	if (!falculaTexture.loadFromFile("prop/falcula.png"))
	{
		std::cerr << "Failed to load falcula texture" << std::endl;
		return;
	}

	sf::Vector2f falculaPosition = Position;
	sf::Sprite falculaSprite(falculaTexture);
	falculaSprite.setOrigin({ 25.f,45.f });
	falculaSprite.setRotation(head_map->m_degree);
	falculaSprite.setPosition(falculaPosition);

	sf::Vector2f lineSize(1.f, 5.f);//���� 0.f ��� 5.f
	sf::RectangleShape line(lineSize);
	line.setFillColor(sf::Color::Black);
	line.setOrigin({ 1.f,3.f });
	line.rotate(head_map->m_degree - sf::degrees(90));
	line.setPosition(falculaPosition);
	while (true)//���
	{
		switch (ant.direction)//�����ٶ�
		{
		case Direction::UP:
			falculaPosition.y -= 0.07;
			break;
		case Direction::DOWN:
			falculaPosition.y += 0.07;
			break;
		case Direction::LEFT:
			falculaPosition.x -= 0.07;
			break;
		case Direction::RIGHT:
			falculaPosition.x += 0.07;
			break;
		}
		lineSize.x += 0.07;
		falculaSprite.setPosition(falculaPosition);
		line.setSize(lineSize);
		window.draw(s_map);
		window.draw(s_ant);
		for (int i = 0; i < prop_list.size(); i++)
		{
			window.draw(prop_list[i]);
		}
		window.draw(line);
		window.draw(falculaSprite);
		window.display();
		//���
		//������ͼ
		if (falculaPosition.x >= 100 * head_map->Width || falculaPosition.y >= 100 * head_map->Height || falculaPosition.x <= 0 || falculaPosition.y <= 0)
		{
			break;
		}
		//����Ƿ�������
		for (int i = 0; i < prop_list.size(); i++)
		{
			if ((int)falculaPosition.x == (int)prop_list[i].getX() * 100 - 50 && (int)falculaPosition.y == (int)prop_list[i].getY() * 100 - 50)
			{
				//ץ�ŵ��߻�
				while (true)
				{
					switch (ant.direction)//�����ٶ�
					{
					case Direction::UP:
						falculaPosition.y += 0.07;
						break;
					case Direction::DOWN:
						falculaPosition.y -= 0.07;
						break;
					case Direction::LEFT:
						falculaPosition.x += 0.07;
						break;
					case Direction::RIGHT:
						falculaPosition.x -= 0.07;
						break;
					}
					lineSize.x -= 0.07;//�߳���

					sf::Vector2f propPosition = falculaPosition;
					switch (ant.direction)//ʹ����ץ��ʱ�ڹ�צ����
					{
					case Direction::UP:
						propPosition.y -= 25;
						break;
					case Direction::DOWN:
						propPosition.y += 25;
						break;
					case Direction::LEFT:
						propPosition.x -= 25;
						break;
					case Direction::RIGHT:
						propPosition.x += 25;
						break;
					}
					prop_list[i].setPosition(propPosition);//����λ��
					falculaSprite.setPosition(falculaPosition);//��צλ��
					line.setSize(lineSize);//�߳�����
					window.draw(s_map);
					window.draw(s_ant);
					for (int j = 0; j < prop_list.size(); j++)
					{
						window.draw(prop_list[j]);
					}
					window.draw(line);
					window.draw(falculaSprite);
					window.display();
					bool if_catch = false;
					switch (ant.direction)
					{
					case Direction::UP:
						if (falculaPosition.y >= line.getPosition().y + 30)
						{
							if_catch = true;
						}
						break;
					case Direction::DOWN:
						if (falculaPosition.y <= line.getPosition().y)
						{
							if_catch = true;
						}
						break;
					case Direction::LEFT:
						if (falculaPosition.x >= line.getPosition().x)
						{
							if_catch = true;
						}
						break;
					case Direction::RIGHT:
						if (falculaPosition.x <= line.getPosition().x)
						{
							if_catch = true;
						}
						break;
					}
					if (if_catch == true)
					{
						int type = prop_list[i].getType();
						prop_list.erase(prop_list.begin() + i);
						for (int j = 0; j < prop_list.size(); j++)
						{
							window.draw(prop_list[j]);
						}
						switch (type)
						{
						case 0:
							ant.num_rocket++;
							cout << "�㹴���˻�������ߣ�����" << endl;
							break;
						case 1:
							ant.num_big_rocket++;
							cout << "�㹴���˴��������ߣ�����" << endl;
							break;
						case 2:
							ant.num_LaserPointer++;
							cout << "�㹴�м���ָʾ�����ߣ�����" << endl;
							break;
						case 3:
							ant.num_falcula++;
							cout << "�㹴���˹�צ���ߣ�����" << endl;
							break;
						}
						window.display();
						return;
					}
				}
			}
		}
	}
	//��צ��
	while (true)
	{
		switch (ant.direction)//�����ٶ�
		{
		case Direction::UP:
			falculaPosition.y += 0.07;
			break;
		case Direction::DOWN:
			falculaPosition.y -= 0.07;
			break;
		case Direction::LEFT:
			falculaPosition.x += 0.07;
			break;
		case Direction::RIGHT:
			falculaPosition.x -= 0.07;
			break;
		}
		lineSize.x -= 0.07;
		falculaSprite.setPosition(falculaPosition);
		line.setSize(lineSize);
		window.draw(s_map);
		window.draw(s_ant);
		for (int i = 0; i < prop_list.size(); i++)
		{
			window.draw(prop_list[i]);
		}
		window.draw(line);
		window.draw(falculaSprite);
		window.display();
		switch (ant.direction)
		{
		case Direction::UP:
			if (falculaPosition.y >= line.getPosition().y)
			{
				return;
			}
			break;
		case Direction::DOWN:
			if (falculaPosition.y <= line.getPosition().y)
			{
				return;
			}
			break;
		case Direction::LEFT:
			if (falculaPosition.x >= line.getPosition().x)
			{
				return;
			}
			break;
		case Direction::RIGHT:
			if (falculaPosition.x <= line.getPosition().x)
			{
				return;
			}
			break;
		}
	}
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

int gameOver_GoldenFinger(sf::RenderWindow& window, const S_Map& s_map, const S_Ant& s_ant,const std::vector<Prop>& prop_list,const Ant &ant, int& best_source, int& best_roundsNum, int& best_destroyNum)
{
	
	HCURSOR customCursor2 = LoadCursorFromFile(L"material/Vision Cursor White/link.cur");//���ļ��м��ع��
	sf::Texture gameOver_texture;
	if (!gameOver_texture.loadFromFile("context/gameOver_GoldenFinger_cover.png"))
		return -1;
	sf::Sprite gameOver_cover(gameOver_texture);
	gameOver_cover.setOrigin(sf::Vector2f(gameOver_texture.getSize().x / 2, gameOver_texture.getSize().y / 2));
	gameOver_cover.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	sf::Vector2u original_Size = gameOver_texture.getSize();
	sf::Vector2f scale_Size = { 600.f / original_Size.x, 600.f / original_Size.y };
	gameOver_cover.setScale(scale_Size);//��������
	sf::Font font;
	if (!font.openFromFile("TTF/BRLNSDB.ttf"))//BSF�����
	{
		std::cout << "Failed to load font" << std::endl;
		return -1;
	}
	sf::Color text_color(227, 182, 119);

	sf::Text roundsNum(font, to_string(ant.Rounds), 40);
	roundsNum.setFillColor(text_color);
	sf::FloatRect roundsNum_size(roundsNum.getLocalBounds());
	roundsNum.setOrigin(sf::Vector2f(roundsNum_size.getCenter().x*2,0));
	roundsNum.setPosition(sf::Vector2f(870, 525));
	if (best_roundsNum < ant.Rounds)//���»غϼ�¼
		best_roundsNum = ant.Rounds;

	sf::Text destroyedStones(font, to_string(ant.DestroyedStones), 40);
	destroyedStones.setFillColor(text_color);
	sf::FloatRect destroyedStones_size(destroyedStones.getLocalBounds());
	destroyedStones.setOrigin(sf::Vector2f(destroyedStones_size.getCenter().x*2, 0));
	destroyedStones.setPosition(sf::Vector2f(870, 605));
	if (best_destroyNum < ant.DestroyedStones)//����ʯͷ��¼
		best_destroyNum = ant.DestroyedStones;

	sf::Text source(font, to_string(ant.DestroyedStones * 20 + ant.Rounds * 10), 40);
	source.setFillColor(text_color);
	sf::FloatRect source_size(source.getLocalBounds());
	source.setOrigin(sf::Vector2f(source_size.getCenter().x*2, 0));
	source.setPosition(sf::Vector2f(870, 680));
	if (best_source < ant.DestroyedStones * 20 + ant.Rounds * 10)//������߷�
	{
		best_source = ant.DestroyedStones * 20 + ant.Rounds * 10;
		source.setFillColor(sf::Color::Red);//ˢ�¼�¼
		sf::Image image;
		if (!image.loadFromFile("context/gameOver_GoldenFinger_cover_newrecord.png"))
		{
			return -1;
		}
		gameOver_texture.update(image);
	}
	sf::Text T_best_source(font, to_string(best_source), 40);
	T_best_source.setFillColor(sf::Color::Red);
	sf::FloatRect best_source_size(T_best_source.getLocalBounds());
	T_best_source.setOrigin(sf::Vector2f(best_source_size.getCenter().x*2, 0));
	T_best_source.setPosition(sf::Vector2f(870, 728));
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())//�������ж�����Ƿ��ƶ���ĳ��
			{
				//cout << "������꣺" << mouseMoved->position.x << " " << mouseMoved->position.y << std::endl;
				if (mouseMoved->position.x >= 462 && mouseMoved->position.x <= 840 && mouseMoved->position.y >= 821 && mouseMoved->position.y <= 912)
				{
					SetCursor(customCursor2);//��ʱ�������ָ��ͼ��
				}
			}
			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())//��갴��
			{
				if (mouseButtonPressed->button == sf::Mouse::Button::Left)
				{
					if (mouseButtonPressed->position.x >= 462 && mouseButtonPressed->position.x <= 840 && mouseButtonPressed->position.y >= 821 && mouseButtonPressed->position.y <= 912)
						return 0;
				}
			}
		}
		window.clear();
		window.draw(s_map);
		window.draw(s_ant);
		for (int i = 0; i < prop_list.size(); i++)
		{
			window.draw(prop_list[i]);
		}
		window.draw(gameOver_cover);
		window.draw(roundsNum);
        window.draw(destroyedStones);
        window.draw(source);
        window.draw(T_best_source);
		window.display();
	}
}



