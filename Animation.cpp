#include "pch.h"
#include "Animation.h"
#include<string>
#include<cstring>

int Animation::LoadAnimePicture()
{
    // TODO: 在此处添加实现代码.
    //导入火焰动画的所有图片
    CString path = "res/Anime/";
    for (int i = 0; i <frame_fire; i++)
    {
        CImage img;
        AnimePicures_fire.push_back(img);
        CString name = "fireAnime/";
        name = path + name;
        name = name+(to_string(i).c_str());
        CString type = ".png";
        name = name + type;
        AnimePicures_fire[i].Load(name);
        TransparentPNG(&AnimePicures_fire[i]);
        
    }
    for (int i = 0; i < frame_water; i++)
    {
        CImage img;
        AnimePicures_water.push_back(img);
        CString name = "waterAnime/";
        name = path + name;
        name = name+(to_string(i).c_str());
        CString type = ".png";
        name = name + type;
        AnimePicures_water[i].Load(name);
        TransparentPNG(&AnimePicures_water[i]);
    }
    for (int i = 0; i < frame_plant; i++)
    {
        CImage img;
        AnimePicures_plant.push_back(img);
        CString name = "plantAnime/";
        name = path + name;
        name = name + (to_string(i).c_str());
        CString type = ".png";
        name = name + type;
        AnimePicures_plant[i].Load(name);
        TransparentPNG(&AnimePicures_plant[i]);
    }
    for (int i = 0; i < frame_lighting; i++)
    {
        CImage img;
        AnimePicures_lighting.push_back(img);
        CString name = "lightingAnime/";
        name = path + name;
        name = name + (to_string(i).c_str());
        CString type = ".png";
        name = name + type;
        AnimePicures_lighting[i].Load(name);
        TransparentPNG(&AnimePicures_lighting[i]);
    }
    return 0;
}

void Animation::TransparentPNG(CImage* png)
{
    for (int i = 0; i < png->GetWidth(); i++)
    {
        for (int j = 0; j < png->GetHeight(); j++)
        {
            unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i, j));
            pucColor[0] = pucColor[0] * pucColor[3] / 255;
            pucColor[1] = pucColor[1] * pucColor[3] / 255;
            pucColor[2] = pucColor[2] * pucColor[3] / 255;
        }
    }
}
 
 

//播放火焰动画，根据帧数绘制指定图片
void Animation::PlayAnime_fire(CDC* pDC)
{
    // TODO: 在此处添加实现代码.
    if (frame_tmp >= frame_fire)
    {
        frame_tmp++;
        return;
    }
    if (frame_tmp == -1)
    {
        frame_tmp = 0;
    }
    AnimePicures_fire[frame_tmp].SetTransparentColor(RGB(0,0,0));
    AnimePicures_fire[frame_tmp].Draw(*pDC, 60, 220, 256, 256);
    frame_tmp++;
}


void Animation::DrawDCTest(CDC* pDC)
{
    // TODO: 在此处添加实现代码.
    if (frame_tmp >= frame_fire)
    {
        frame_tmp = -1;
        return;
    }
    if (frame_tmp == -1)
    {
        frame_tmp = 0;
    }	
    CImage tmp;
    tmp.Load("res/Anime/fireAnime/1.png");
    //tmp.Draw(*(pDC), 100, 100, 128, 128);
    AnimePicures_fire[frame_tmp].Draw(*(pDC), 60, 220, 256, 256);
}


void Animation::PlayAnime_water(CDC* pDC)
{
    // TODO: 在此处添加实现代码.
        // TODO: 在此处添加实现代码.
    if (frame_tmp >= frame_water)
    {
        frame_tmp++;
        return;
    }
    if (frame_tmp == -1)
    {
        frame_tmp = 0;
    }
    AnimePicures_water[frame_tmp].SetTransparentColor(RGB(0, 0, 0));
    AnimePicures_water[frame_tmp].Draw(*pDC, 60, 220, 256, 256);
    frame_tmp++;
}


void Animation::PlayAnime_plant(CDC* pDC)
{
    // TODO: 在此处添加实现代码.
        // TODO: 在此处添加实现代码.
    if (frame_tmp >= frame_plant)
    {
        frame_tmp++;
        return;
    }
    if (frame_tmp == -1)
    {
        frame_tmp = 0;
    }
    AnimePicures_plant[frame_tmp].SetTransparentColor(RGB(0, 0, 0));
    AnimePicures_plant[frame_tmp].Draw(*pDC, 80, 220, 228, 228);
    frame_tmp++;
}


void Animation::PlayAnime_lighting(CDC* pDC)
{
    // TODO: 在此处添加实现代码.
        // TODO: 在此处添加实现代码.
    if (frame_tmp >= frame_lighting)
    {
        frame_tmp++;
        return;
    }
    if (frame_tmp == -1)
    {
        frame_tmp = 0;
    }
    AnimePicures_lighting[frame_tmp] .SetTransparentColor(RGB(0, 0, 0));
    AnimePicures_lighting[frame_tmp].Draw(*pDC, 440, 60, 200, 256);
    frame_tmp++;
}
