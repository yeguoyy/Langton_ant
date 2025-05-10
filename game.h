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
	bool loadmap(const std::filesystem::path& tileset);//��Ƭ��·�� ��Ƭ��С 
	static sf::Vector2u map_tileSize;//��ͼ��Ƭ��С
	static sf::Vector2u prop_tileSize;//������Ƭ��С
	Prop(int x, int y);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int m_x, m_y;
	sf::VertexArray m_prop;//��ͼ�������飨��̬��
	sf::Texture m_tileset;//��ͼ����
};
