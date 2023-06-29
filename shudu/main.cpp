// (C) Copyright 2023 Yunmei Guan, Jiaqi Shi
// Description：Sudoku Game
// Author：GYM, SJQ
// Date:2023-6
// Modify Record:
#include <iostream>
#include <string>
#include <assert.h>
#include "InputHandler.h"
//using std::cout;
//using std::endl;
using namespace std;

void UnitTest() {
	int argc1, argc2, argc3;
	char** argv1, ** argv2, ** argv3, ** argv4, ** argv5, ** argv6;
	string path = "D:\\LessonProjects\\shudu\\";

	argc1 = 3;
	argc2 = 4;
	argc3 = 5;
	argv1 = new char* [3];//c
	argv2 = new char* [3];//s
	argv3 = new char* [3];//n
	argv4 = new char* [4];//n u
	argv5 = new char* [5];//n m
	argv6 = new char* [5];//n r


	for (int i = 0; i < 3; i++)
	{
		argv1[i] = new char[30];
		argv2[i] = new char[30];
		argv3[i] = new char[30];

	}

	for (int i = 0; i < 4; i++)
	{
		argv4[i] = new char[30];

	}
	for (int i = 0; i < 5; i++)
	{
		argv5[i] = new char[30];
		argv6[i] = new char[30];
	}
	strcpy_s(argv1[0], 30, "shudu.exe");
	strcpy_s(argv1[1], 30, "-c");
	strcpy_s(argv1[2], 30, "100");

	strcpy_s(argv2[0], 30, "shudu.exe");
	strcpy_s(argv2[1], 30, "-s");
	strcpy_s(argv2[2], 30, "question.txt");

	strcpy_s(argv3[0], 30, "shudu.exe");
	strcpy_s(argv3[1], 30, "-n");
	strcpy_s(argv3[2], 30, "100");

	strcpy_s(argv4[0], 30, "shudu.exe");
	strcpy_s(argv4[1], 30, "-n");
	strcpy_s(argv4[2], 30, "10");
	strcpy_s(argv4[3], 30, "-u");

	strcpy_s(argv5[0], 30, "shudu.exe");
	strcpy_s(argv5[1], 30, "-n");
	strcpy_s(argv5[2], 30, "100");
	strcpy_s(argv5[3], 30, "-m");
	strcpy_s(argv5[4], 30, "3");

	strcpy_s(argv6[0], 30, "shudu.exe");
	strcpy_s(argv6[1], 30, "-n");
	strcpy_s(argv6[2], 30, "100");
	strcpy_s(argv6[3], 30, "-r");
	strcpy_s(argv6[4], 30, "20-30");

	InputHandler inputs;
	inputs.setAbsPath(path);
	inputs.check(argc1, argv1);
}

int main(int argc, char* argv[]) {
	InputHandler ih;
	cout << "请输入存储文件的绝对路径:" << endl;
	string abs;
	cin >> abs;
	//ih.setAbsPath(abs);
	//ih.check(argc, argv);
	UnitTest();
	return 0;
}
