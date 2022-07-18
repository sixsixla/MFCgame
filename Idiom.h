#pragma once
#include <atltypes.h>
#include <afxwin.h>
#include<vector>
#include<string>
using namespace std;
//一个结构体，存原成语，问题成语，扣去的字数，扣去的位置
typedef struct QuestionIdiomAbout {
	string Source;
	string Question;
	int LossNum;
	vector<int> LossIndex;//每个扣去的字从左到右，在原成语string中的下标位置
} QuestionIdiomAbout;
class Idiom
{
public:
	//用向量存所有的原始成语
	vector<string> AllIdiom;
	int RandIndex = 0;
	//存已经用过的随机数，避免重复选择成语
	vector<int> RandIndexList;
 
	int IdiomNum=40;
	//难度模式,1表示扣去一个字，2表示扣去2个，3表示3个
	int difficultyMode = 1;
	//一个结构体向量
	vector<QuestionIdiomAbout> AllQuestionAbout;
    //一个结构体
	QuestionIdiomAbout tmpAbout;
	//回答正确的成语
	vector<string> RightResult;
	//回答错误的成语
	vector<string> WrongResult;
	//从txt文件中导入成语
	void LoadIdiomFromTxt();
	//生成一个随机数，用以选择对应下标的成语作为本次的题目，同时该随机数不能是之前已经用过的
	bool SetRandIndex();
	//产生一个题目，从选出的原成语中，按难度随机扣去相应的字数，例如普通难度，扣去两个字，用“__”代替。
	void SpawnOneQuestion();
	bool CheckAnswer(CString as1);
	//核对回答是否正确
	bool CheckAllAnswer(vector<CString> AllAnswer);
};

