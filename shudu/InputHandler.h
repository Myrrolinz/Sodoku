#pragma once
#include <iostream>
#include <string>
#include "GenerateHandler.h"
#include "SolveHandler.h"
using namespace std;

class InputHandler {
public:
	void check(int argc, char** argv);
	void getFinal(int num);
	//���þ���·��
	void setAbsPath(string abs) {
		absolatePath = abs;
	}
	Generatehandler generator;//����������Ŀ������
	SolverHandler board;
	int GetNum();
	char GetType1();
	char GetType2();
	int GetRange1();
	int GetRange2();
	int GetLevel();
private:
	int isNum(const string& s);
	string absolatePath = "D:\\LessonProjects\\shudu\\shudu";
	string FinalPath = "final.txt";//�洢�վ�
	string AnsPath = "ans.txt";//�洢����
	string QuexPath = "question.txt";//�洢������Ŀ
	char type1 = 'y';
	char type2 = 'y';
	int num;
	int range1;
	int range2;
	int level;
};

