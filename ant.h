#ifndef ANT_H
#define ANT_H
#include "map.h"
#include "prop.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum Direction { DOWN, LEFT, UP, RIGHT };

class Ant
{
public:
	Direction direction;//蚂蚁方向
	static int Ant_x, Ant_y;//当前蚂蚁坐标
	static int initial_x, initial_y;//初始坐标
	int num_rocket;
	int num_big_rocket;
	int num_LaserPointer;
	int num_falcula;

	int Rounds;
	int DestroyedStones;

	Ant();
	int move(Map*&);
};
class S_Ant : public sf::Drawable, public sf::Transformable//SFML地图类，用于显示Ant
{
public:
	bool loadmap(const std::filesystem::path& tileset, Ant& ant,const Map * head_map);//瓦片集路径 瓦片大小 
	void S_showAnt(const Map* head_map);
	static sf::Vector2u tileSize;//瓦片大小
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::VertexArray m_ant;//地图顶点数组（动态）
	sf::Texture m_tileset;//地图纹理
};

#endif 