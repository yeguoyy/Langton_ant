#include "prop.h"
#include "map.h"
#include <iostream>

Prop::Prop(int x, int y,int type)
{
	m_x = x;
	m_y = y;
	m_type = type;
}

bool Prop::loadmap(const std::filesystem::path& tileset)
{
	if (!m_tileset.loadFromFile(tileset))//��ȡAnt����
		return false;
	m_prop.setPrimitiveType(sf::PrimitiveType::Triangles);//���ö�������
	m_prop.resize(6);//��������Ĵ�СΪ��Ⱥ͸߶ȳ˻���6������Ϊÿ����Ԫ�������������Σ������㣩���
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


void creatProp(std::vector<Prop>& prop_list, const Map& map, int type)//�������� 0С��� 1����
{
	while (true)
	{
		int rocket_x = rand() % map.Width + 1;
		int rocket_y = rand() % map.Height + 1;
		
		int if_right = 0;
		if (map.m_map[rocket_x][rocket_y] != 2  && rocket_x != map.M_ant_x && rocket_y != map.M_ant_y)
		{
			for (int i = 0; i < prop_list.size(); i++)
			{
				if (prop_list[i].getX() == rocket_x && prop_list[i].getY() == rocket_y)
				{
					if_right = 1;
					break;
				}
			}
			if (if_right == 1)
				continue;
			//std::cout << "�µ���λ��" << rocket_x << " " << rocket_y << std::endl;
			prop_list.push_back(Prop(rocket_x, rocket_y, type));
			prop_list[prop_list.size() - 1].loadmap("tileMap/Prop.png");
			return;
		}
	}
}
