#include "game.h"// ͬʱ��������ͷ�ļ�
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;


bool Read_map(string, Map*&, Ant&,S_Map&, S_Ant& ,sf::RenderWindow&);
static int x, y;

int chooseMode(Map*& head_map, Ant& ant,S_Map &s_map,S_Ant &s_ant, sf::RenderWindow &window)
{
	cout << "ѡ��ؿ�ģʽ�밴1��������ɹؿ�ģʽ�밴2,����ָģʽ�밴3" << endl;
	int choice;
	while (true)
	{
		cin >> choice;
		if (cin.fail() || (choice != 1 && choice != 2&&choice !=3))
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
		cout << "������ؿ���ţ�1��2��3��" << endl;
		int num;
		while (true)
		{
			cin >> num;
			if (cin.fail() || (num != 1 && num != 2&& num!=3))
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
		filename = "map\\"+to_string(num) + ".txt";// ������ת��Ϊ�ַ���
		//cout << filename << endl;
		if (!Read_map(filename, head_map, ant,s_map,s_ant,window))// ��ȡ�ؿ���ͼ
		{
			return -1;
		}
		break;
	case 2:
		creatMap(head_map, ant, s_map, s_ant, window);
		break;
	case 3:
        //introduction(window);
        //pause(window);
		GoldenFingerMode_creatMap(head_map, ant, s_map, s_ant, window);
		return 3;
        break;
        default:
			return -1;
	}
	system("cls");
	return 1;
}
void creatMap(Map*& head_map, Ant& ant, S_Map&s_map, S_Ant&s_ant, sf::RenderWindow& window)
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
		else if (x > 15 || y > 15)
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
	head_map->M_ant_x =  ant.Ant_x;
    head_map->M_ant_y = ant.Ant_y;
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
					head_map->m_map[i][j] = 1;
				}
				else
				{
					head_map->m_map[i][j] = 0;
				}
			}
		}
	}
	int way = rand() % 4 + 1;
	switch (way)
	{
	case 2:
		ant.direction = UP;
		break;
	case 3:
		ant.direction = DOWN;
		break;
	case 4:
		ant.direction = LEFT;
		break;
	case 5:
		ant.direction = RIGHT;
		break;
	}
	head_map->m_degree = Way_to_Degree(ant.direction);
	window.setSize(sf::Vector2u(static_cast<unsigned int>(x * 100), static_cast<unsigned int>(y * 100)));//�ı䴰�ڴ�СҪע��ı���ͼ���ĵ�
	sf::View view = window.getDefaultView();
	view.setSize(sf::Vector2f(static_cast<float>(x * 100), static_cast<float>(y * 100)));
	view.setCenter(sf::Vector2f(static_cast<float>(x * 50), static_cast<float>(y * 50))); // ������ͼ���ĵ�
	window.setView(view);
	if (!s_map.loadmap("tileMap\\S_Map.png", { 100,100 }, head_map->m_map, x, y))
	{
		cout << "��ͼ����ʧ��" << endl;
		system("pause");
	}

	if (!s_ant.loadmap("tileMap\\S_Ant.png", { 100,100 }, ant, head_map))
	{
		cout << "Ant����ʧ��" << endl;
		system("pause");
	}
}

void GoldenFingerMode_creatMap(Map*& head_map, Ant& ant, S_Map& s_map, S_Ant& s_ant, sf::RenderWindow& window)
{
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
		else if (x > 15 || y > 15)
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
	head_map->M_ant_x = ant.Ant_x;
	head_map->M_ant_y = ant.Ant_y;
	// ��̬�����ά�ڴ�
	head_map->m_map = new int* [head_map->Width + 1];// ��̬�����ڴ�
	for (int i = 1; i <= head_map->Width; i++)
	{
		head_map->m_map[i] = new int[head_map->Height + 1];// ��̬�����ڴ�
	}
	//ȫ��
	
	for (int i = 1; i <= head_map->Width; i++)
	{
		for (int j = 1; j <= head_map->Height; j++)
		{
				head_map->m_map[i][j] = 0;
		}
	}
	head_map->m_map[ant.Ant_x][ant.Ant_y] = rand() % 4 + 1;
	switch (head_map->m_map[ant.Ant_x][ant.Ant_y])
	{
	case 2:
		ant.direction = UP;
		break;
	case 3:
		ant.direction = DOWN;
		break;
	case 4:
		ant.direction = LEFT;
		break;
	case 5:
		ant.direction = RIGHT;
		break;

	}
	head_map->m_degree = Way_to_Degree(ant.direction);
	window.setSize(sf::Vector2u(static_cast<unsigned int>(x * 100), static_cast<unsigned int>(y * 100)));//�ı䴰�ڴ�СҪע��ı���ͼ���ĵ�
	sf::View view = window.getDefaultView();
	view.setSize(sf::Vector2f(static_cast<float>(x * 100), static_cast<float>(y * 100)));
	view.setCenter(sf::Vector2f(static_cast<float>(x * 50), static_cast<float>(y * 50))); // ������ͼ���ĵ�
	window.setView(view);
	if (!s_map.loadmap("tileMap\\S_Map.png", { 100,100 }, head_map->m_map, x, y))
	{
		cout << "��ͼ����ʧ��" << endl;
		system("pause");
	}

	if (!s_ant.loadmap("tileMap\\S_Ant.png", { 100,100 }, ant, head_map))
	{
		cout << "Ant����ʧ��" << endl;
		system("pause");
	}
}

