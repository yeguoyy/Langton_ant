#ifndef MAP_H
#define MAP_H
//#include "ant.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Map
{
public:
	int** m_map;//地图数组 0白1黑 2障碍
	int Width;
	int Height;
	int Ant_color;//蚂蚁脚下颜色，用于赋给下一个地图
	int M_ant_x, M_ant_y;
	sf::Angle m_degree;
	Map* nextMap;
	Map* preMap;

	void showMap();
	void copyMap(Map& const map);
	void creatBar();
	void creatBar(int x, int y);
	Map();
	Map(Map& const map);
	~Map();
};
class S_Map : public sf::Drawable, public sf::Transformable//SFML地图类，用于显示地图
{
public:
	bool loadmap(const std::filesystem::path& tileset, sf::Vector2u tileSize, int** tiles, const int wide, const int height);//瓦片集路径 瓦片大小 瓦片数组 宽 高
	void S_showMap(const Map* head_map,int);
	void S_showMap(const Map* player_map);
	
	

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::VertexArray m_map;//地图顶点数组（动态）
	sf::Texture m_tileset;//地图纹理
};




#endif