#pragma once
#include <atltypes.h>
#include <afxwin.h>
#include<map>
#include <string>
using namespace std;
class Hero
{
public:
	// ��������
	CPoint m_pos;
	// �����ƶ��ٶ�
	int m_speed = 20;
	//�����е���Ʒ,��map�����洢,������stringΪkey������intΪvalue
	map<string, int> m_backPack;
	//����������
	int propNum = 2;
	//��������Ʒ��=��������+���
	int packNum = propNum + 1;
	// ��ʾ��ǰ����ʱҪ���ڼ�֡
	int frame = 0;
	void MoveHero();
	void DrawHero(CDC * pDC);

	// ��int��ʾ����0,1,2,3�ֱ��Ӧ��������
	int m_dirNum = 0;
	// �ڴ�DC
	CDC memDC;
	//��txt�ļ������뱳������
	int LoadBackpackFromTxt();
	//����ǰ��������д��txt�ļ��У������´���Ϸ��ʼʱ�ļ��أ�ʵ�ֵ��ߵ��ⲿ�洢
	void WriteBackPackToTxt();
};


 