void Map::creatBar()
{
	srand(time(NULL));
	int bar_x=rand() % this->Width + 1;
    int bar_y=rand() % this->Height + 1;
	if (this->m_map[bar_x][bar_y] == 3)
	{
		this->creatBar();
		return;
	}
    m_map[bar_x][bar_y] = 3;
	return;
}


bool Read_map(string filename, Map*& head_map, Ant& ant,S_Map &s_map, S_Ant& s_ant, sf::RenderWindow & window)
{
	fstream fil(filename);

	if (!fil.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		system("pause");
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
		head_map->M_ant_x = ant.Ant_x;
        head_map->M_ant_y = ant.Ant_y;
		int way;
		fil >> way;
		switch (way)
		{
		case 2:
			ant.direction = UP;
			break;
		case 3:
			ant.direction = DOWN;
			break;
		case 4:
			ant.direction = LEFT;
			break;
		case 5:
			ant.direction = RIGHT;
			break;
		}
		head_map->m_degree = Way_to_Degree(ant.direction);
		//cout << "w=" << w << "h=" << h << endl;
		window.setSize(sf::Vector2u(static_cast<unsigned int>(x * 100), static_cast<unsigned int>(y * 100)));
		sf::View view = window.getDefaultView();
		view.setSize(sf::Vector2f(static_cast<float>(x * 100), static_cast<float>(y * 100)));
		view.setCenter(sf::Vector2f(static_cast<float>(x * 50), static_cast<float>(y * 50))); // ������ͼ���ĵ�
		window.setView(view);
        if(!s_map.loadmap("tileMap\\S_Map.png", {100,100}, head_map->m_map, x, y))
            return false;
		if (!s_ant.loadmap("tileMap\\S_Ant.png", { 100,100 }, ant,head_map))
            return false;
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
	preMap = nullptr;
    M_ant_x = 0;
    M_ant_y = 0;
	m_degree = sf::degrees( 0.0f );
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
			case 1:
				cout << '#' << " ";
				break;
			/*case 2:
				cout << '1' << " ";
				break;
			case 3:
				cout << 'v' << " ";
				break;
			case 4:
				cout << '<' << " ";
				break;
			case 5:
				cout << '>' << " ";
				break;*/
			default:
				cout << m_map[i][j] << " ";
				break;
			}
		}
		cout << endl;
	}
}
void S_Map::S_showMap(const Map* head_map, int S_step)
{
	if (S_step > 0)
	{
		for (int i = 1; i <= head_map->Width; i++)
		{
			for (int j = 1; j <= head_map->Height; j++)
			{
				if (head_map->m_map[i][j] != head_map->preMap->m_map[i][j])//�����һ��
				{
					int tile_x= head_map->m_map[i][j];
					int tile_y = 0;
					sf::Vertex* triangles = &m_map[((i - 1) + (j - 1) * head_map->Width) * 6];
					triangles[0].texCoords = sf::Vector2f(tile_x * 100, tile_y * 100);
					triangles[1].texCoords = sf::Vector2f((tile_x + 1) * 100, tile_y * 100);
					triangles[2].texCoords = sf::Vector2f(tile_x * 100, (tile_y + 1) * 100);
					triangles[3].texCoords = sf::Vector2f(tile_x * 100, (tile_y + 1) * 100);
					triangles[4].texCoords = sf::Vector2f((tile_x + 1) *100, tile_y * 100);
					triangles[5].texCoords = sf::Vector2f((tile_x + 1) * 100, (tile_y + 1) * 100);
				}
			}
		}
	}
	else if (S_step == 0)
	{
		for (int i = 1; i <= head_map->Width; i++)
		{
			for (int j = 1; j <= head_map->Height; j++)
			{
					int tile_x = head_map->m_map[i][j];
					int tile_y = 0;
					sf::Vertex* triangles = &m_map[((i - 1) + (j - 1) * head_map->Width) * 6];
					triangles[0].texCoords = sf::Vector2f(tile_x * 100, tile_y * 100);
					triangles[1].texCoords = sf::Vector2f((tile_x + 1) * 100, tile_y * 100);
					triangles[2].texCoords = sf::Vector2f(tile_x * 100, (tile_y + 1) * 100);
					triangles[3].texCoords = sf::Vector2f(tile_x * 100, (tile_y + 1) * 100);
					triangles[4].texCoords = sf::Vector2f((tile_x + 1) * 100, tile_y * 100);
					triangles[5].texCoords = sf::Vector2f((tile_x + 1) * 100, (tile_y + 1) * 100);
			}
		}
	}
}
void S_Map::S_showMap(const Map* head_map)
{
	for (int i = 1; i <= head_map->Width; i++)
	{
		for (int j = 1; j <= head_map->Height; j++)
		{
				int tile_x = head_map->m_map[i][j];
				int tile_y = 0;
				sf::Vertex* triangles = &m_map[((i - 1) + (j - 1) * head_map->nextMap->Width) * 6];
				triangles[0].texCoords = sf::Vector2f(tile_x * 100, tile_y * 100);
				triangles[1].texCoords = sf::Vector2f((tile_x + 1) * 100, tile_y * 100);
				triangles[2].texCoords = sf::Vector2f(tile_x * 100, (tile_y + 1) * 100);
				triangles[3].texCoords = sf::Vector2f(tile_x * 100, (tile_y + 1) * 100);
				triangles[4].texCoords = sf::Vector2f((tile_x + 1) * 100, tile_y * 100);
				triangles[5].texCoords = sf::Vector2f((tile_x + 1) * 100, (tile_y + 1) * 100);
		}
	}
}
Map::Map(Map& map)
{
	this->Width = map.Width;
	this->Height = map.Height;
	this->Ant_color = map.Ant_color;
    this->M_ant_x = map.M_ant_x;
    this->M_ant_y = map.M_ant_y;
	this->m_degree= map.m_degree;
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
	this->preMap = map.preMap;
}
void Map::copyMap(Map& map)
{
	this->Width = map.Width;
	this->Height = map.Height;
	this->Ant_color = map.Ant_color;
	this->M_ant_x = map.M_ant_x;
	this->M_ant_y = map.M_ant_y;
	this->m_degree = map.m_degree;
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
	this->preMap = map.preMap;
}

