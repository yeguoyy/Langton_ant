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

void player_try(Map& player_map)
{
	while(true)
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
		int x, y;
        cout << "����������ı���ɫ�����꣺" << endl;
        cin >> x >> y;
        if (x > player_map.Width || y > player_map.Height|| x <= 0 || y <= 0)
        {
            cout << "������ͼ��Χ" << endl;
			cin.clear();
        }
		else if (cin.fail())
		{
			cout << "�������" << endl;
            cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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