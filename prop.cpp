#include "prop.h"

Prop::Prop(int x, int y,int type)
{
	m_x = x;
	m_y = y;
	m_type = type;
}

bool Prop::loadmap(const std::filesystem::path& tileset)
{
	if (!m_tileset.loadFromFile(tileset))//读取Ant纹理
		return false;
	m_prop.setPrimitiveType(sf::PrimitiveType::Triangles);//设置顶点类型
	m_prop.resize(6);//顶点数组的大小为宽度和高度乘积的6倍，因为每个单元格由两个三角形（六个点）组成
	int x = m_x - 1;
	int y = m_y - 1;
	sf::Vertex* triangles = &m_prop[0];
	triangles[0].position = sf::Vector2f(x * map_tileSize.x + prop_tileSize.x / 2, y * map_tileSize.y + prop_tileSize.y / 2);
	triangles[1].position = sf::Vector2f((x + 1) * map_tileSize.x - prop_tileSize.x / 2, y * map_tileSize.y + prop_tileSize.y / 2);
	triangles[2].position = sf::Vector2f(x * map_tileSize.x + prop_tileSize.x / 2, (y + 1) * map_tileSize.y - prop_tileSize.y / 2);
	triangles[3].position = sf::Vector2f(x * map_tileSize.x + prop_tileSize.x / 2, (y + 1) * map_tileSize.y - prop_tileSize.y / 2);
	triangles[4].position = sf::Vector2f((x + 1) * map_tileSize.x - prop_tileSize.x / 2, y * map_tileSize.y + prop_tileSize.y / 2);
	triangles[5].position = sf::Vector2f((x + 1) * map_tileSize.x - prop_tileSize.x / 2, (y + 1) * map_tileSize.y - prop_tileSize.y / 2);

	triangles[0].texCoords = sf::Vector2f(m_type * prop_tileSize.x, 0 * prop_tileSize.y);
	triangles[1].texCoords = sf::Vector2f((m_type + 1) * prop_tileSize.x, 0 * prop_tileSize.y);
	triangles[2].texCoords = sf::Vector2f(m_type * prop_tileSize.x, (0 + 1) * prop_tileSize.y);
	triangles[3].texCoords = sf::Vector2f(m_type * prop_tileSize.x, (0 + 1) * prop_tileSize.y);
	triangles[4].texCoords = sf::Vector2f((m_type + 1) * prop_tileSize.x, 0 * prop_tileSize.y);
	triangles[5].texCoords = sf::Vector2f((m_type + 1) * prop_tileSize.x, (0 + 1) * prop_tileSize.y);

	sf::Vector2f position = sf::Vector2f((x + 0.5) * map_tileSize.x, (y + 0.5) * map_tileSize.y);
	this->setOrigin(position);
	this->setPosition(position);
	return true;
}
int Prop::getType()
{
	return m_type;
}
int Prop::getX()
{
	return m_x;
}
int Prop::getY()
{
	return m_y;
}

void Prop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_prop, states);
}

void creatRocket(std::vector<Prop>& prop_list)
{

}