#pragma once

class Map
{
public:
	int** m_map;//��ͼ���� 0��8�� 1��2��3��4��
	int Width;
    int Height;
	int Ant_color;//���Ͻ�����ɫ�����ڸ�����һ����ͼ
	
    void showMap();
	Map* nextMap;
    Map();
    ~Map();
};

bool chooseMap(Map*&);
//void creatMap(Map&);

