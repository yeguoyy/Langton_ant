#include "game.h"// ͬʱ��������ͷ�ļ�
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
using namespace std;

bool Read_map(string, Map*&, Ant&);
static int x, y;

bool chooseMap(Map*& head_map, Ant& ant)
{
	cout << "ѡ��ؿ�ģʽ�밴1��������ɹؿ�ģʽ�밴2" << endl;
	int choice;
	while (true)
	{
		cin >> choice;
		if (cin.fail() || (choice != 1 && choice != 2))
		{
			cout << "�������,����������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			break;
		}
	}
	string filename;
	switch (choice) {
	case 1:
		cout << "������ؿ���ţ�1��2��" << endl;
		int num;
		while (true)
		{
			cin >> num;
			if (cin.fail() || (num != 1 && num != 2))
			{
				cout << "�������,����������" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else
			{
				break;
			}
		}
		filename = to_string(num) + ".txt";// ������ת��Ϊ�ַ���
		//cout << filename << endl;
		if (!Read_map(filename, head_map, ant))// ��ȡ�ؿ���ͼ
		{
			return false;
		}
		break;
	case 2:
		creatMap(head_map, ant);
		break;
	}
	system("cls");
	return true;
}
void creatMap(Map*& head_map, Ant& ant)
{
	srand(time(0));
	cout << "��������Ҫ���ɵ���Ŀ�ĳ��ȺͿ��" << endl;

	while (true)
	{
		cin >> x >> y;
		if (cin.fail() || (x <= 0 || y <= 0))
		{
			cout << "�������,����������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (x > 30 || y > 30)
		{
			cout << "�������,����������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			break;
		}
	}
	head_map->Width = x;
	head_map->Height = y;
	ant.Ant_x = (int)(head_map->Width / 2) + 1;
	ant.Ant_y = (int)(head_map->Height / 2) + 1;
	Ant::initial_x = ant.Ant_x;
	Ant::initial_y = ant.Ant_y;
	// ��̬�����ά�ڴ�
	head_map->m_map = new int* [head_map->Width + 1];// ��̬�����ڴ�
	for (int i = 1; i <= head_map->Width; i++)
	{
		head_map->m_map[i] = new int[head_map->Height + 1];// ��̬�����ڴ�
	}
	//������ǰ�ɫ������ ÿ10���һ���ɫ
	int edge = ((head_map->Width < head_map->Height) ? head_map->Width : head_map->Height) / 10 + 1;
	for (int i = 1; i <= head_map->Width; i++)
	{
		for (int j = 1; j <= head_map->Height; j++)
		{
			if (i <= edge || i >= head_map->Width - (edge - 1) || j <= edge || j >= head_map->Height - (edge - 1))
			{
				head_map->m_map[i][j] = 0;
			}
			else//test �ڴ˼�����������߼� �ֿ飿
			{
				/*if (rand() % 2 == 0)
				{
					head_map->m_map[i][j] = 8;
				}
				else
				{
					head_map->m_map[i][j] = 0;
				}*/
				/*�����߼���Խ�����м�Խ�����Ǻ�ɫ*/
				int RandNum = rand() % (ant.Ant_x - edge) * (ant.Ant_y - edge);
				if (RandNum > (abs(i - ant.Ant_x) + edge) * (abs(j - ant.Ant_y) + edge))
				{
					head_map->m_map[i][j] = 8;
				}
				else
				{
					head_map->m_map[i][j] = 0;
				}
			}
		}
	}
	head_map->m_map[ant.Ant_x][ant.Ant_y] = rand() % 4 + 1;
	switch (head_map->m_map[ant.Ant_x][ant.Ant_y])
	{
	case 1:
		ant.direction = UP;
		break;
	case 2:
		ant.direction = DOWN;
		break;
	case 3:
		ant.direction = LEFT;
		break;
	case 4:
		ant.direction = RIGHT;
		break;
	}
}

bool Read_map(string filename, Map*& head_map, Ant& ant)
{
	fstream fil(filename);

	if (!fil.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return false;
	}
	else {
		fil >> x >> y;// ��ȡ��ͼ���
		head_map->Width = x;
		head_map->Height = y;
		// ��̬�����ά�ڴ�
		head_map->m_map = new int* [head_map->Width + 1];// ��̬�����ڴ�
		for (int i = 1; i <= head_map->Width; i++) {
			head_map->m_map[i] = new int[head_map->Height + 1];// ��̬�����ڴ�
		}
		// ��ȡ��ͼ (1,1)Ϊ���Ͻ� ��ȡ˳��ͷ����ڴ�˳��һ��
		for (int j = 1; j <= head_map->Height; j++) {
			for (int i = 1; i <= head_map->Width; i++) {
				fil >> head_map->m_map[i][j];
			}
		}
		//������ʼλ��
		fil >> ant.Ant_x >> ant.Ant_y;
		Ant::initial_x = ant.Ant_x;
		Ant::initial_y = ant.Ant_y;
		//���� 1��1 v��2 <��3 >��4
		fil >> head_map->m_map[ant.Ant_x][ant.Ant_y];
		switch (head_map->m_map[ant.Ant_x][ant.Ant_y])
		{
		case 1:
			ant.direction = UP;
			break;
		case 2:
			ant.direction = DOWN;
			break;
		case 3:
			ant.direction = LEFT;
			break;
		case 4:
			ant.direction = RIGHT;
			break;
		}
		//cout << "w=" << w << "h=" << h << endl;
		fil.close();
		return true;
	}
}

Map::Map()
{
	m_map = nullptr;
	Width = 0;
	Height = 0;
	Ant_color = 0;
	nextMap = nullptr;
}

Map::~Map()
{
	if (m_map != nullptr) {
		for (int i = 1; i <= Height; i++) {
			delete[] m_map[i];
		}
		delete[] m_map;
	}
}
//1��1 v��2 <��3 >��4
void Map::showMap()
{
	for (int i = 1; i <= Height; i++) {

		for (int j = 1; j <= Width; j++) {
			switch (m_map[j][i])
			{
			case 0:
				cout << 'O' << " ";
				break;
			case 8:
				cout << '#' << " ";
				break;
			case 1:
				cout << '1' << " ";
				break;
			case 2:
				cout << 'v' << " ";
				break;
			case 3:
				cout << '<' << " ";
				break;
			case 4:
				cout << '>' << " ";
				break;
			default:
				cout << m_map[i][j] << " ";
				break;
			}
		}
		cout << endl;
	}
}
Map::Map(Map& map)
{
	this->Width = map.Width;
	this->Height = map.Height;
	this->Ant_color = map.Ant_color;
	this->m_map = new int* [Width + 1];
	for (int i = 1; i <= Width; i++)
	{
		this->m_map[i] = new int[Height + 1];
		for (int j = 1; j <= Height; j++)
		{
			this->m_map[i][j] = map.m_map[i][j];
		}
	}
	this->nextMap = map.nextMap;
}
