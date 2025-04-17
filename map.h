#ifndef MAP_H
#define MAP_H
//#include "ant.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Map
{
public:
	int** m_map;//��ͼ���� 0��1�� 2�� 3�� 4�� 5��
	int Width;
	int Height;
	int Ant_color;//���Ͻ�����ɫ�����ڸ�����һ����ͼ
	Map* nextMap;

	void showMap();
	Map();
	Map(Map& const map);
	~Map();
};
class S_Map : public sf::Drawable, public sf::Transformable//SFML��ͼ�࣬������ʾ��ͼ
{
public:
	bool loadmap(const std::filesystem::path& tileset, sf::Vector2u tileSize, int** tiles, const int wide, const int height);//��Ƭ��·�� ��Ƭ��С ��Ƭ���� �� ��
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::VertexArray m_map;//��ͼ�������飨��̬��
	sf::Texture m_tileset;//��ͼ����
};





#endif