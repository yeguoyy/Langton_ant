#include "ant.h"
#include <iostream>


int Ant::Ant_x = 1;
int Ant::Ant_y = 1;
int Ant::initial_x = 1;
int Ant::initial_y = 1;
sf::Vector2u S_Ant::tileSize = { 100,100 };
Ant::Ant() {
	direction = DOWN;
	num_rocket = 10;
	num_big_rocket = 10;
	num_LaserPointer = 10;
	num_falcula = 10;
}
sf::Angle Way_to_Degrees(Direction direction)
{
	switch (direction) {
	case UP:
		return sf::degrees(0.0f);
	case RIGHT:
		return sf::degrees(90.0f);
	case DOWN:
		return sf::degrees(180.0f);
	case LEFT:
		return sf::degrees(270.0f);
	}
}
int Ant::move(Map*& map)
{
	Map* NewMap = new Map;
	NewMap->Height = map->Height;
	NewMap->Width = map->Width;
	NewMap->m_map = new int* [NewMap->Width + 1];
	for (int i = 1; i <= NewMap->Width; i++)
	{
		NewMap->m_map[i] = new int[NewMap->Height + 1];
	}//分配内存
	//NewMap->m_map= map->m_map;//复制原图 浅拷贝！！！！
	//因为这个是动态内存分配，这样复制相当于所有的指针都指向同一块内存，所以修改其中一个指针，另一个指针也会改变
	for (int i = 1; i <= NewMap->Width; i++)
	{
		for (int j = 1; j <= NewMap->Height; j++)
		{
			NewMap->m_map[i][j] = map->m_map[i][j];
		}
	}//复制原图

	NewMap->m_map[Ant_x][Ant_y] = map->Ant_color;//将蚂蚁脚下的方块赋给新图
	int new_x = Ant_x;
	int new_y = Ant_y;

	switch (direction) {
	case DOWN:
		new_y++;
		break;
	case LEFT:
		new_x--;
		break;
	case RIGHT:
		new_x++;
		break;
	case UP:
		new_y--;
		break;
	}
	//位置超出边界,掉头并颜色翻转
	if (new_x < 1 || new_x > NewMap->Width || new_y < 1 || new_y > NewMap->Height)
	{
		switch (direction)
		{
		case UP:
			direction = DOWN;

			break;
		case DOWN:
			direction = UP;

			break;
		case LEFT:
			direction = RIGHT;

			break;
		case RIGHT:
			direction = LEFT;

			break;
		}
	}
	else {
		Ant_x = new_x;
		Ant_y = new_y;
		//颜色翻转和转弯（白右黑左）
		if (NewMap->m_map[Ant_x][Ant_y] == 0) {
			NewMap->Ant_color = 1;//颜色翻转
			NewMap->m_map[Ant_x][Ant_y] = 1;
			if (direction == RIGHT)
			{
				direction = DOWN;
			}
			else {
				direction = (Direction)((int)direction + 1);
			}
		}
		else if (NewMap->m_map[Ant_x][Ant_y] == 1) {
			NewMap->Ant_color = 0;//颜色翻转
			NewMap->m_map[Ant_x][Ant_y] = 0;
			if (direction == DOWN)
			{
				direction = RIGHT;
			}
			else {
				direction = (Direction)((int)direction - 1);
			}
		}
		else if (NewMap->m_map[Ant_x][Ant_y] >= 2)//撞到障碍物
		{
			return -1;
		}
		
	}
	NewMap->M_ant_x = Ant_x;
	NewMap->M_ant_y = Ant_y;
	NewMap->m_degree=Way_to_Degrees(direction);
	NewMap->preMap= map;
	map->nextMap = NewMap;//将新图赋给nextMap
}


void S_Ant::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_ant, states);
}
bool S_Ant::loadmap(const std::filesystem::path& tileset, Ant& ant,const Map *head_map)
{
	if (!m_tileset.loadFromFile(tileset))//读取Ant纹理
		return false;
	m_ant.setPrimitiveType(sf::PrimitiveType::Triangles);//设置顶点类型
	m_ant.resize(6);//顶点数组的大小为宽度和高度乘积的6倍，因为每个单元格由两个三角形（六个点）组成
	int x = ant.initial_x-1;
	int y = ant.initial_y-1;
	sf::Vertex* triangles = &m_ant[0];
	triangles[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
	triangles[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
	triangles[2].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
	triangles[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
	triangles[4].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
	triangles[5].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);

	triangles[0].texCoords = sf::Vector2f(0 * tileSize.x, 0 * tileSize.y);
	triangles[1].texCoords = sf::Vector2f((0 + 1) * tileSize.x, 0 * tileSize.y);
	triangles[2].texCoords = sf::Vector2f(0 * tileSize.x, (0 + 1) * tileSize.y);
	triangles[3].texCoords = sf::Vector2f(0 * tileSize.x, (0 + 1) * tileSize.y);
	triangles[4].texCoords = sf::Vector2f((0 + 1) * tileSize.x, 0 * tileSize.y);
	triangles[5].texCoords = sf::Vector2f((0 + 1) * tileSize.x, (0 + 1) * tileSize.y);

	sf::Vector2f position = sf::Vector2f((x + 0.5) * tileSize.x, (y + 0.5) * tileSize.y);
	this->setOrigin(position);
	this->setPosition(position);
	this->setRotation(head_map->m_degree);
	return true;
}



void S_Ant::S_showAnt(const Map* head_map)
{
		std::cout << "当前蚂蚁脚下为：";
		int color = head_map->Ant_color;
		if (color == 0)
		{
			std::cout << "白色" << std::endl;
		}
		else if (color == 1)
		{
			std::cout << "黑色" << std::endl;
		}
		sf::Vertex* triangles = &m_ant[0];
		std::cout << "当前位置：" << head_map->M_ant_x << " " << head_map->M_ant_y << std::endl;
		this->setPosition(sf::Vector2f((head_map->M_ant_x - 0.5) * tileSize.x, (head_map->M_ant_y - 0.5) * tileSize.y));

		triangles[0].texCoords = sf::Vector2f(color * tileSize.x, 0 * tileSize.y);
		triangles[1].texCoords = sf::Vector2f((color + 1) * tileSize.x, 0 * tileSize.y);
		triangles[2].texCoords = sf::Vector2f(color * tileSize.x, (0+ 1) * tileSize.y);
		triangles[3].texCoords = sf::Vector2f(color * tileSize.x, (0 + 1) * tileSize.y);
		triangles[4].texCoords = sf::Vector2f((color + 1) * tileSize.x, 0 * tileSize.y);
		triangles[5].texCoords = sf::Vector2f((color + 1) * tileSize.x, (0 + 1) * tileSize.y);

		this->setRotation(head_map->m_degree);
}
