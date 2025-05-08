#ifndef MAP_H
#define MAP_H
//#include "ant.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Map
{
public:
	int** m_map;//��ͼ���� 0��1�� 2�ϰ�
	int Width;
	int Height;
	int Ant_color;//���Ͻ�����ɫ�����ڸ�����һ����ͼ
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
class S_Map : public sf::Drawable, public sf::Transformable//SFML��ͼ�࣬������ʾ��ͼ
{
public:
	bool loadmap(const std::filesystem::path& tileset, sf::Vector2u tileSize, int** tiles, const int wide, const int height);//��Ƭ��·�� ��Ƭ��С ��Ƭ���� �� ��
	void S_showMap(const Map* head_map,int);
	void S_showMap(const Map* player_map);
	
	

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::VertexArray m_map;//��ͼ�������飨��̬��
	sf::Texture m_tileset;//��ͼ����
};




#endif