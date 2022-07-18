// CDialgFight.cpp: 实现文件
//

#include "pch.h"
#include "chengyuCaiCai.h"
#include "CDialgFight.h"
#include "afxdialogex.h"
#include"TabSheet.h"
#include"DialgOPfight.h"
#include<mmsystem.h>
#pragma comment(lib, "Winmm.lib")

// CDialgFight 对话框

IMPLEMENT_DYNAMIC(CDialgFight, CDialogEx)

CDialgFight::CDialgFight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGFIGHT, pParent)
{

}

CDialgFight::~CDialgFight()
{
}

void CDialgFight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ShowQuestion, showQuestion);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_PROGRESS1, HeroHealth);
	DDX_Control(pDX, IDC_PROGRESS2, BossHealth);
	DDX_Control(pDX, IDC_TxtRight, TxtRight);
	DDX_Control(pDX, IDC_TxtWrong, TxtWrong);
}


BEGIN_MESSAGE_MAP(CDialgFight, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialgFight::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_TxtWrong, &CDialgFight::OnStnClickedTxtwrong)
	ON_STN_CLICKED(IDC_TxtRight, &CDialgFight::OnStnClickedTxtright)
END_MESSAGE_MAP()


// CDialgFight 消息处理程序


void CDialgFight::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CRect rect;
	GetClientRect(&rect);
	CDC memDC;
	CBitmap bitmapTmp, * pOldBitmap;
	//创建内存DC
	memDC.CreateCompatibleDC(&dc);
	//创建内存位图bitmap
	bitmapTmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	//将内存位图转入内存DC中，这样才能在内存DC上画图
	pOldBitmap = memDC.SelectObject(&bitmapTmp);

	DrawBgFight(&memDC);
	DrawFightBoss(&memDC);
	DrawFightHero(&memDC);

	if (!IfOnlnit)
	{
		//根据难度决定该播放哪种攻击动画
	 
		if (ThisTurnRight)
		{
	       m_anime.PlayAnime_lighting(&memDC);
		   if (m_anime.frame_tmp > m_anime.frame_lighting)
		   {
					m_anime.frame_tmp = -1;
					ThisTurnRight = false;
					KillTimer(2);
		    }
			 
		}
		else
		{
			switch (DifficultMode)
			{
			case 1:
			{

				m_anime.PlayAnime_plant(&memDC);
				if (m_anime.frame_tmp > m_anime.frame_plant)
				{
					m_anime.frame_tmp = -1;
					KillTimer(2);
				}
				break;
			}
			case 2:
			{
				m_anime.PlayAnime_water(&memDC);
				if (m_anime.frame_tmp > m_anime.frame_water)
				{
					m_anime.frame_tmp = -1;
					KillTimer(2);
				}
				break;
			}
			case 3:
			{
				m_anime.PlayAnime_fire(&memDC);
				if (m_anime.frame_tmp > m_anime.frame_fire)
				{
					m_anime.frame_tmp = -1;
					KillTimer(2);
				}
				break;
			}
			default:
				break;
			}
		}
	}
	IfOnlnit = false;

	//画内存DC
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

}


void CDialgFight::DrawBgFight(CDC* pDC)
{
	// TODO: 在此处添加实现代码.

	CBitmap bmp;
	CDC memDC;
	BITMAP bmpinfo;
    bmp.LoadBitmap(IDB_bgFight);
	bmp.GetBitmap(&bmpinfo);
	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);

	//draw
	pDC->BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(old);
	bmp.DeleteObject();

}


void CDialgFight::DrawFightBoss(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp;
	CDC memDC;
	BITMAP bmpinfo;
	if(DifficultMode==1)
	  bmp.LoadBitmap(IDB_miaomiaohua);
	else if (DifficultMode==2)
	{
		bmp.LoadBitmap(IDB_shuijiangui2);
	}
	else
	{
		bmp.LoadBitmap(IDB_penhuolong);
	}
	bmp.GetBitmap(&bmpinfo);
	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);
	//draw
	pDC->TransparentBlt(500,100,bmpinfo.bmWidth*1.5,bmpinfo.bmHeight*1.5, &memDC,
		0, 0, bmpinfo.bmWidth,bmpinfo.bmHeight, RGB(255, 255, 255));
	memDC.SelectObject(old);
	bmp.DeleteObject();

}


