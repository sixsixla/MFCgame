#pragma once
#include<map>
#include<string>
using namespace std;

// DialgOPprop 对话框

class DialgOPprop : public CDialogEx
{
	DECLARE_DYNAMIC(DialgOPprop)

public:
	DialgOPprop(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialgOPprop();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPprop };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	// 使用的道具序号，没用为0
	int UsedPropIndex = 0;
	//背包内容
	map<string, int> packContentProp;
	// 当前回合是否使用过道具
	bool ThisTurnUsed = false;
	CButton UseDrug;
	CButton UseSilkBag;
};
