#pragma once
#include<vector>
#include<string>
using namespace std;

// DialgOPfight 对话框

class DialgOPfight : public CDialogEx
{
	DECLARE_DYNAMIC(DialgOPfight)

public:
	DialgOPfight(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialgOPfight();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPfight };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// 用户输入的回答
	CString answerIn;
	//存用户输入答案的向量
	vector<CString> AllanserIn;
	// 接收答案的输入框
	CEdit answerEdit;
	// 确定按钮是否被点击
	bool IsClicked;
	CEdit answerEdit2;
	CEdit answerEdit3;
	// 可用的编辑框数量
	int EditNum = 1;
};
