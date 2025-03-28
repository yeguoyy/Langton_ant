#include "game.h"
#include <iostream>
using namespace std;

void introduction()
{
	cout << "欢迎来到兰顿蚂蚁游戏" << endl;
	cout << "兰顿蚂蚁由黑（#）白（O）格子和一只蚂蚁构成，蚂蚁可在平面正方格上移动。" << endl
		<< "若在白格，则右转90度，将该格改为黑格，并向前移动一步；" << endl
		<< "若在黑格，则左转90度，将该格该为白格，并向前移动一步；" << endl
		<< "若撞墙，则原地不动，自转180度调头但不改变脚下颜色。" << endl;
	cout << "玩家需要根据蚂蚁的最终蚁行图倒推初始图" << endl;
}