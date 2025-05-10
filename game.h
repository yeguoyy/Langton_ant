#pragma once
#include "map.h"
#include "ant.h"
int chooseMode(Map*&, Ant&, S_Map&, S_Ant&, sf::RenderWindow&);
void creatMap(Map*&, Ant&, S_Map&, S_Ant&, sf::RenderWindow&);
void GoldenFingerMode_creatMap(Map*&, Ant&, S_Map&, S_Ant&, sf::RenderWindow&);
int player_try(Map&, Map*& const, S_Map&, S_Ant&, int, int);
int GoldenFingerMode_player_try(Map*&, S_Map&, S_Ant&, int, int, int times);
void introduction(sf::Text&);
void Sports_process(int step, Map*&, Ant&);
void Show_process(Map*, Ant&, S_Map&, S_Ant&, sf::RenderWindow&);
void pause(sf::RenderWindow&);
sf::Angle Way_to_Degree(Direction direction);

class Prop : public sf::Drawable, public sf::Transformable
{
public:
	bool loadmap(const std::filesystem::path& tileset);//瓦片集路径 瓦片大小 
	static sf::Vector2u map_tileSize;//地图瓦片大小
	static sf::Vector2u prop_tileSize;//道具瓦片大小
	Prop(int x, int y);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int m_x, m_y;
	sf::VertexArray m_prop;//地图顶点数组（动态）
	sf::Texture m_tileset;//地图纹理
};
