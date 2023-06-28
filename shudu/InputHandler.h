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
	//设置绝对路径
	void setAbsPath(string abs) {
		absolatePath = abs;
	}
	Generatehandler generator;//定义数独题目生成器
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
	string FinalPath = "final.txt";//存储终局
	string AnsPath = "ans.txt";//存储求解答案
	string QuexPath = "question.txt";//存储数独题目
	char type1 = 'y';
	char type2 = 'y';
	int num;
	int range1;
	int range2;
	int level;
};

