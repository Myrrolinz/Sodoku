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
private:
	int isNum(const string& s);
	string absolatePath = "D:\\LessonProjects\\shudu\\shudu";
	string FinalPath = "final.txt";//�洢�վ�
	string AnsPath = "ans.txt";//�洢����
	string QuexPath = "question.txt";//�洢������Ŀ
};

