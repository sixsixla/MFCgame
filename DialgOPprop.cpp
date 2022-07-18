// DialgOPprop.cpp: 实现文件
//

#include "pch.h"
#include "chengyuCaiCai.h"
#include "DialgOPprop.h"
#include "afxdialogex.h"


// DialgOPprop 对话框

IMPLEMENT_DYNAMIC(DialgOPprop, CDialogEx)

DialgOPprop::DialgOPprop(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPprop, pParent)
{

}

DialgOPprop::~DialgOPprop()
{
}

void DialgOPprop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UseDrug, UseDrug);
	DDX_Control(pDX, IDC_UseSilkBag, UseSilkBag);
}


BEGIN_MESSAGE_MAP(DialgOPprop, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &DialgOPprop::OnBnClickedButton2)
END_MESSAGE_MAP()


// DialgOPprop 消息处理程序


void DialgOPprop::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = GetCheckedRadioButton(IDC_UseDrug, IDC_UseSilkBag);
	UseDrug.SetCheck(0);
	UseSilkBag.SetCheck(0);
	if (i == 0)
		return;
	if (ThisTurnUsed)
	{
		MessageBox("一回合只能用一次哦！");
		return;
	}
	if (i == IDC_UseDrug)
	{
		if (packContentProp.find("drug")->second >= 1)
		{
			packContentProp.find("drug")->second -= 1;
			UsedPropIndex = 1;
			ThisTurnUsed = true;
		}
		else
		{
			MessageBox("使用失败！数量不足");
		}
		 
	}
		 
	if (i == IDC_UseSilkBag)
	{
		if (packContentProp.find("silkBag")->second >= 1)
		{
			packContentProp.find("silkBag")->second -= 1;
			UsedPropIndex = 2;
			ThisTurnUsed = true;
		}
		else
		{
			MessageBox("使用失败！数量不足");
		}
	 
	}
	 

}
