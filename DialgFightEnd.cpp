// DialgFightEnd.cpp: 实现文件
//

#include "pch.h"
#include "chengyuCaiCai.h"
#include "DialgFightEnd.h"
#include "afxdialogex.h"
#include"CDialgFight.h"


// DialgFightEnd 对话框

IMPLEMENT_DYNAMIC(DialgFightEnd, CDialogEx)

DialgFightEnd::DialgFightEnd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FightEnd, pParent)
{

}

DialgFightEnd::~DialgFightEnd()
{
}

void DialgFightEnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EndResultTxt, ResultTxt);
	DDX_Control(pDX, IDC_LIST1, HistoryList);
	DDX_Control(pDX, IDC_TxtRight, TxtRight);
	DDX_Control(pDX, IDC_TxtWrong, TxtWrong);
	DDX_Control(pDX, IDC_GetCoinTxt, GetCoinTxt);
}


BEGIN_MESSAGE_MAP(DialgFightEnd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DialgFightEnd::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// DialgFightEnd 消息处理程序


BOOL DialgFightEnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	setResultTxt();

	//设置列表控件
	CRect rc;
	CWnd* pWnd = GetDlgItem(IDC_LIST1);//IDC_picture为picture控件ID
	pWnd->GetClientRect(&rc);//rc为控件的大小。
	int tmpx = rc.Height();//控件高
	int tmpy = rc.Width();//控件宽
	HistoryList.SetExtendedStyle(HistoryList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CString head[] = { TEXT("成语"),TEXT("对错") };
	for (int i = 0; i < 2; i++)
	{
		HistoryList.InsertColumn(i+1, head[i], LVCFMT_CENTER,83);
	}
	for (int i = 0; i < History.size(); i++)
	{
		HistoryList.InsertItem(i, TEXT(History[i].source.c_str()));
		if (History[i].IfRight)
		{
			HistoryList.SetItemText(i,1,TEXT("√"));
		}
		else
		{
			HistoryList.SetItemText(i, 1, TEXT("×"));
		}
	}
	 //设置字体样式
	SetFontStyle();
	//设置最终正确/错误数
	SetTxtRightAndWrong();
	//显示获得的金币
	SetGetCoinTxt();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DialgFightEnd::setResultTxt()
{
	// TODO: 在此处添加实现代码.
	if (IfSuccess)
	{
		ResultTxt.SetWindowTextA(TEXT("挑战成功"));
	}
	else
	{
		ResultTxt.SetWindowTextA(TEXT("挑战失败"));
	}
}


void DialgFightEnd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

//设置背景图片
void DialgFightEnd::SetBgPicture(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp;
	CDC memDC;
	BITMAP bmpinfo;
	if(IfSuccess)
	  bmp.LoadBitmapA(IDB_EndBg1);
	else
	{
		bmp.LoadBitmapA(IDB_EndBg2);
	}
	bmp.GetBitmap(&bmpinfo);
	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);
	CRect rect;
	GetClientRect(&rect);
	//draw
	pDC->StretchBlt(0, 0,rect.Width(),rect.Height(), &memDC, 0, 0,bmpinfo.bmWidth,bmpinfo.bmHeight, SRCCOPY);
	memDC.SelectObject(old);
	bmp.DeleteObject();
 
}


void DialgFightEnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	SetBgPicture(&dc);
}


HBRUSH DialgFightEnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);		          //设置背景透明
		pDC->SetTextColor(RGB(120, 40, 179));        //设置字体为黄色
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
 
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void DialgFightEnd::SetFontStyle()
{
	// TODO: 在此处添加实现代码.
	m_font.CreatePointFont(170, ("宋体"));
	ResultTxt.SetFont(&m_font);
}


void DialgFightEnd::SetTxtRightAndWrong()
{
	// TODO: 在此处添加实现代码.
	string txt = "正确: ";
	string num = to_string(EndRightNum);
	txt = txt + num;
	TxtRight.SetWindowTextA(TEXT(txt.c_str()));

	string txt2 = "错误：";
	string num2 = to_string(EndWrongNum);
	txt2 = txt2 + num2;
	TxtWrong.SetWindowTextA(TEXT(txt2.c_str()));
}


void DialgFightEnd::SetGetCoinTxt()
{
	// TODO: 在此处添加实现代码.
	string txt = "金币  X ";
	GetCoinNum = EndRightNum * 10 + EndWrongNum * 2;
	string num = to_string(GetCoinNum);
	txt = txt + num;
	GetCoinTxt.SetWindowTextA(TEXT(txt.c_str()));
}
