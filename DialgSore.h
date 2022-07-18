#pragma once
#include<map>
#include<string>
using namespace std;

// DialgSore 对话框

class DialgSore : public CDialogEx
{
	DECLARE_DYNAMIC(DialgSore)

public:
	DialgSore(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialgSore();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_StoreInside };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	//存背包物品
	map<string,int>  packContent;
	//存所有商品和价格
	map<string, int> AllPropAbout;
	void DrawStoreBg(CDC* pDC);
	// 道具_回复药
	CButton prop_drug;
	// 精灵球道具
	CButton Prop_spritBall;
	//尝试购买道具，判断玩家拥有的金币是否足够，返回购买是否成功。
	bool TryBuyProp();
	//设置要显示的道具名称和价格
	void SetAllPropAbout();
	void BuyProp();
	afx_msg void OnBnClickedBtbuy();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtbuy2();
	// 是否点击了离开按钮，主窗口通过该变量来得知应该更新数据了
	bool IsExit = false;
};
