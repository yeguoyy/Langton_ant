#pragma once
#define Width 10
#define Height 10

class Map
{
public:
	int m_map[Width][Height];
	void creatMap();
    void showMap();
};