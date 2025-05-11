#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Prop : public sf::Drawable, public sf::Transformable
{
public:
	bool loadmap(const std::filesystem::path& tileset);//瓦片集路径 瓦片大小 
	static sf::Vector2u map_tileSize;//地图瓦片大小
	static sf::Vector2u prop_tileSize;//道具瓦片大小
	Prop(int x, int y,int type);
	int getType();
	int getX();
	int getY();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int m_type; //0火箭，1激光指示器
	int m_x, m_y;
	sf::VertexArray m_prop;//地图顶点数组（动态）
	sf::Texture m_tileset;//地图纹理
};
