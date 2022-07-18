
// chengyuCaiCaiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "chengyuCaiCai.h"
#include "chengyuCaiCaiDlg.h"
#include "afxdialogex.h"
#include"Hero.h"
#include"CDialgFight.h"
#include"CDailgMenu.h"
#include<mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CchengyuCaiCaiDlg 对话框



CchengyuCaiCaiDlg::CchengyuCaiCaiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHENGYUCAICAI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchengyuCaiCaiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_packIcon, showPackIcon);
	DDX_Control(pDX, IDC_packList, packList);
	//  DDX_Control(pDX, IDC_MenuIcon, showMenuIcon);
	//  DDX_Control(pDX, IDC_MenuIcon, showMenuIcon);
	//  DDX_Control(pDX, IDC_menu, menuIcon);
}

BEGIN_MESSAGE_MAP(CchengyuCaiCaiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_packIcon, &CchengyuCaiCaiDlg::OnStnClickedpackicon)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_packList, &CchengyuCaiCaiDlg::OnLvnItemchangedpacklist)
	ON_WM_CLOSE()
	 
	ON_STN_CLICKED(IDC_Menu, &CchengyuCaiCaiDlg::OnStnClickedMenu)
END_MESSAGE_MAP()


// CchengyuCaiCaiDlg 消息处理程序

