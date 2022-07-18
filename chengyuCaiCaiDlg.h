
// chengyuCaiCaiDlg.h: 头文件
//
#include"Hero.h"
#include"CDialgFight.h"
#include"DialgSore.h"
#include<cstring>
#pragma once
#define MAX_BLOCK_NUM_ROW 20
#define MAX_BLOCK_NUM_COL 30
#define BLOCK_SIZE 30


// CchengyuCaiCaiDlg 对话框
class CchengyuCaiCaiDlg : public CDialogEx
{
// 构造
public:
	CchengyuCaiCaiDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHENGYUCAICAI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void DrawMap(CDC* pDC);
	int m_map[MAX_BLOCK_NUM_ROW][MAX_BLOCK_NUM_COL];
	// 加载背景图片
	CStatic m_bg;
	 
	afx_msg void OnTimer(UINT_PTR nIDEvent);
   
	//角色对象
	Hero m_Hero;
	// Boss们的区域，角色坐标进入后触发相应战斗
	RECT Boss1Area;
	RECT Boss2Area;
	RECT Boss3Area;
	RECT StoreArea;
	//战斗窗口对象
	CDialgFight dialgFight;
	//store窗口对象
	DialgSore store;
	// 表示计时器是否工作
	bool TimerFlag = true;
	// 显示背包图标
	CStatic showPackIcon;
	//绘制背包图标
	void setPackIcon();
	afx_msg void OnStnClickedpackicon();
	afx_msg void OnLvnItemchangedpacklist(NMHDR* pNMHDR, LRESULT* pResult);
	// 显示背包内容
	CListCtrl packList;
	// 标记当前背包内容是否显示
	bool IfPackShow = false;
	//物品中文名称
	CString AllPropName[];
	//设置显示背包内容的list控件中的值
	int setPackListContent();
	//绘制角色
	void DrawRole(CDC* pDC);
	//绘制地图
	void DrawBgMap(CDC* pDC);
	//绘制敌人
	void DrawBoss(CDC* pDC);
	//绘制商店
	void DrawStore(CDC* pDC);
	//判断是否进入BOSS区域，进入了哪一个
	int IntoWhichBoosArea();
	//生成战斗窗口
	void SpawnFightDialg(int difficultMode);
	//是否进入了商店区域
	bool IntoStoreArea();
	afx_msg void OnClose();
	void SetMenuIcon();
	// 显示菜单图标的控件// 显示菜单图标的控件
//	CStatic showMenuIcon;
//	CStatic menuIcon;
	afx_msg void OnStnClickedPicture();
	afx_msg void OnStnClickedMenu();
};
