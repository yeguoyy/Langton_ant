#include "game.h"
#include <iostream>
//#include <windows.h>
using namespace std;

//����˵���� ײǽ�� ������ɵ�ͼ �طŹ���(��ʱ����)��  ��ʼλ�� ������ ��ͼ���湦�� ������� �����ţ��ϰ��
//��ս����ͨ���ı�ڰף�����С�Ĳ��������ϵ�Ŀ������

int main()
{
	introduction();
	Ant ant;
	//����ָ��������ȡÿһ����ͼ�ĵ�ַ
	Map *head_map=new Map;
	Map *tail_map=new Map;
	sf::RenderWindow window(sf::VideoMode({ 500, 500 }), L"��������",sf::Style::Default);
	//// ��ȡ���ھ��
	//const wchar_t* windowTitle = L"��������";
	//HWND hwnd = FindWindow(NULL, windowTitle);
	//if (hwnd != NULL)
	//{
	//	std::cout << "���ھ�����ҵ������ֵ: " << hwnd << std::endl;

	//	// ����������ǰ̨
	//	SetForegroundWindow(hwnd);
	//}
	//else
	//{
	//	std::cerr << "�޷��ҵ����ھ��" << std::endl;
	//}



	S_Map s_map;
	S_Ant s_ant;
	//�����ͷβ���
	if (!chooseMap(head_map,ant,s_map,s_ant,window))
	{
		return 0;
	}
	int temp = 0;
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
				
				if (keyPressed->code == sf::Keyboard::Key::Escape&&temp==0)
				{
					temp = 1;
					tail_map = head_map;
					int goal_step = 1000;
					Sports_process(goal_step, head_map, ant); //ģ���˶�
					Map player_map(*head_map);
					//player_try(player_map,tail_map);//��ҳ���
					Show_process(tail_map, ant,s_map,s_ant,window);//չʾ�˶�
				}
			}

		}

		// draw the map
		window.clear();
		window.draw(s_map);
		window.draw(s_ant);
		window.display();
	}
	
	//test
    system("pause");
	//tail_map->showMap();//�����������ʵ�һ����ͼ
	return 0;
}