bool S_Map::loadmap(const std::filesystem::path& tileset, sf::Vector2u tileSize,int** tiles, const int width, const int height)
{
	if (!m_tileset.loadFromFile(tileset))//��ȡ��Ƭ������
		return false;

	m_map.setPrimitiveType(sf::PrimitiveType::Triangles);//���ö�������
	m_map.resize(width * height * 6);//��������Ĵ�СΪ��Ⱥ͸߶ȳ˻���6������Ϊÿ����Ԫ�������������Σ������㣩���

	for (unsigned int i = 0; i < width; ++i)
	{
        for (unsigned int j = 0; j < height; ++j)
        {
			const int tileNumber = tiles[i+1][j+1];//��ȡ��ǰ��Ԫ���е������� 0 1 2 3 
			//��Ƭ�������մ����ң����м����ķ�ʽ����

			//m_tileset.getSize().x ��ʾ����Ŀ�ȣ�tileSize.x ��ʾÿ����Ԫ��Ŀ��  m_tileset.getSize().x / tileSize.x ������Ƭ������
			//const int tile_x = tileNumber % (m_tileset.getSize().x / tileSize.x);//���㵱ǰ��Ƭ���ڵ�������
            //const int tile_y = tileNumber / (m_tileset.getSize().y / tileSize.y);//���㵱ǰ��Ƭ���ڵ�������
			int tile_x = tileNumber;
			int tile_y = 0;

			sf::Vertex* triangles = &m_map[(i + j * width) * 6];//��ȡ��ǰ���������ָ��

			// define the 6 corners of the two triangles
			triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
			triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
			triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

			// define the 6 matching texture coordinates
			triangles[0].texCoords = sf::Vector2f(tile_x * tileSize.x, tile_y * tileSize.y);
			triangles[1].texCoords = sf::Vector2f((tile_x + 1) * tileSize.x, tile_y * tileSize.y);
			triangles[2].texCoords = sf::Vector2f(tile_x * tileSize.x, (tile_y + 1) * tileSize.y);
			triangles[3].texCoords = sf::Vector2f(tile_x * tileSize.x, (tile_y + 1) * tileSize.y);
			triangles[4].texCoords = sf::Vector2f((tile_x + 1) * tileSize.x, tile_y * tileSize.y);
			triangles[5].texCoords = sf::Vector2f((tile_x + 1) * tileSize.x, (tile_y + 1) * tileSize.y);
        }
	}
    return true;

}
void S_Map::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_map, states);
}

