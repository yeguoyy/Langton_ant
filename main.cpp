#include "game.h"
#include <iostream>
using namespace std;

//����˵���� ײǽ�� ������ɵ�ͼ �طŹ���(��ʱ����)  ��ʼλ�� ���� ��ͼ���湦�� ������� �����ţ��ϰ��
//��ս����ͨ���ı�ڰף�����С�Ĳ��������ϵ�Ŀ������

int main()
{
	introduction();
	Ant ant;
	//����ָ��������ȡÿһ����ͼ�ĵ�ַ
	Map *head_map=new Map;
	Map *tail_map=new Map;
	//�����ͷβ���
	if (!chooseMap(head_map,ant))
	{
		return 0;
	}
	tail_map = head_map;
	head_map->showMap();
	int goal_step = 3;
	Sports_process(goal_step, head_map, ant); //ģ���˶�
	std::cout << "head_map address: " << head_map << std::endl;
	std::cout << "tail_map address: " << tail_map << std::endl;

	
	//test
    system("pause");
	tail_map->showMap();//�������������ʵ�һ����ͼ
	system("pause");

	return 0;
}