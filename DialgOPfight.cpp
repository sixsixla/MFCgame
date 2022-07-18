// DialgOPfight.cpp: 实现文件
//

#include "pch.h"
#include "chengyuCaiCai.h"
#include "DialgOPfight.h"
#include "afxdialogex.h"


// DialgOPfight 对话框

IMPLEMENT_DYNAMIC(DialgOPfight, CDialogEx)

DialgOPfight::DialgOPfight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPfight, pParent)
{

}

DialgOPfight::~DialgOPfight()
{
}

void DialgOPfight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, answerEdit);
	DDX_Control(pDX, IDC_EDIT2, answerEdit2);
	DDX_Control(pDX, IDC_EDIT3, answerEdit3);
}


BEGIN_MESSAGE_MAP(DialgOPfight, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DialgOPfight::OnBnClickedButton1)
END_MESSAGE_MAP()


// DialgOPfight 消息处理程序


void DialgOPfight::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (EditNum)
	{
	case 3:
		answerEdit3.GetWindowTextA(answerIn);
		AllanserIn.push_back(answerIn);
		answerEdit3.SetWindowTextA("");
	case 2:
		answerEdit2.GetWindowTextA(answerIn);
		AllanserIn.push_back(answerIn);
		answerEdit2.SetWindowTextA("");
	case 1:
		answerEdit.GetWindowTextA(answerIn);
		AllanserIn.push_back(answerIn);
		answerEdit.SetWindowTextA("");
	default:
		break;
	}
	//answerEdit.GetWindowTextA(answerIn);
	IsClicked = true;
	//answerEdit.SetWindowTextA("");

}
