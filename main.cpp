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
	int goal_step = 100;
	Sports_process(goal_step, head_map, ant); //ģ���˶�
	Show_process(goal_step,tail_map, ant);//չʾ�˶�

	//test
    system("pause");
	//tail_map->showMap();//�����������ʵ�һ����ͼ

	return 0;
}