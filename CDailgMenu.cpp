// CDailgMenu.cpp: 实现文件
//

#include "pch.h"
#include "chengyuCaiCai.h"
#include "CDailgMenu.h"
#include "afxdialogex.h"


// CDailgMenu 对话框

IMPLEMENT_DYNAMIC(CDailgMenu, CDialogEx)

CDailgMenu::CDailgMenu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Menu, pParent)
{

}

CDailgMenu::~CDailgMenu()
{
}

void CDailgMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Title, ShowTitle);
}


BEGIN_MESSAGE_MAP(CDailgMenu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDailgMenu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDailgMenu::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDailgMenu 消息处理程序


void CDailgMenu::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("1.控制角色，靠近敌人或商店触发战斗或进入商店\n2.战斗，用成语猜猜击败敌人,获得金币\n3.商店，使用金币购买道具，道具用于辅助战斗\n4.背包，查看已有金币和道具 ");
}


void CDailgMenu::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("作者：1061145朱忆添\n");
}


void CDailgMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	DrawMenuBg(&dc);
}


void CDailgMenu::DrawMenuBg(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp;
	CDC memDC;
	BITMAP bmpinfo;
	CRect rect;
	GetClientRect(&rect);
	bmp.LoadBitmapA(IDB_MenuBg2);
	bmp.GetBitmap(&bmpinfo);
	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);

	//draw
	pDC->StretchBlt(0, 0,rect.Width(),rect.Height(),&memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	memDC.SelectObject(old);
	bmp.DeleteObject();
}

//设置字体的样式，大小和颜色
void CDailgMenu::SetFontStyle()
{
	// TODO: 在此处添加实现代码.
		//设置字体样式
	TitleFont.CreatePointFont(170, TEXT("宋体"));
	ShowTitle.SetFont(&TitleFont);
}


BOOL CDailgMenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetFontStyle();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CDailgMenu::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);		          //设置背景透明
		pDC->SetTextColor(RGB(255, 0,0));        //设置字体为黄色
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