BOOL CchengyuCaiCaiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//显示图片
	setPackIcon();
    //设置背包list控件
	packList.SetExtendedStyle(packList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString head[] = { TEXT("物品"),TEXT("数量") };
	for (int i = 0; i < 2; i++)
	{
		packList.InsertColumn(i, head[i], LVCFMT_CENTER, 52);
	}
	 
	
	//播放背景音乐
	mciSendString("open res\\MainBgMusic.mp3 alias MainBgMusic", NULL, 0, NULL);
	mciSendString("play MainBgMusic repeat", NULL, 0, NULL);
    //设置角色相关信息
	m_Hero.m_pos.x=400;
	m_Hero.m_pos.y = 400;
	//导入角色的背包内容
	m_Hero.LoadBackpackFromTxt();
	
	//设置定时器
	SetTimer(1, 100, NULL);

	//开启新窗口
	//CDialgFight dialgFight;
	//dialgFight.DoModal();

 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CchengyuCaiCaiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CchengyuCaiCaiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC memDC;
		CBitmap bitmapTmp,*pOldBitmap;
		//创建内存DC
		memDC.CreateCompatibleDC(&dc);
		//创建内存位图bitmap
		bitmapTmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		//将内存位图转入内存DC中，这样才能在内存DC上画图
		pOldBitmap = memDC.SelectObject(&bitmapTmp);

		//DrawMap(&dc);
		//DrawBgMap(&dc);
		//DrawBoss(&dc);
		//DrawStore(&dc);
		DrawBgMap(&memDC);
		DrawBoss(&memDC);
		DrawStore(&memDC);
		//m_Hero.DrawHero(&dc);
		DrawRole(&memDC);
		//将内存DC画到正真的dc中
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CchengyuCaiCaiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchengyuCaiCaiDlg::DrawMap(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp;
	CDC memDC;  //内存虚拟画布，可以画，但看不到，从内存复制到屏幕才显示
	//从本地读取
	CStdioFile mapFile;
	mapFile.Open("pokemon2.txt", CFile::modeRead);
	 
    memDC.CreateCompatibleDC(pDC);  //内存dc创建和屏幕dc兼容
	for (int row = 0; row < MAX_BLOCK_NUM_ROW; row++)
	{
		for (int col = 0; col < MAX_BLOCK_NUM_COL; col++)
		{
			//int bmpID = IDB_BITMAP1;// rand() % 5 + IDB_BITMAP1;  //随机取ID1 rand:0-4
			//m_map[row][col] = bmpID;
			//infs >> m_map[row][col];
			char buff[4] = { '\0' };
			mapFile.Read(buff, 4);
			m_map[row][col] = atoi(buff);

			bmp.LoadBitmap(m_map[row][col]);
			memDC.SelectObject(&bmp);

			int x = col * BLOCK_SIZE;
			int y = row * BLOCK_SIZE;
			pDC->BitBlt(x, y, BLOCK_SIZE, BLOCK_SIZE,
				&memDC, 0, 0, SRCCOPY);

			bmp.DeleteObject();

		}
		char buffEnd[1];
		mapFile.Read(buffEnd, 1);

	}
	mapFile.Close();
	memDC.DeleteDC();

}


void CchengyuCaiCaiDlg::DrawBoss(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp,bmp2, bmp3;
	CDC memDC, memDC2, memDC3;
	BITMAP bmpinfo;
	bmp.LoadBitmapA(IDB_miaomiaohua);
	bmp.GetBitmap(&bmpinfo);

	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);
	//pDC->BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	//BOSS ONE
	pDC->TransparentBlt(750, 400, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC,
		0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
	memDC.SelectObject(old);
	bmp.DeleteObject();
 
	Boss1Area = { 750,400,750+bmpinfo.bmWidth, 400+bmpinfo.bmHeight };

	//TWO BOSS
	bmp2.LoadBitmapA(IDB_shuijiangui);
	bmp2.GetBitmap(&bmpinfo);

	memDC2.CreateCompatibleDC(pDC);
	CBitmap* old2 = memDC2.SelectObject(&bmp2);
	//pDC->BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	pDC->TransparentBlt(80, 200, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC2,
		0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
	memDC2.SelectObject(old2);
	bmp2.DeleteObject();
   
	Boss2Area = {80,200,80+bmpinfo.bmWidth, 200+bmpinfo.bmHeight };

	//Three BOSS
	bmp3.LoadBitmapA(IDB_penhuolong);
	bmp3.GetBitmap(&bmpinfo);

	memDC3.CreateCompatibleDC(pDC);
	CBitmap* old3 = memDC3.SelectObject(&bmp3);
	//pDC->BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	pDC->TransparentBlt(750, 50, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC3,
		0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
	memDC3.SelectObject(old2);
	bmp3.DeleteObject();
	 
	Boss3Area = { 750,50,750+bmpinfo.bmWidth, 50+bmpinfo.bmHeight };


}


void CchengyuCaiCaiDlg::OnTimer(UINT_PTR nIDEvent)
{    
	 
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//从商店页面中退出了，更新背包内容
	if (store.IsExit)
	{
		m_Hero.m_backPack = store.packContent;
		store.IsExit = false;
	}
	if (!TimerFlag)
		return;
	else
	{


		m_Hero.MoveHero();
		int flag = IntoWhichBoosArea();
		if (flag != 0)
		{
			SpawnFightDialg(flag);
		}
		IntoStoreArea();
	 
		//CDialgFight fight;
		//switch (flag)
		//{
		//case 1:
		//	/*dialgFight.DifficultMode = 1;
		//	dialgFight.DoModal();*/
		//	KillTimer(1);
		//	mciSendString("stop MainBgMusic", NULL, 0, NULL);
		//	//设置战斗对话框的一些变量
		//	fight.DifficultMode = 1;
		//	fight.packContentFight = m_Hero.m_backPack;
		//	fight.DoModal();
		//	
		//	mciSendString("play MainBgMusic repeat", NULL, 0, NULL);
		//	SetTimer(1, 100, NULL);
		//	break;
		//case 2:
		//	/*dialgFight.DifficultMode = 2;
		//	dialgFight.DoModal();*/
		//	KillTimer(1);
		//	mciSendString("stop MainBgMusic", NULL, 0, NULL);
		//	//设置战斗对话框的一些变量
		//	fight.DifficultMode = 2;
		//	fight.packContentFight = m_Hero.m_backPack;
		//	fight.DoModal();
		//	mciSendString("play MainBgMusic repeat", NULL, 0, NULL);
		//	SetTimer(1, 100, NULL);
		//	break;
		//case 3:
		//	/*	dialgFight.DifficultMode = 3;
		//		dialgFight.DoModal();*/
		//	KillTimer(1);
		//	mciSendString("stop MainBgMusic", NULL, 0, NULL);
		//	fight.DifficultMode = 3;
		//	fight.packContentFight = m_Hero.m_backPack;
		//	fight.DoModal();
		//	mciSendString("play MainBgMusic repeat", NULL, 0, NULL);
		//	SetTimer(1, 100, NULL);
		//	break;
		//default:
		//	break;
		//}
		Invalidate(false);
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CchengyuCaiCaiDlg::DrawRole(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpWalk;
	bmpWalk.LoadBitmapA(IDB_pikaqiuWalk);
	memDC.SelectObject(&bmpWalk);
	pDC->TransparentBlt(m_Hero.m_pos.x-48, m_Hero.m_pos.y-48, 96, 96, &memDC,
		m_Hero.frame * 48, m_Hero.m_dirNum * 48, 48, 48, RGB(255, 255, 255));
}


void CchengyuCaiCaiDlg::DrawBgMap(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp;
	CDC memDC;
	BITMAP bmpinfo;

	bmp.LoadBitmapA(IDB_bgMap);
 
	bmp.GetBitmap(&bmpinfo);
	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);
	//draw
	pDC->BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(old);
	bmp.DeleteObject();
}


int CchengyuCaiCaiDlg::IntoWhichBoosArea()
{
	// TODO: 在此处添加实现代码.
	CPoint tmp = m_Hero.m_pos;
	int DistanceBuf = 30;
	//如果进入了某个BOSS区域，返回值，根据角色朝向把角色移出区域，防止角色不动时，下次执行时再次进入
	if (PtInRect(&Boss1Area, tmp))
	{
		switch (m_Hero.m_dirNum)
		{
		case 0:
			m_Hero.m_pos.y = Boss1Area.top - DistanceBuf;
			break;
		case 1:
			m_Hero.m_pos.x = Boss1Area.right + DistanceBuf;
			break;
		case 2:
			m_Hero.m_pos.x = Boss1Area.left - DistanceBuf;
			break;
		case 3:
			m_Hero.m_pos.y = Boss1Area.bottom + DistanceBuf;
			break;
		default:
			break;
		}
		return 1;
	}
		 
	if (PtInRect(&Boss2Area, tmp))
	{
		switch (m_Hero.m_dirNum)
		{
		case 0:
			m_Hero.m_pos.y = Boss2Area.top - DistanceBuf;
			break;
		case 1:
			m_Hero.m_pos.x = Boss2Area.right + DistanceBuf;
			break;
		case 2:
			m_Hero.m_pos.x = Boss2Area.left - DistanceBuf;
			break;
		case 3:
			m_Hero.m_pos.y = Boss2Area.bottom + DistanceBuf;
			break;
		default:
			break;
		}
		return 2;
	}
		 
	if (PtInRect(&Boss3Area, tmp))
	{
		switch (m_Hero.m_dirNum)
		{
		case 0:
			m_Hero.m_pos.y = Boss3Area.top - DistanceBuf;
			break;
		case 1:
			m_Hero.m_pos.x = Boss3Area.right + DistanceBuf;
			break;
		case 2:
			m_Hero.m_pos.x = Boss3Area.left - DistanceBuf;
			break;
		case 3:
			m_Hero.m_pos.y = Boss3Area.bottom + DistanceBuf;
			break;
		default:
			break;
		}
		return 3;
	}
	//PtInRect();
	return 0;
}


void CchengyuCaiCaiDlg::setPackIcon()
{
	// TODO: 在此处添加实现代码.
	//显示图片
	showPackIcon.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	//2.通过路径获取bitmap句柄
    #define HBMP(filepath,width,height) (HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)
//3.获取控件大小
	CRect rect;
	showPackIcon.GetWindowRect(rect);
	//4.静态控件设置bitmap
	showPackIcon.SetBitmap(HBMP(TEXT("./res/packIcon2.bmp"), rect.Width(), rect.Height()));

}


void CchengyuCaiCaiDlg::OnStnClickedpackicon()
{
	// TODO: 在此添加控件通知处理程序代码
	if (packList.IsWindowVisible())
		packList.ShowWindow(SW_HIDE);
	else
	{
		setPackListContent();
		packList.ShowWindow(SW_SHOW);
	}
}


void CchengyuCaiCaiDlg::OnLvnItemchangedpacklist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

//设置背包列表控件的内容
int CchengyuCaiCaiDlg::setPackListContent()
{
	// TODO: 在此处添加实现代码.
	CString AllName[] = {TEXT("金币"), TEXT("回复药"), TEXT("精灵球") };
	//重新写入前先清空List
	packList.DeleteAllItems();
	int row = 0;
	for (auto i = m_Hero.m_backPack.begin();i!=m_Hero.m_backPack.end();i++)
	{
		//if (i->second != 0)
		{
			packList.InsertItem(row,AllName[row]);
			packList.SetItemText(row, 1, to_string(i->second).c_str());
		}
		row++;
	}
	return 0;
}


void CchengyuCaiCaiDlg::DrawStore(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp;
	CDC memDC;
	BITMAP bmpinfo;
	bmp.LoadBitmapA(IDB_store);
	bmp.GetBitmap(&bmpinfo);

	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);
	pDC->TransparentBlt(420, 200, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC,
		0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
	StoreArea = { 420,200,420 + bmpinfo.bmWidth,200 + bmpinfo.bmHeight };
	memDC.SelectObject(old);
	bmp.DeleteObject();
}


void CchengyuCaiCaiDlg::SpawnFightDialg(int difficultMode)
{
	// TODO: 在此处添加实现代码.
	CDialgFight fight;
 
		KillTimer(1);
		mciSendString("stop MainBgMusic", NULL, 0, NULL);
		//设置战斗对话框的一些变量
		fight.DifficultMode = difficultMode;
		fight.packContentFight = m_Hero.m_backPack;
		fight.DoModal();
		m_Hero.m_backPack = fight.packContentFight;
		mciSendString("play MainBgMusic repeat", NULL, 0, NULL);
		SetTimer(1, 100, NULL);
 
}


bool CchengyuCaiCaiDlg::IntoStoreArea()
{
	// TODO: 在此处添加实现代码.
	//如果进入商店区域
	int DistanceBuf = 30;

	if (PtInRect(&StoreArea, m_Hero.m_pos))
	{
		switch (m_Hero.m_dirNum)
		{
		case 0:
			m_Hero.m_pos.y = StoreArea.top - DistanceBuf;
			break;
		case 1:
			m_Hero.m_pos.x = StoreArea.right + DistanceBuf;
			break;
		case 2:
			m_Hero.m_pos.x = StoreArea.left - DistanceBuf;
			break;
		case 3:
			m_Hero.m_pos.y = StoreArea.bottom + DistanceBuf;
			break;
		default:
			break;
		}
		KillTimer(1);
		//设置sotre对象中的背包内容
		store.packContent = m_Hero.m_backPack;
		store.DoModal();
		SetTimer(1,100,NULL);
		return true;	
	}
	return false;
}


void CchengyuCaiCaiDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//将背包内容写入本地txt文件中
	m_Hero.WriteBackPackToTxt();
	CDialogEx::OnClose();
}

//
void CchengyuCaiCaiDlg::SetMenuIcon()
{
//	// TODO: 在此处添加实现代码.
//		//显示图片
//	CStatic menuIcon;
//	menuIcon.GetDlgItem(IDC_menu); 
//	menuIcon.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
//	//2.通过路径获取bitmap句柄
//#define HBMP(filepath,width,height) (HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)
////3.获取控件大小
//	CRect rect;
//	menuIcon.GetWindowRect(rect);
//	//4.静态控件设置bitmap
//	menuIcon.SetBitmap(HBMP(TEXT("./res/MenuIcon.bmp"), rect.Width(), rect.Height()));
}


 


void CchengyuCaiCaiDlg::OnStnClickedMenu()
{
	// TODO: 在此添加控件通知处理程序代码
	CDailgMenu menu;
	menu.DoModal();
}
