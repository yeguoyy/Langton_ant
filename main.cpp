#include "game.h"
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

#define goal_step 100
using namespace std;

//����˵���� ײǽ�� ������ɵ�ͼ�� �طŹ���(��ʱ����)��  ��ʼλ�� ������ ������� �����ţ��ϰ��ʤ������ ���¿�ʼ��Ϸ�����ã�
//����ָ��ս����ͨ���ı�ڰף�����С�Ĳ��������ϵ�Ŀ������������˵�����ߡ��÷֣�
//���ߣ���̹�˴�ս������̣���С�ɵ��̣���λ��ץȡ������������צ��
//�¼�����������ӣ��������ɣ���ͼ���˵�����Χϴ�ƣ���

int main()
{
	srand(time(NULL));
	Ant ant;
	//����ָ��������ȡÿһ����ͼ�ĵ�ַ
	Map* head_map = new Map;
	Map* tail_map = new Map;
	Map player_map;
	
	sf::RenderWindow window(sf::VideoMode({ 800, 1200 }), L"��������", sf::Style::Default);
	sf::Texture Start_texture;
	if (!Start_texture.loadFromFile("context/Start_game_cover.png", false, sf::IntRect({ 0, 0 }, { 1024, 1536 })))//sf::IntRect ����һ���򵥵�ʵ�����ͣ���ʾһ�����Ρ����Ĺ��캯�����ܾ��ε����Ͻ�����ʹ�С��
		return -1;
	sf::Sprite Start_game_cover(Start_texture);
	sf::Vector2u original_Start_Size = Start_texture.getSize();
	sf::Vector2f scale_Start_Size = { 800.f / original_Start_Size.x, 1200.f / original_Start_Size.y };
	Start_game_cover.setScale(scale_Start_Size);//��������

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
	sf::VertexArray line(sf::PrimitiveType::LineStrip, 6);
	//�����ͷβ���
	int process = 0;//0 ��ʼ��Ϸ���棬1ѡ���ͼ��Ԥ����������2չʾ�˶�
	int if_line = 0;
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
				if (keyPressed->code == sf::Keyboard::Key::Escape)//�˳���Ϸ
				{
					process = 4;
				}

				if (keyPressed->code == sf::Keyboard::Key::Enter && process == 3)//�طŹ���
				{
					//player_try(player_map,tail_map);//��ҳ���
					Show_process(tail_map, ant, s_map, s_ant, window);//չʾ�˶�
					process++;
				}
				if (keyPressed->code == sf::Keyboard::Key::U && process <= -2)
				{
					if (ant.num_LaserPointer > 0)
					{
						if_line += 3;
						ant.num_LaserPointer--;
						cout << "����ָʾ�����ɹ�������" << endl;
						cout << "��ǰ����ָʾ��������" << if_line << endl;
					}
					else
					{
                        cout << "����ָʾ�������ˣ�����" << endl;
						cout << "��ȥ��ͼ��ʰȡ�� >_<" <<endl;
					}
				}
				if (keyPressed->code == sf::Keyboard::Key::L && process <= -2)
				{
					if (ant.num_falcula > 0)
					{
						sf::Vector2f Position = s_ant.getPosition();
						falcula(ant, head_map, s_map, s_ant, prop_list, window, Position);
						ant.num_falcula--;
					}
					else
					{
						cout << "��צ�����ˣ�����" << endl;
						cout << "��ȥ��ͼ��ʰȡ�� >_<" << endl;
					}
				}
				if (keyPressed->code == sf::Keyboard::Key::Enter && process <= -2)
				{
					cout << "�ɹ���������..." << endl;
					process = -7;
				}
			}
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())//�������ж�����Ƿ��ƶ���ĳ��
			{
				if (process == 0)
				{
					//cout << "������꣺" << mouseMoved->position.x << " " << mouseMoved->position.y << std::endl;
					if (mouseMoved->position.x >= 160 && mouseMoved->position.x <= 642 && mouseMoved->position.y >= 423 && mouseMoved->position.y <= 555)
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
						if (mouseButtonPressed->position.x >= 160 && mouseButtonPressed->position.x <= 642 && mouseButtonPressed->position.y >= 423 && mouseButtonPressed->position.y <= 555)
							process++;
					}
					if (process == 2)
					{
						if (mouseButtonPressed->position.x >= 0 && mouseButtonPressed->position.y >= 0 && mouseButtonPressed->position.y <= player_map.Height * 100 && mouseButtonPressed->position.x <= player_map.Width * 100)
							process += player_try(player_map, tail_map, s_map, s_ant, (int)mouseButtonPressed->position.x / 100 + 1, (int)mouseButtonPressed->position.y / 100 + 1);//��ҳ���		
						
					}
					if (process <= -2)
					{
						
						if (mouseButtonPressed->position.x >= 0 && mouseButtonPressed->position.y >= 0 && mouseButtonPressed->position.y <= head_map->Height * 100 && mouseButtonPressed->position.x <= head_map->Width * 100)
						{
							process += GoldenFingerMode_player_try(ant,head_map, s_map, s_ant, (int)mouseButtonPressed->position.x / 100 + 1, (int)mouseButtonPressed->position.y / 100 + 1,if_line);
							cout <<"ʣ�����������"<<(process+7)<<"��"<<endl;
							cout<< "��Enter������" << endl;
						}
						Confirm_line(line, *head_map);//����·������
						
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
				process = -2;//����ѭ��
				cout << "�������" << endl;
				cout << "��������ڰ׸��Ӹı����ϵ��˶��켣��Ҫ����ײ���ϰ����" << endl;
				tail_map = head_map;
				prop_list.push_back(Prop(5, 5, 0));//��������
				prop_list[prop_list.size() - 1].loadmap("tileMap/Prop.png");
			}
			else if (choise == 4)
			{
				process = 4;
			}
			else
			{
				//��ͨģʽ
				process++;
				tail_map = head_map;
				Sports_process(goal_step, head_map, ant); //ģ���˶�
				player_map.copyMap(*head_map);
			}
		}
		else if (process == -7)
		{
			
			GoldenFinger_moveProcess(ant, head_map, s_map, s_ant, prop_list, window,5,process,if_line);//5 ��
			if (if_line > 0)//ÿ���غϿ�һ���
				if_line--;
			ant.Rounds += 1;
			cout << "����ָʾ��ʣ�����:" << if_line << endl;
			cout << "�������"<<endl;
			cout << "��������ڰ׸��Ӹı����ϵ��˶��켣��Ҫ����ײ���ϰ����" << endl;
			Confirm_line(line, *head_map);
		}
		else if (process == 4)//��Ϸ�������»ص�������
		{
			delete head_map;
			head_map = new Map;
			ant = Ant();
			player_map = Map();
			for  (int i = 0; i < prop_list.size(); i++)
			{
				prop_list.erase(prop_list.begin() + i);
			}
			if_line = 0;
			process = 0;
			window.setSize(sf::Vector2u(800,1200));//�ı䴰�ڴ�СҪע��ı���ͼ���ĵ�
			sf::View view = window.getDefaultView();
			view.setSize(sf::Vector2f(800,1200));
			view.setCenter(sf::Vector2f(400,600)); // ������ͼ���ĵ�
			window.setView(view);
			s_map= S_Map();
			s_ant = S_Ant();
			sf::Image image;
			if (!image.loadFromFile("context/Start_game_cover.png"))//��ͨģʽ
			{
				system("pause");
				return -1;
			}
			Start_texture.update(image);
			window.clear();
			window.draw(Start_game_cover);
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
			if (if_line!=0)//ʣ�������Ϊ0��show��
			window.draw(line);
		}
		window.display();
	}

	system("pause");
	return 0;
}