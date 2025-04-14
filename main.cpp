#include "game.h"
#include <iostream>
using namespace std;

//规则说明√ 撞墙√ 随机生成地图 回放功能(延时播放)√  起始位√ 交互√ 地图保存功能 误输入√ 传送门？障碍物？
//挑战赛（通过改变黑白，以最小的步数让蚂蚁到目标区域）

int main()
{
	introduction();
	Ant ant;
	//该用指针用来读取每一个地图的地址
	Map *head_map=new Map;
	Map *tail_map=new Map;
	//链表的头尾结点
	if (!chooseMap(head_map,ant))
	{
		return 0;
	}
	tail_map = head_map;
	int goal_step = 100;
	Sports_process(goal_step, head_map, ant); //模拟运动
	Map player_map(*head_map);
	player_try(player_map,tail_map);
	Show_process(goal_step,tail_map, ant);//展示运动
	//test
    system("pause");
	//tail_map->showMap();//可以正常访问第一个地图
	return 0;
}