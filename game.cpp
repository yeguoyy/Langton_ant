#include "game.h"
#include <iostream>
using namespace std;


void introduction()
{
	cout << "��ӭ��������������Ϸ" << endl;
	cout << "���������ɺڣ�#���ף�O�����Ӻ�һֻ���Ϲ��ɣ����Ͽ���ƽ�����������ƶ���" << endl
		<< "���ڰ׸�����ת90�ȣ����ø��Ϊ�ڸ񣬲���ǰ�ƶ�һ����" << endl
		<< "���ںڸ�����ת90�ȣ����ø��Ϊ�׸񣬲���ǰ�ƶ�һ����" << endl
		<< "��ײǽ����ԭ�ز�������ת180�ȵ�ͷ�����ı������ɫ��" << endl;
	cout << "�����Ҫ�������ϵ���������ͼ���Ƴ�ʼͼ" << endl;
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
			else if (player_map.m_map[i][j] != 0 && player_map.m_map[i][j] != 8)
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
void player_try(Map& player_map, Map*& tail_map)
{
	while (true)
	{
		system("cls");
		player_map.showMap();
		cout << "���Ͻ��µ���ɫΪ��";
		if (player_map.Ant_color == 0)
		{
			std::cout << "��ɫ" << std::endl;
		}
		else if (player_map.Ant_color == 8)
		{
			std::cout << "��ɫ" << std::endl;
		}
		if (if_player_win(player_map, tail_map) == true)
		{
			cout << "��ϲ�㣬��Ӯ�ˣ�" << endl;
			system("pause");
			return;
		}
		int x, y;
		cout << "����������ı���ɫ�����꣺" << endl;
		cin >> x >> y;
		if (x > player_map.Width || y > player_map.Height || x < 0 || y < 0)
		{
			cout << "������ͼ��Χ������������" << endl;
			cin.clear();
			system("pause");
		}
		else if (x == 0 && y == 0)
		{
			cout << "����" << endl;
			system("pause");
			return;
		}
		else if (cin.fail())
		{
			cout << "�������,����������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
		}
		else if (x == Ant::Ant_x && y == Ant::Ant_y)
		{
			if (player_map.Ant_color == 0)
			{
				player_map.Ant_color = 8;
			}
			else if (player_map.Ant_color == 8)
			{

				player_map.Ant_color = 0;
			}
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