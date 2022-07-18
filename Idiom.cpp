#include "pch.h"
#include "Idiom.h"
#include "afxdialogex.h"
#include "resource.h"
#include <clocale>
#include<algorithm>
void Idiom::LoadIdiomFromTxt()
{
	CStdioFile file;
	CString tmp;
	file.Open(_T("res/QuestionTest3.txt"), CFile::modeRead);
 
	for (int i = 0; i < IdiomNum; i++)
	{		 
		char* pOldLocale = _strdup(setlocale(LC_CTYPE, NULL));
		setlocale(LC_CTYPE, "chs");
		char buf[9];
		//file.Read(buf,sizeof(buf));
		file.ReadString(tmp);
		setlocale(LC_CTYPE, pOldLocale);
		free(pOldLocale);
		string tmpIdiom(tmp.GetBuffer());
		tmp.ReleaseBuffer();
		AllIdiom.push_back(tmpIdiom);

	}
 
	file.Close();
}

bool Idiom::SetRandIndex()
{
	srand((unsigned)time(NULL));
	RandIndex = (rand() % (IdiomNum));
	for (int i = 0; i < RandIndexList.size(); i++)
	{
		if (RandIndexList[i] == RandIndex)
		{
			RandIndex = rand() % IdiomNum;
			i = 0;
		}
	}
	RandIndexList.push_back(RandIndex);
	if (RandIndexList.size() >= IdiomNum)
		return false;
	else
	{
		return true;
	}

}

void Idiom::SpawnOneQuestion()
{
	//QuestionIdiomAbout tmpAbout;
	tmpAbout.Source = AllIdiom[RandIndex];
	tmpAbout.Question = AllIdiom[RandIndex];
	tmpAbout.LossNum = difficultyMode;
	for (int i = 0; i < difficultyMode; i++)
	{
		int index1 = (rand() % 4);
		for (int i = 0; i < tmpAbout.LossIndex.size(); i++)
		{
			while (index1==tmpAbout.LossIndex[i])
			{
				srand((unsigned)time(NULL));
				index1 = (rand() % 4);
			}
		}
		tmpAbout.LossIndex.push_back(index1);

	}
	//对记录着扣去字的位置的向量进行排序，默认从小到大
	sort(tmpAbout.LossIndex.begin(), tmpAbout.LossIndex.end());
	//扣字，做成题目字符串
	for (int i = 0; i < tmpAbout.LossIndex.size(); i++)
	{
		int indextmp = tmpAbout.LossIndex[i];
		char blank ='_';
		tmpAbout.Question = tmpAbout.Question.replace((indextmp)*2,2, "__");
	}
}

bool Idiom::CheckAnswer(CString as1)
{
	string ans1 = as1.GetBuffer();
	int indextmp = tmpAbout.LossIndex[0];
	if (tmpAbout.Source[indextmp * 2] != ans1[0] || tmpAbout.Source[indextmp * 2 + 1] != ans1[1])
	{
		return false;
	}
	return true;
}

bool Idiom::CheckAllAnswer(vector<CString> AllAnswer)
{
	// TODO: 在此处添加实现代码.
	for (int i = AllAnswer.size()-1; i >= 0; i--)
	{
		string ans1 = AllAnswer[i].GetBuffer();
		int indextmp = tmpAbout.LossIndex[difficultyMode-i-1];
		if (tmpAbout.Source[indextmp * 2] != ans1[0] || tmpAbout.Source[indextmp * 2 + 1] != ans1[1])
		{
			return false;
		}
		 
	}
	return true;
}
