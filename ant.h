#ifndef ANT_H
#define ANT_H
#include "map.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum Direction { DOWN, LEFT, UP, RIGHT };

class Ant
{
public:
	Direction direction;//蚂蚁方向
	static int Ant_x, Ant_y;//当前蚂蚁坐标
	static int initial_x, initial_y;//初始坐标

	Ant();
	void move(Map*&);
};
class S_Ant : public sf::Drawable, public sf::Transformable//SFML地图类，用于显示Ant
{
public:
	bool loadmap(const std::filesystem::path& tileset, sf::Vector2u tileSize, Ant& ant);//瓦片集路径 瓦片大小 
	void S_showAnt(const Map* head_map, const Ant& ant, int);
	static sf::Vector2u tileSize;//瓦片大小
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::VertexArray m_ant;//地图顶点数组（动态）
	sf::Texture m_tileset;//地图纹理
};

#endif 