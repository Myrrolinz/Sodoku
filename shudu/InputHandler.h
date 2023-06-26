#pragma once
#include <iostream>
#include <string>
#include "GenerateHandler.h"
using namespace std;

class InputHandler {
public:
	void check(int argc, char** argv);
	void getFinal(int num);
	void getQues(int num,int begin_num,int end_num);
	Generatehandler generator;//定义数独题目生成器
private:
	int isNum(const string& s);
};

