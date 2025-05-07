#include "game.h"// 同时包含两个头文件
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
	cout << "选择关卡模式请按1，随机生成关卡模式请按2,金手指模式请按3" << endl;
	int choice;
	while (true)
	{
		cin >> choice;
		if (cin.fail() || (choice != 1 && choice != 2&&choice !=3))
		{
			cout << "输入错误,请重新输入" << endl;
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
		cout << "请输入关卡编号（1、2、3）" << endl;
		int num;
		while (true)
		{
			cin >> num;
			if (cin.fail() || (num != 1 && num != 2&& num!=3))
			{
				cout << "输入错误,请重新输入" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else
			{
				break;
			}
		}
		filename = "map\\"+to_string(num) + ".txt";// 将数字转换为字符串
		//cout << filename << endl;
		if (!Read_map(filename, head_map, ant,s_map,s_ant,window))// 读取关卡地图
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
	cout << "请输入想要生成的题目的长度和宽度" << endl;

	while (true)
	{
		cin >> x >> y;
		if (cin.fail() || (x <= 0 || y <= 0))
		{
			cout << "输入错误,请重新输入" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (x > 15 || y > 15)
		{
			cout << "输入过大,请重新输入" << endl;
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
	// 动态分配二维内存
	head_map->m_map = new int* [head_map->Width + 1];// 动态分配内存
	for (int i = 1; i <= head_map->Width; i++)
	{
		head_map->m_map[i] = new int[head_map->Height + 1];// 动态分配内存
	}
	//最外层是白色更规整 每10格多一层白色
	int edge = ((head_map->Width < head_map->Height) ? head_map->Width : head_map->Height) / 10 + 1;
	for (int i = 1; i <= head_map->Width; i++)
	{
		for (int j = 1; j <= head_map->Height; j++)
		{
			if (i <= edge || i >= head_map->Width - (edge - 1) || j <= edge || j >= head_map->Height - (edge - 1))
			{
				head_map->m_map[i][j] = 0;
			}
			else//test 在此加入随机生成逻辑 分块？
			{
				/*if (rand() % 2 == 0)
				{
					head_map->m_map[i][j] = 8;
				}
				else
				{
					head_map->m_map[i][j] = 0;
				}*/
				/*初级逻辑，越靠近中间越容易是黑色*/
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
	window.setSize(sf::Vector2u(static_cast<unsigned int>(x * 100), static_cast<unsigned int>(y * 100)));//改变窗口大小要注意改变视图中心点
	sf::View view = window.getDefaultView();
	view.setSize(sf::Vector2f(static_cast<float>(x * 100), static_cast<float>(y * 100)));
	view.setCenter(sf::Vector2f(static_cast<float>(x * 50), static_cast<float>(y * 50))); // 设置视图中心点
	window.setView(view);
	if (!s_map.loadmap("tileMap\\S_Map.png", { 100,100 }, head_map->m_map, x, y))
	{
		cout << "地图加载失败" << endl;
		system("pause");
	}

	if (!s_ant.loadmap("tileMap\\S_Ant.png", { 100,100 }, ant, head_map))
	{
		cout << "Ant加载失败" << endl;
		system("pause");
	}
}

void GoldenFingerMode_creatMap(Map*& head_map, Ant& ant, S_Map& s_map, S_Ant& s_ant, sf::RenderWindow& window)
{
	cout << "请输入想要生成的题目的长度和宽度" << endl;
	while (true)
	{
		cin >> x >> y;
		if (cin.fail() || (x <= 0 || y <= 0))
		{
			cout << "输入错误,请重新输入" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (x > 15 || y > 15)
		{
			cout << "输入过大,请重新输入" << endl;
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
	// 动态分配二维内存
	head_map->m_map = new int* [head_map->Width + 1];// 动态分配内存
	for (int i = 1; i <= head_map->Width; i++)
	{
		head_map->m_map[i] = new int[head_map->Height + 1];// 动态分配内存
	}
	//全白
	
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
	window.setSize(sf::Vector2u(static_cast<unsigned int>(x * 100), static_cast<unsigned int>(y * 100)));//改变窗口大小要注意改变视图中心点
	sf::View view = window.getDefaultView();
	view.setSize(sf::Vector2f(static_cast<float>(x * 100), static_cast<float>(y * 100)));
	view.setCenter(sf::Vector2f(static_cast<float>(x * 50), static_cast<float>(y * 50))); // 设置视图中心点
	window.setView(view);
	if (!s_map.loadmap("tileMap\\S_Map.png", { 100,100 }, head_map->m_map, x, y))
	{
		cout << "地图加载失败" << endl;
		system("pause");
	}

	if (!s_ant.loadmap("tileMap\\S_Ant.png", { 100,100 }, ant, head_map))
	{
		cout << "Ant加载失败" << endl;
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
		cout << "文件打开失败" << endl;
		system("pause");
		return false;
	}
	else {
		fil >> x >> y;// 读取地图宽高
		
		head_map->Width = x;
		head_map->Height = y;
		// 动态分配二维内存
		head_map->m_map = new int* [head_map->Width + 1];// 动态分配内存
		for (int i = 1; i <= head_map->Width; i++) {
			head_map->m_map[i] = new int[head_map->Height + 1];// 动态分配内存
		}
		// 读取地图 (1,1)为左上角 读取顺序和分配内存顺序不一样
		for (int j = 1; j <= head_map->Height; j++) {
			for (int i = 1; i <= head_map->Width; i++) {
				fil >> head_map->m_map[i][j];
			}
		}
		//传入起始位置
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
		view.setCenter(sf::Vector2f(static_cast<float>(x * 50), static_cast<float>(y * 50))); // 设置视图中心点
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
//1上1 v下2 <左3 >右4
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
				if (head_map->m_map[i][j] != head_map->preMap->m_map[i][j])//如果不一样
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
	if (!m_tileset.loadFromFile(tileset))//读取瓦片集纹理
		return false;

	m_map.setPrimitiveType(sf::PrimitiveType::Triangles);//设置顶点类型
	m_map.resize(width * height * 6);//顶点数组的大小为宽度和高度乘积的6倍，因为每个单元格由两个三角形（六个点）组成

	for (unsigned int i = 0; i < width; ++i)
	{
        for (unsigned int j = 0; j < height; ++j)
        {
			const int tileNumber = tiles[i+1][j+1];//获取当前单元格中的纹理编号 0 1 2 3 
			//瓦片集纹理按照从左到右，换行继续的方式排列

			//m_tileset.getSize().x 表示纹理的宽度，tileSize.x 表示每个单元格的宽度  m_tileset.getSize().x / tileSize.x 计算瓦片集纹理
			//const int tile_x = tileNumber % (m_tileset.getSize().x / tileSize.x);//计算当前瓦片所在的行索引
            //const int tile_y = tileNumber / (m_tileset.getSize().y / tileSize.y);//计算当前瓦片所在的列索引
			int tile_x = tileNumber;
			int tile_y = 0;

			sf::Vertex* triangles = &m_map[(i + j * width) * 6];//获取当前顶点数组的指针

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

