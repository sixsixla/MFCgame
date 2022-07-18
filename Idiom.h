#pragma once
#include <atltypes.h>
#include <afxwin.h>
#include<vector>
#include<string>
using namespace std;
//һ���ṹ�壬��ԭ�����������ȥ����������ȥ��λ��
typedef struct QuestionIdiomAbout {
	string Source;
	string Question;
	int LossNum;
	vector<int> LossIndex;//ÿ����ȥ���ִ����ң���ԭ����string�е��±�λ��
} QuestionIdiomAbout;
class Idiom
{
public:
	//�����������е�ԭʼ����
	vector<string> AllIdiom;
	int RandIndex = 0;
	//���Ѿ��ù���������������ظ�ѡ�����
	vector<int> RandIndexList;
 
	int IdiomNum=40;
	//�Ѷ�ģʽ,1��ʾ��ȥһ���֣�2��ʾ��ȥ2����3��ʾ3��
	int difficultyMode = 1;
	//һ���ṹ������
	vector<QuestionIdiomAbout> AllQuestionAbout;
    //һ���ṹ��
	QuestionIdiomAbout tmpAbout;
	//�ش���ȷ�ĳ���
	vector<string> RightResult;
	//�ش����ĳ���
	vector<string> WrongResult;
	//��txt�ļ��е������
	void LoadIdiomFromTxt();
	//����һ�������������ѡ���Ӧ�±�ĳ�����Ϊ���ε���Ŀ��ͬʱ�������������֮ǰ�Ѿ��ù���
	bool SetRandIndex();
	//����һ����Ŀ����ѡ����ԭ�����У����Ѷ������ȥ��Ӧ��������������ͨ�Ѷȣ���ȥ�����֣��á�__�����档
	void SpawnOneQuestion();
	bool CheckAnswer(CString as1);
	//�˶Իش��Ƿ���ȷ
	bool CheckAllAnswer(vector<CString> AllAnswer);
};

