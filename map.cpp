#include "game.h"// ͬʱ��������ͷ�ļ�
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool Read_map(string, Map*&, Ant&);
static int x, y;
bool chooseMap(Map*& head_map, Ant& ant)
{
	cout << "ѡ��ؿ�ģʽ�밴1��������ɹؿ�ģʽ�밴2" << endl;
	int choice;
	cin >> choice;
	string filename;
	switch (choice) {
	case 1:
		cout << "������ؿ���ţ�1��2��" << endl;
		int num;
		cin >> num;
		system("cls");
		filename = to_string(num) + ".txt";// ������ת��Ϊ�ַ���
		//cout << filename << endl;
		if (!Read_map(filename, head_map, ant))// ��ȡ�ؿ���ͼ
		{
			return false;
		}
		break;
	case 2:
		cout << "��������Ҫ���ɵ���Ŀ�ĳ��ȺͿ��" << endl;
		cin >> x >> y;
		// creatMap(head_map);
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
		fil >> ant.Ant_x >> ant.Ant_y;
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
