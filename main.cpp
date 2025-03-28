#include "game.h"
#include <iostream>
using namespace std;

//规则说明√ 撞墙√ 随机生成地图 回放功能(延时播放)  起始位√ 交互 地图保存功能

int main()
{
	introduction();
	Ant ant;
	//该用指针用来读取每一个地图的地址
	Map *head_map=new Map;
	Map *tail_map;
	//链表的头尾结点
	if (!chooseMap(head_map,ant))
	{
		return 0;
	}
	tail_map = head_map;
	head_map->showMap();
	int goal_step = 1000;
	Sports_process(goal_step, head_map, ant); //模拟运动

	
	//test
    system("pause");
	//tail_map->showMap();//可以正常访问第一个地图

	return 0;
}