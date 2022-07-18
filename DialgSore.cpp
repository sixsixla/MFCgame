// DialgSore.cpp: 实现文件
//

#include "pch.h"
#include "chengyuCaiCai.h"
#include "DialgSore.h"
#include "afxdialogex.h"


// DialgSore 对话框

IMPLEMENT_DYNAMIC(DialgSore, CDialogEx)

DialgSore::DialgSore(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_StoreInside, pParent)
{

}

DialgSore::~DialgSore()
{
}

void DialgSore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, prop_drug);
	DDX_Control(pDX, IDC_CHECK2, Prop_spritBall);
}


BEGIN_MESSAGE_MAP(DialgSore, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BtBuy, &DialgSore::OnBnClickedBtbuy)
	ON_BN_CLICKED(IDC_BtBuy2, &DialgSore::OnBnClickedBtbuy2)
END_MESSAGE_MAP()


// DialgSore 消息处理程序


void DialgSore::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	DrawStoreBg(&dc);
}


void DialgSore::DrawStoreBg(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp;
	CDC memDC;
	BITMAP bmpinfo;
	CRect rect;
	GetClientRect(&rect);
	bmp.LoadBitmapA(IDB_storeBg);
	bmp.GetBitmap(&bmpinfo);
	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);
	pDC->StretchBlt(0, 0,rect.Width(),rect.Height(), &memDC, 0, 0,bmpinfo.bmWidth,bmpinfo.bmHeight, SRCCOPY);
	memDC.SelectObject(old);
	bmp.DeleteObject();

}


bool DialgSore::TryBuyProp()
{
	// TODO: 在此处添加实现代码.
	int TotalPrice = 0;
	if (prop_drug.GetCheck())
	{
		TotalPrice += AllPropAbout.find("drug")->second;
	}
	if (Prop_spritBall.GetCheck())
	{
		TotalPrice += AllPropAbout.find("silkBag")->second;
	}
	if (!prop_drug.GetCheck() && !Prop_spritBall.GetCheck())
	{
		MessageBox("请选择商品");
		return false;
	}
	if (TotalPrice > packContent.find("coin")->second)
	{
		MessageBox("购买失败！金币不足");
		return false;
	}
	else
	{
		packContent.find("coin")->second -= TotalPrice;
		if (prop_drug.GetCheck())
		{
			packContent.find("drug")->second+=1;
		}
			 
		if (Prop_spritBall.GetCheck())
		{
			packContent.find("silkBag")->second += 1;
		}

		MessageBox("购买成功!");
		return true;
	}
}


void DialgSore::SetAllPropAbout()
{
	// TODO: 在此处添加实现代码.
	AllPropAbout.insert(pair<string, int>("drug", 50));
	AllPropAbout.insert(pair<string, int>("silkBag", 100));
}


void DialgSore::BuyProp()
{
	// TODO: 在此处添加实现代码.
	if (TryBuyProp())
	{
		
	}
}


void DialgSore::OnBnClickedBtbuy()
{
	// TODO: 在此添加控件通知处理程序代码
	TryBuyProp();
}


BOOL DialgSore::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetAllPropAbout();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DialgSore::OnBnClickedBtbuy2()
{
	
	// TODO: 在此添加控件通知处理程序代码
	IsExit = true;
	OnOK();
}
