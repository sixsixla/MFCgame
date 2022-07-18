#pragma once


// CDailgMenu 对话框

class CDailgMenu : public CDialogEx
{
	DECLARE_DYNAMIC(CDailgMenu)

public:
	CDailgMenu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDailgMenu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Menu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnPaint();
	void DrawMenuBg(CDC* pDC);
	// 标题的字体样式
	CFont TitleFont;
	void SetFontStyle();
	// 标题控件
	CStatic ShowTitle;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
