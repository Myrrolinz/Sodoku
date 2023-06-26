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
	Generatehandler generator;//定义数独题目生成器
	SolverHandler board;
private:
	int isNum(const string& s);
	string FinalPath = "final.txt";//存储终局
	string AnsPath = "ans.txt";//存储求解答案
	string QuexPath = "question.txt";//存储数独题目
};