void CDialgFight::DrawFightHero(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CBitmap bmp;
	CDC memDC;
	BITMAP bmpinfo;
	bmp.LoadBitmap(IDB_pikaqiuFight);
	bmp.GetBitmap(&bmpinfo);
	memDC.CreateCompatibleDC(pDC);
	CBitmap* old = memDC.SelectObject(&bmp);
	//draw
	pDC->TransparentBlt(80, 300, bmpinfo.bmWidth*2, bmpinfo.bmHeight*2, &memDC,
		0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
	memDC.SelectObject(old);
	bmp.DeleteObject();
}


BOOL CDialgFight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
   // showQuestion.SubclassDlgItem(IDC_ShowQuestion, this);
	//播放战斗背景音乐
	mciSendString(TEXT("open res\\FightBgMusic.mp3 alias FightBgMusic"), NULL, 0, NULL);
	mciSendString(TEXT("play FightBgMusic repeat"), NULL, 0, NULL);

	//设置字体样式
	Question_font.CreatePointFont(170,TEXT("楷体"));
	showQuestion.SetFont(&Question_font);

	//设置idiom对象相关变量
	m_Idiom.difficultyMode = DifficultMode;
	m_Idiom.LoadIdiomFromTxt();
	 
	 
	 
	//设置标签页控件
	m_tab.AddPage(TEXT("战斗"),&OPfight, IDD_OPfight);
	m_tab.AddPage(TEXT("道具"), &OPprop, IDD_OPprop);
	m_tab.Show();
	//设置输入区中的编辑框数量
	SetOPfightEdit();
	//初始化道具对话框中的背景内容变量
	OPprop.packContentProp = packContentFight;

	//初始化时,先产生一个随机数，再根据随机数选择产生一个成语问题
	m_Idiom.SetRandIndex();
	m_Idiom.SpawnOneQuestion();
	//显示成语问题
	SetQuestionIdiom();
	//设置血量
	HeroHealth.SetRange(0, 100);
	BossHealth.SetRange(0, BossMaxHealth);
	HeroHealth.SetPos(100);
	BossHealth.SetPos(200);
    
	//加载动画资源
	m_anime.LoadAnimePicture();

	//设置定时器
	SetTimer(1, 100, NULL);
 
	//美化对话框样式
	//SetClientStyle();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialgFight::SetQuestionIdiom()
{
	// TODO: 在此处添加实现代码.
	//showQuestion.SetWindowText(TEXT(m_Idiom.AllIdiom[m_Idiom.RandIndex]).c_str());
	showQuestion.SetWindowText((m_Idiom.tmpAbout.Question).c_str());

}


void CDialgFight::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_Idiom.SetRandIndex())
	{
		//MessageBox(TEXT("挑战成功"));
		//exit(0);
	}
	else
	{
		m_Idiom.tmpAbout.LossIndex.clear();
		m_Idiom.SpawnOneQuestion();
		SetQuestionIdiom();
	}
		 
}


bool CDialgFight::CheckAnswerIn()
{
	// TODO: 在此处添加实现代码.
	m_Idiom.CheckAnswer(OPfight.answerIn);
	return true;
}


void CDialgFight::OnTimer(UINT_PTR nIDEvent)
{   
	//两个计时器，1用于控制战斗逻辑 2用于播放攻击动画
	switch (nIDEvent)
	{
	case 1:
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

		//如果使用了道具，触发相应道具的效果
		if (OPprop.UsedPropIndex != 0)
		{
			packContentFight = OPprop.packContentProp;

			switch (OPprop.UsedPropIndex)
			{
			case 1:
				PropDrugEffect();
				break;
			case 2:
				PropSilkEffect();
				break;
			default:
				break;
			}
			OPprop.UsedPropIndex = 0;

		}
		//如何玩家点击了输入区域中的确定按钮，则提交答案，本回合结束。
		//程序判断回答对错，播放相应攻击音效和动画，减少某一方的血量，将本次题目存入答题历史中，生成下一个题目。如果血量<0，生成结算窗口
		if (OPfight.IsClicked)
		{
			//进入下一回合
			OPprop.ThisTurnUsed = false;
			//这句代码一定要放在if/else前面，否则不会被执行，WHY？
			OPfight.IsClicked = false;
			bool ThisIf = m_Idiom.CheckAllAnswer(OPfight.AllanserIn);
			ThisTurnRight = ThisIf;
			//清空向量，为下次存储做准备
			OPfight.AllanserIn.clear();
			//如果回答正确
			if (ThisIf)
			{				 
				//播放攻击音效
				PlaySound((LPCSTR)(IDR_HeroAt), AfxGetResourceHandle(),
					SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);

				//激活动画播放的计时器
				SetTimer(2, 100, NULL);
				//清空向量，为下次存储做准备
				OPfight.AllanserIn.clear();
				//m_Idiom.CheckAnswer(OPfight.answerIn)
				MessageBox(TEXT("正确"));
				//将本次答题存入答题历史记录中
				SetAnserHistory(true);
				//设置正确数
				RightNum += 1;

				SetTxtRight();
				//设置血量
				now_BossHealth -= 20;
				BossHealth.SetPos(now_BossHealth);
				//如果BOSS角色归零，战斗结束，生成结算窗口
				if (now_BossHealth <= 0)
				{
					now_BossHealth = 0;
					BossHealth.SetPos(now_BossHealth);
					IfSucceed = true;
					FightEndDialg.EndRightNum = RightNum;
					FightEndDialg.EndWrongNum = WrongNum;
					//关闭音乐
					mciSendString("close FightBgMusic", NULL, 0, NULL);
					ShowEndDialg();
				}
				nextQuestion();
			}
			else
			{
				//播放攻击音效
				PlaySound((LPCSTR)(IDR_Boss1At1), AfxGetResourceHandle(),
					SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);

				//激活BOSS攻击动画的计时器
				SetTimer(2, 100, NULL);

				string txtWrong = "错误\n答案是:";
				string txtAnswer = m_Idiom.tmpAbout.Source;
				txtWrong = txtWrong + txtAnswer;
				MessageBox(TEXT(txtWrong.c_str()));
				//将本次答题存入答题历史记录中
				SetAnserHistory(false);

				//设置错误数
				WrongNum += 1;
				SetTxtWrong();
				//设置血量

				now_HeroHealth -= 20;
				HeroHealth.SetPos(now_HeroHealth);
				if (now_HeroHealth <= 0)
				{
					now_HeroHealth = 0;
					HeroHealth.SetPos(now_HeroHealth);
					IfSucceed = false;
					FightEndDialg.EndRightNum = RightNum;
					FightEndDialg.EndWrongNum = WrongNum;
					//关闭音乐
					mciSendString("close FightBgMusic", NULL, 0, NULL);
					ShowEndDialg();
				}

				nextQuestion();
			}

		}
		break;
	}
	case 2:
	{
		//一定要放在最前面，否则无法执行，和之前有个放在ifelse之后就无法执行的语句类似
		Invalidate(false);		 
	}
	case 3:
	{
		Invalidate(false);
	}
	}
	//CDialogEx::OnTimer(nIDEvent);
}


