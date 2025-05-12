#include "game.h"
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

#define goal_step 1000
using namespace std;

//����˵�� ײǽ�� ������ɵ�ͼ�� �طŹ���(��ʱ����)��  ��ʼλ�� ������ ��ͼ���湦�� ������� �����ţ��ϰ��ʤ������ ���¿�ʼ��Ϸ�����ã�
//����ָ��ս����ͨ���ı�ڰף�����С�Ĳ��������ϵ�Ŀ������������˵�����ߡ��÷֣�
//���ߣ���̹�˴�ս�����⣬�ɵ�����λ��ץȡ����������
//�¼�����������ӣ��������ɣ���ͼ���˵�����Χϴ�ƣ���

int main()
{
	Ant ant;
	//����ָ��������ȡÿһ����ͼ�ĵ�ַ
	Map* head_map = new Map;
	Map* tail_map = new Map;
	Map player_map;

	sf::Font font;
	if (!font.openFromFile("TTC/msyh.ttc"))
	{
		std::cout << "Failed to load font" << std::endl;
		return -1;
	}
	sf::Text Rules(font);
	introduction(Rules);
	sf::RenderWindow window(sf::VideoMode({ 600, 900 }), L"��������", sf::Style::Default);
	sf::Texture Start_texture;
	if (!Start_texture.loadFromFile("context/Start_game_cover.png", false, sf::IntRect({ 0, 0 }, { 1024, 1536 })))//sf::IntRect ����һ���򵥵�ʵ�����ͣ���ʾһ�����Ρ����Ĺ��캯�����ܾ��ε����Ͻ�����ʹ�С��
		return -1;
	sf::Sprite Start_game_cover(Start_texture);
	sf::Vector2u original_Start_Size = Start_texture.getSize();
	sf::Vector2f scale_Start_Size = { 600.f / original_Start_Size.x, 900.f / original_Start_Size.y };
	Start_game_cover.setScale(scale_Start_Size);

	HCURSOR customCursor1 = LoadCursorFromFile(L"material/Vision Cursor White/pointer.cur");//���ļ��м��ع��
	HCURSOR customCursor2 = LoadCursorFromFile(L"material/Vision Cursor White/link.cur");//���ļ��м��ع��
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
	vector<Prop> prop_list;
	//�����ͷβ���
	int process = 0;//0 ��ʼ��Ϸ���棬1ѡ���ͼ��Ԥ����������2չʾ�˶�
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
				if (keyPressed->code == sf::Keyboard::Key::Tab)
				{
					process++;
				}

				if (keyPressed->code == sf::Keyboard::Key::Enter && process == 3)
				{
					//player_try(player_map,tail_map);//��ҳ���
					Show_process(tail_map, ant, s_map, s_ant, window);//չʾ�˶�
					process++;
				}
			}
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())//�������ж�����Ƿ��ƶ���ĳ��
			{
				if (process == 0)
				{
					//cout << "������꣺" << mouseMoved->position.x << " " << mouseMoved->position.y << std::endl;
					if (mouseMoved->position.x >= 128 && mouseMoved->position.x <= 475 && mouseMoved->position.y >= 325 && mouseMoved->position.y <= 410)
					{

						SetCursor(customCursor2);//��ʱ�������ָ��ͼ��
					}
				}
			}
			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())//��갴��
			{
				if (mouseButtonPressed->button == sf::Mouse::Button::Left)
				{
					if (process == 0)
					{
						if (mouseButtonPressed->position.x >= 128 && mouseButtonPressed->position.x <= 475 && mouseButtonPressed->position.y >= 325 && mouseButtonPressed->position.y <= 410)
							process++;
					}
					if (process == 2)
					{
						if (mouseButtonPressed->position.x >= 0 && mouseButtonPressed->position.y >= 0 && mouseButtonPressed->position.y <= player_map.Height * 100 && mouseButtonPressed->position.x <= player_map.Width * 100)
							process += player_try(player_map, tail_map, s_map, s_ant, (int)mouseButtonPressed->position.x / 100 + 1, (int)mouseButtonPressed->position.y / 100 + 1);//��ҳ���		
						//tail_map->showMap();
					}
					if (process <= -2)
					{
						if (mouseButtonPressed->position.x >= 0 && mouseButtonPressed->position.y >= 0 && mouseButtonPressed->position.y <= head_map->Height * 100 && mouseButtonPressed->position.x <= head_map->Width * 100)
						{
							process += GoldenFingerMode_player_try(ant,head_map, s_map, s_ant, (int)mouseButtonPressed->position.x / 100 + 1, (int)mouseButtonPressed->position.y / 100 + 1, 5);
						}
					}
				}
			}
		}

		if (process == 1)
		{
			int choise = chooseMode(head_map, ant, s_map, s_ant, window);
			if (choise == -1)
			{
				return 0;
			}
			else if (choise == 3)
			{
				process = -2;
				tail_map = head_map;
				prop_list.push_back(Prop(5, 5, 0));//��������
				prop_list[prop_list.size() - 1].loadmap("tileMap/Prop.png");
			}
			else
			{
				process++;
				tail_map = head_map;
				Sports_process(goal_step, head_map, ant); //ģ���˶�
				player_map.copyMap(*head_map);
			}
		}
		else if (process == -7)
		{
			GoldenFinger_moveProcess(ant, head_map, s_map, s_ant, prop_list, window,5,process);//5 ��
		}
		window.clear();
		// draw the map
		if (process == 0)
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
			for (int i = 0; i < prop_list.size(); i++)
			{
				window.draw(prop_list[i]);
			}
		}
		window.display();
	}

	//test
	system("pause");
	//tail_map->showMap();//�����������ʵ�һ����ͼ
	return 0;
}