#include "game.h"
#include <iostream>
#include <windows.h>
using namespace std;

//����˵�� ײǽ�� ������ɵ�ͼ�� �طŹ���(��ʱ����)��  ��ʼλ�� ���� ��ͼ���湦�� ������� �����ţ��ϰ��
//��ս����ͨ���ı�ڰף�����С�Ĳ��������ϵ�Ŀ������

int main()
{
	Ant ant;
	//����ָ��������ȡÿһ����ͼ�ĵ�ַ
	Map* head_map = new Map;
	Map* tail_map = new Map;
	sf::Font font;
	if (!font.openFromFile("msyh.ttc"))
	{
		std::cout << "Failed to load font" << std::endl;
		return -1;
	}
	sf::Text Rules(font);
	introduction(Rules);
	sf::RenderWindow window(sf::VideoMode({ 600, 900 }), L"��������", sf::Style::Default);
	sf::Texture Start_texture;
	if (!Start_texture.loadFromFile("Start_game_cover.png", false, sf::IntRect({ 0, 0 }, { 1024, 1536 })))//sf::IntRect ����һ���򵥵�ʵ�����ͣ���ʾһ�����Ρ����Ĺ��캯�����ܾ��ε����Ͻ�����ʹ�С��
		return -1;
	sf::Sprite Start_game_cover(Start_texture);
	sf::Vector2u original_Start_Size = Start_texture.getSize();
	sf::Vector2f scale_Start_Size = { 600.f / original_Start_Size.x, 900.f / original_Start_Size.y };
	Start_game_cover.setScale(scale_Start_Size);

	HCURSOR customCursor1 = LoadCursorFromFile(L"pointer.cur");//���ļ��м��ع��
	HCURSOR customCursor2 = LoadCursorFromFile(L"link.cur");//���ļ��м��ع��
	if (!customCursor1 || !customCursor2) {
		DWORD dwError = GetLastError();
		MessageBox(NULL, L"Failed to load custom cursor", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
	HWND hwnd = FindWindow(NULL, L"��������");//��ȡ���ھ��
	if (!hwnd) {
		MessageBox(NULL, L"Failed to find window", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
	//�������ָ��ͼ��
	SetClassLongPtr(hwnd, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(customCursor1));//�����������ָ��ͼ��
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
				if (keyPressed->code == sf::Keyboard::Key::Escape && temp == 2)
				{
					temp++;
					tail_map = head_map;
					int goal_step = 1000;
					Sports_process(goal_step, head_map, ant); //ģ���˶�
					Map player_map(*head_map);
					//player_try(player_map,tail_map);//��ҳ���
					Show_process(tail_map, ant, s_map, s_ant, window);//չʾ�˶�
				}
			}
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())//�������ж�����Ƿ��ƶ���ĳ��
			{
				if (temp == 0)
				{
					if (mouseMoved->position.x >= 87 && mouseMoved->position.x <= 514 && mouseMoved->position.y >= 658 && mouseMoved->position.y <= 784)
					{
						SetCursor(customCursor2);//��ʱ�������ָ��ͼ��
					}
				}
			}
			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())//��갴��
			{
					if (mouseButtonPressed->button == sf::Mouse::Button::Left)
					{
						//std::cout << "the Left button was pressed" << std::endl;
						if (mouseButtonPressed->position.x >= 87 && mouseButtonPressed->position.x <= 514 && mouseButtonPressed->position.y >= 658 && mouseButtonPressed->position.y <= 784)
							temp++;
					}
				}

			}

			if (temp == 1)
			{
				if (!chooseMap(head_map, ant, s_map, s_ant, window))
				{
					return 0;
				}
				temp++;
			}
			window.clear();
			// draw the map
			if (temp == 0)
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
			}
			window.display();
		}

		//test
		system("pause");
		//tail_map->showMap();//�����������ʵ�һ����ͼ
		return 0;
	}