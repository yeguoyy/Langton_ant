#ifndef MAP_H
#define MAP_H
//#include "ant.h"

class Map
{
public:
	int** m_map;//地图数组 0白8黑 1↑2↓3←4→
	int Width;
    int Height;
	int Ant_color;//蚂蚁脚下颜色，用于赋给下一个地图
	
    void showMap();
	Map* nextMap;
    Map();
    ~Map();
};

void creatMap(Map*&);

#endif