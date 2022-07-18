#pragma once
#include <atltypes.h>
#include <afxwin.h>
#include<map>
#include <string>
using namespace std;
class Hero
{
public:
	// 人物坐标
	CPoint m_pos;
	// 人物移动速度
	int m_speed = 20;
	//背包中的物品,用map容器存储,道具名string为key，数量int为value
	map<string, int> m_backPack;
	//道具种类数
	int propNum = 2;
	//背包内物品数=道具种类+金币
	int packNum = propNum + 1;
	// 表示当前绘制时要画第几帧
	int frame = 0;
	void MoveHero();
	void DrawHero(CDC * pDC);

	// 用int表示方向，0,1,2,3分别对应下左右上
	int m_dirNum = 0;
	// 内存DC
	CDC memDC;
	//从txt文件中载入背包内容
	int LoadBackpackFromTxt();
	//将当前背包内容写入txt文件中，用于下次游戏开始时的加载，实现道具的外部存储
	void WriteBackPackToTxt();
};


 
