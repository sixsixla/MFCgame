#include <atltypes.h>
#include <afxwin.h>
#include<vector>
#include<deque>
#include <atlimage.h>
#pragma once
using namespace std;
class Animation
{
public:
	// 火焰动画的帧数
	int frame_fire = 10;
	int frame_water = 9;
	int frame_plant = 8;
	int frame_lighting = 8;
	//当前帧数
	int frame_tmp = -1;
	deque<CImage> AnimePicures_fire;
	deque<CImage> AnimePicures_water;
	deque<CImage> AnimePicures_plant;
	deque<CImage> AnimePicures_lighting;
	int LoadAnimePicture();
	void TransparentPNG(CImage* png);
	void PlayAnime_fire(CDC* pDC);
	void DrawDCTest(CDC* pDC);
	void PlayAnime_water(CDC* pDC);
	void PlayAnime_plant(CDC* pDC);
	void PlayAnime_lighting(CDC* pDC);
};

