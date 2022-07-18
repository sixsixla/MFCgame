#include "pch.h"
#include "Hero.h"
#include "afxdialogex.h"
#include "resource.h"



void Hero::MoveHero()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_dirNum = 1;
		m_pos.x -= m_speed;
		frame++;
		if (frame > 3)
			frame = 0;

	}	 
	else
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m_dirNum = 2;
			m_pos.x += m_speed;
			frame++;
			if (frame > 3)
				frame = 0;

		}
		else
			if (GetAsyncKeyState(VK_UP))
			{
				m_dirNum = 3;
				m_pos.y -= m_speed;
				frame++;
				if (frame > 3)
					frame = 0;

			}
			else
				if (GetAsyncKeyState(VK_DOWN))
				{
					m_dirNum = 0;
					m_pos.y += m_speed;
					frame++;
					if (frame > 3)
						frame = 0;

				}
 }
void Hero::DrawHero(CDC* pDC)
{
	
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpWalk;
	bmpWalk.LoadBitmapA(IDB_pikaqiuWalk);
	memDC.SelectObject(&bmpWalk);
	pDC->TransparentBlt(m_pos.x,m_pos.y,48,48,&memDC,
		frame * 48, m_dirNum*48,48,48, RGB(255, 255, 255));

}


int Hero::LoadBackpackFromTxt()
{
	// TODO: 在此处添加实现代码.
	CStdioFile file;
	CString tmpKey;
	CString tmpValue;
	if (file.Open(_T("res/backPack.txt"), CFile::modeRead))
	{
		//file.Open(_T("res/backPack.txt"), CFile::modeRead);
		for (int i = 0; i < packNum; i++)
		{


			file.ReadString(tmpKey);
			file.ReadString(tmpValue);
			string StmpKey(tmpKey.GetBuffer());
			tmpKey.ReleaseBuffer();
			string StmpValue(tmpValue.GetBuffer());
			tmpValue.ReleaseBuffer();
			int Value = atoi(StmpValue.c_str());
			m_backPack.insert(pair<string, int>(StmpKey, Value));

		}

		file.Close();
	}
	return 0;
}


void Hero::WriteBackPackToTxt()
{
	// TODO: 在此处添加实现代码.
	CStdioFile file;
	CString tmpKey;
	CString tmpValue;
	if (file.Open(_T("res/backPack.txt"), CFile::modeReadWrite))
	{
		//file.Open(_T("res/backPack.txt"), CFile::modeReadWrite);
		for (auto i = m_backPack.begin(); i != m_backPack.end(); i++)
		{

			tmpKey = i->first.c_str();
			tmpValue = to_string(i->second).c_str();
			file.WriteString(tmpKey + "\n");
			file.WriteString(tmpValue + "\n");
		}
		file.Close();
	}
}
