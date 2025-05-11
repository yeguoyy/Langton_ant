#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Prop : public sf::Drawable, public sf::Transformable
{
public:
	bool loadmap(const std::filesystem::path& tileset);//��Ƭ��·�� ��Ƭ��С 
	static sf::Vector2u map_tileSize;//��ͼ��Ƭ��С
	static sf::Vector2u prop_tileSize;//������Ƭ��С
	Prop(int x, int y,int type);
	int getType();
	int getX();
	int getY();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int m_type; //0�����1����ָʾ��
	int m_x, m_y;
	sf::VertexArray m_prop;//��ͼ�������飨��̬��
	sf::Texture m_tileset;//��ͼ����
};
