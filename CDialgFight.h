#pragma once
#include"Idiom.h"
#include"DialgOPfight.h"
#include"DialgOPprop.h"
#include"DialgFightEnd.h"
#include"TabSheet.h"
#include"Animation.h"
#include<map>
#include<string>
#include<mmsystem.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
// CDialgFight 对话框

class CDialgFight : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgFight)

public:
	CDialgFight(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialgFight();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGFIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
 
	// 题目的字体样式
	CFont Question_font;
	CStatic showQuestion;
	virtual BOOL OnInitDialog();
	void SetQuestionIdiom();
	//成语类对象
	Idiom m_Idiom;
	afx_msg void OnBnClickedButton1();
	// 操作区域的标签页控件，该控件能嵌入显示其他窗口，通过页签在不同子窗口间切换
	CTabSheet m_tab;
	//页签子窗口其一，接受输入的窗口
	DialgOPfight OPfight;
	//页签子窗口其二，使用道具的窗口
	DialgOPprop OPprop;
	//结算页面对象
	DialgFightEnd FightEndDialg;
	// 角色的血量
	CProgressCtrl HeroHealth;
	// BOSS的血量
	CProgressCtrl BossHealth;
	// 该BOSS的满血量
	int BossMaxHealth = 200;
	// 当前血量
	int now_HeroHealth = 100;
	// BOSS当前血量
	int now_BossHealth = BossMaxHealth;
	// 是否挑战成功
	bool IfSucceed;
	afx_msg void OnStnClickedTxtwrong();
	afx_msg void OnStnClickedTxtright();
	// 显示正确个数
	CStatic TxtRight;
	// 显示错误个数
	CStatic TxtWrong;
	// 正确个数
	int RightNum;
	// 错误个数
	int WrongNum;
	//存背包内容
	map<string, int> packContentFight;
	//创建动画类对象
	Animation m_anime;

	//绘制背景
	void DrawBgFight(CDC* pDC);
	//绘制敌人
	void DrawFightBoss(CDC* pDC);
	//绘制角色
	void DrawFightHero(CDC* pDC);
	//核对输入的回答是否正确
	bool CheckAnswerIn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//产生下一个题目并显示
	void nextQuestion();
	void ShowEndDialg();
	//每次回答后，将本次题目打上正确或错误的标签，存入答题历史向量中
	void SetAnserHistory(bool IfRight);
	void SetClientStyle();
	void SetTxtRight();
	void SetTxtWrong();
	// 难度系数
	int DifficultMode = 1;
	//根据难度确定要显示的输入框个数，简单1个，普通2个，困难3个
	void SetOPfightEdit();
	//道具回复药的效果
	void PropDrugEffect();
	//道具精灵球的效果
	void PropSilkEffect();
	// 是否第一次启动
	bool IfOnlnit = true;
	// 本回合答案是否正确
	bool ThisTurnRight = false;
};