void CDialgFight::nextQuestion()
{
	// TODO: 在此处添加实现代码.
	if (!m_Idiom.SetRandIndex())
	{
		//MessageBox(TEXT("挑战成功"));
		//exit(0);
	}
	else
	{
		m_Idiom.tmpAbout.LossIndex.clear();
		m_Idiom.SpawnOneQuestion();
		SetQuestionIdiom();
	}
}


void CDialgFight::ShowEndDialg()
{
	// TODO: 在此处添加实现代码.
	DialgFightEnd end;
	if (IfSucceed)
	{
		//FightEndDialg.ResultTxt.SetWindowTextA(TEXT("挑战成功"));
	    FightEndDialg.IfSuccess = true;
	}
	else
	{
		//end.ResultTxt.SetWindowTextA(TEXT("挑战失败"));
		FightEndDialg.IfSuccess = false;
	}
 
	FightEndDialg.DoModal();
	packContentFight.find("coin")->second += FightEndDialg.GetCoinNum;
	FightEndDialg.GetCoinNum = 0;
	OnOK();
	 
    
}


void CDialgFight::SetAnserHistory(bool IfRight)
{
	// TODO: 在此处添加实现代码.
	AnswerHistory tmp;
	tmp.source = m_Idiom.tmpAbout.Source;
	if (IfRight)
		tmp.IfRight = true;
	else
	{
		tmp.IfRight = false;
	}
	FightEndDialg.History.push_back(tmp);
}
//美化对话框样式
void CDialgFight::SetClientStyle()
{
	// TODO: 在此处添加实现代码.
	CRgn rgnTmp;
	RECT rc;
	GetClientRect(&rc);
	rgnTmp.CreateRoundRectRgn(rc.left + 3, rc.top + 3, rc.right - rc.left - 3, rc.bottom - rc.top - 3, 6, 6);
	SetWindowRgn(rgnTmp, TRUE);
}


void CDialgFight::OnStnClickedTxtwrong()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialgFight::OnStnClickedTxtright()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialgFight::SetTxtRight()
{
	// TODO: 在此处添加实现代码.
	string txt = "正确: ";
	string num = to_string(RightNum);
	txt = txt + num;
	TxtRight.SetWindowTextA(TEXT(txt.c_str()));
}


void CDialgFight::SetTxtWrong()
{
	// TODO: 在此处添加实现代码.
	string txt = "错误: ";
	string num = to_string(WrongNum);
	txt = txt + num;
	TxtWrong.SetWindowTextA(TEXT(txt.c_str()));
}


void CDialgFight::SetOPfightEdit()
{
	// TODO: 在此处添加实现代码.
	OPfight.EditNum = DifficultMode;
	switch (DifficultMode)
	{
	case 1: 
		OPfight.answerEdit2.ShowWindow(FALSE);
		OPfight.answerEdit3.ShowWindow(FALSE);
		break;
	case 2:
		OPfight.answerEdit3.ShowWindow(FALSE);
		break;
	default:
		break;
	}
}


void CDialgFight::PropDrugEffect()
{
	// TODO: 在此处添加实现代码.
	KillTimer(1);
	now_HeroHealth += 50;
	if (now_HeroHealth >= 100)
	{
		now_HeroHealth = 100;
	}
	HeroHealth.SetPos(now_HeroHealth);
	MessageBox("使用回复药\n生命值+50");
	SetTimer(1, 100, NULL);
}


void CDialgFight::PropSilkEffect()
{
	// TODO: 在此处添加实现代码.
	KillTimer(1);
	string txt = "使用精灵球\n悄悄告诉你答案:";
	string txtAnswer = m_Idiom.tmpAbout.Source;
	txt = txt + txtAnswer;
	MessageBox(TEXT(txt.c_str()));
	SetTimer(1, 100, NULL);

}
