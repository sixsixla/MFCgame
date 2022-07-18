#pragma once
#include<string>
#include<vector>
#include<string>
using namespace std;
// DialgFightEnd 对话框
//定义结构体，存本次答题记录
typedef struct AnswerHistory {
	string source;
	bool IfRight;
} AnswerHistory;
class DialgFightEnd : public CDialogEx
{
	DECLARE_DYNAMIC(DialgFightEnd)

public:
	DialgFightEnd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialgFightEnd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FightEnd };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 显示结算文字
	CStatic ResultTxt;
	bool IfSuccess;
	//存答题记录的向量
	vector<AnswerHistory> History;
	virtual BOOL OnInitDialog();
	void setResultTxt();
	afx_msg void OnBnClickedButton1();
	// 显示答题记录
	 
	// 显示答题记录
	CListCtrl HistoryList;
	// 通过static控件显示背景图片
	CStatic Bg_Picture;
	void SetBgPicture(CDC* pDC);
	// 显示背景图片的控件
	CStatic BgPicture;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// 字体样式
	CFont m_font;
	void SetFontStyle();
	CStatic TxtRight;
	CStatic TxtWrong;
	// 最终正确数
	int EndRightNum = 0;
	int EndWrongNum = 0;
	void SetTxtRightAndWrong();
	// 本次战斗获得的金币数
	int GetCoinNum = 0;
	CStatic GetCoinTxt;
	void SetGetCoinTxt();
};
