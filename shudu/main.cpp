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
	int argc1, argc2, argc3, argc4;
	char** argv1, ** argv2, ** argv3, ** argv4, ** argv5, ** argv6, ** argv7, ** argv8, ** argv9, ** argv10;
	string path = "D:\\LessonProjects\\shudu\\";
	InputHandler inputs;
	inputs.setAbsPath(path);
	argc1 = 3;
	argc2 = 4;
	argc3 = 5;
	argc4 = 6;
	argv1 = new char* [3];//c
	argv2 = new char* [3];//s
	argv3 = new char* [3];//n
	argv4 = new char* [4];//n u
	argv5 = new char* [5];//n m
	argv6 = new char* [5];//n r
	argv7 = new char* [6];//n r u
	argv8 = new char* [6];//n r u
	argv9 = new char* [6];//n r u
	argv10 = new char* [6];//n r u

	for (int i = 0; i < 3; i++) {
		argv1[i] = new char[30];
		argv2[i] = new char[30];
		argv3[i] = new char[30];
	}
	for (int i = 0; i < 4; i++) {
		argv4[i] = new char[30];

	}
	for (int i = 0; i < 5; i++) {
		argv5[i] = new char[30];
		argv6[i] = new char[30];
	}
	for (int i = 0; i < 6; i++) {
		argv7[i] = new char[30];
		argv8[i] = new char[30];
		argv9[i] = new char[30];
		argv10[i] = new char[30];
	}

	strcpy_s(argv1[0], 30, "shudu.exe");
	strcpy_s(argv1[1], 30, "-c");
	strcpy_s(argv1[2], 30, "100");
	// -c 100
	inputs.check(argc1, argv1);

	strcpy_s(argv2[0], 30, "shudu.exe");
	strcpy_s(argv2[1], 30, "-s");
	strcpy_s(argv2[2], 30, "question.txt");
	// -s question.txt
	inputs.check(argc1, argv2);

	strcpy_s(argv3[0], 30, "shudu.exe");
	strcpy_s(argv3[1], 30, "-n");
	strcpy_s(argv3[2], 30, "100");
	// -n 100
	inputs.check(argc1, argv3);
	strcpy_s(argv3[2], 30, "100");
	inputs.check(argc1, argv3);

	strcpy_s(argv4[0], 30, "shudu.exe");
	strcpy_s(argv4[1], 30, "-n");
	strcpy_s(argv4[2], 30, "10");
	strcpy_s(argv4[3], 30, "-u");
	// -n 100 -u
	inputs.check(argc2, argv4);
	strcpy_s(argv4[2], 30, "0");
	inputs.check(argc2, argv4);
	//-u -n 100
	strcpy_s(argv4[1], 30, "-u");
	strcpy_s(argv4[2], 30, "-n");
	strcpy_s(argv4[3], 30, "10");


	strcpy_s(argv5[0], 30, "shudu.exe");
	strcpy_s(argv5[1], 30, "-n");
	strcpy_s(argv5[2], 30, "100");
	strcpy_s(argv5[3], 30, "-m");
	strcpy_s(argv5[4], 30, "3");
	//-n 100 -m 3
	inputs.check(argc3, argv5);
	//-n 100 -m 1
	strcpy_s(argv5[4], 30, "1");
	inputs.check(argc3, argv5);
	//-n 100 -m 2
	strcpy_s(argv5[4], 30, "2");
	inputs.check(argc3, argv5);
	//-n 100 -m 6
	strcpy_s(argv5[4], 30, "6");
	inputs.check(argc3, argv5);
	//-n 0 -m 2
	strcpy_s(argv5[2], 30, "0");
	inputs.check(argc3, argv5);

	strcpy_s(argv6[0], 30, "shudu.exe");
	strcpy_s(argv6[1], 30, "-n");
	strcpy_s(argv6[2], 30, "100");
	strcpy_s(argv6[3], 30, "-r");
	strcpy_s(argv6[4], 30, "20-55");
	//-n 100 -r 20-50
	inputs.check(argc3, argv6);
	//-n 0
	strcpy_s(argv6[2], 30, "10000000");
	inputs.check(argc3, argv6);
	//-r dd
	strcpy_s(argv6[4], 30, "20");
	inputs.check(argc3, argv6);

	strcpy_s(argv7[0], 30, "shudu.exe");
	strcpy_s(argv7[1], 30, "-n");
	strcpy_s(argv7[2], 30, "10");
	strcpy_s(argv7[3], 30, "-r");
	strcpy_s(argv7[4], 30, "20-55");
	strcpy_s(argv7[5], 30, "-u");
	// -n 100 -r 20-55 -u
	inputs.check(argc4, argv7);
	// -n 100 -r 1-6 -u
	strcpy_s(argv7[4], 30, "1-6");
	inputs.check(argc4, argv7);
	// -n 100 -r 1 -u
	strcpy_s(argv7[4], 30, "1");
	inputs.check(argc4, argv7);

	strcpy_s(argv8[0], 30, "shudu.exe");
	strcpy_s(argv8[1], 30, "-u");
	strcpy_s(argv8[2], 30, "-r");
	strcpy_s(argv8[3], 30, "20-55");
	strcpy_s(argv8[4], 30, "-n");
	strcpy_s(argv8[5], 30, "10");
	// -u  -r 20-55 -n 10
	inputs.check(argc4, argv8);
	strcpy_s(argv8[3], 30, "0-5");
	// -u  -r 0-5 -n 10
	inputs.check(argc4, argv8);
	strcpy_s(argv8[3], 30, "11");
	// -u  -r 11 -n 10
	inputs.check(argc4, argv8);

	strcpy_s(argv9[0], 30, "shudu.exe");
	strcpy_s(argv9[1], 30, "-u");
	strcpy_s(argv9[2], 30, "-m");
	strcpy_s(argv9[3], 30, "1");
	strcpy_s(argv9[4], 30, "-n");
	strcpy_s(argv9[5], 30, "10");
	// -u -m 1 -n 10
	inputs.check(argc4, argv9);
	strcpy_s(argv9[3], 30, "2");
	// -u -m 2 -n 10
	inputs.check(argc4, argv9);
	strcpy_s(argv9[3], 30, "3");
	// -u -m 3 -n 10
	inputs.check(argc4, argv9);
	strcpy_s(argv9[3], 30, "6");
	// -u -m 6 -n 10
	inputs.check(argc4, argv9);

	strcpy_s(argv9[0], 30, "shudu.exe");
	strcpy_s(argv9[1], 30, "-m");
	strcpy_s(argv9[2], 30, "1");
	strcpy_s(argv9[3], 30, "-u");
	strcpy_s(argv9[4], 30, "-n");
	strcpy_s(argv9[5], 30, "10");
	// -m 1 -u -n 10
	inputs.check(argc4, argv9);


	strcpy_s(argv10[0], 30, "shudu.exe");
	strcpy_s(argv10[2], 30, "-m");
	strcpy_s(argv10[1], 30, "-u");
	strcpy_s(argv10[3], 30, "1");
	strcpy_s(argv10[4], 30, "-n");
	strcpy_s(argv10[5], 30, "10");
	// -m -u 1 -n 10
	inputs.check(argc4, argv10);
}

int main(int argc, char* argv[]) {
	InputHandler ih;
	cout << "请输入存储文件的绝对路径:" << endl;
	string abs;
	cin >> abs;
	ih.setAbsPath(abs);
	ih.check(argc, argv);
	// UnitTest();
	return 0;
}
