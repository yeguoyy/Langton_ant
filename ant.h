#ifndef ANT_H
#define ANT_H
#include "map.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum Direction { DOWN, LEFT, UP, RIGHT };

class Ant
{
public:
	Direction direction;//���Ϸ���
	static int Ant_x, Ant_y;//��ǰ��������
	static int initial_x, initial_y;//��ʼ����

	Ant();
	void move(Map*&);
};
class S_Ant : public sf::Drawable, public sf::Transformable//SFML��ͼ�࣬������ʾAnt
{
public:
	bool loadmap(const std::filesystem::path& tileset, sf::Vector2u tileSize, Ant& ant);//��Ƭ��·�� ��Ƭ��С 
	void S_showAnt(const Map* head_map, const Ant& ant, int);
	static sf::Vector2u tileSize;//��Ƭ��С
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::VertexArray m_ant;//��ͼ�������飨��̬��
	sf::Texture m_tileset;//��ͼ����
};

#endif 