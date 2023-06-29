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
	char** argv1, ** argv2, ** argv3, ** argv4, ** argv5, ** argv6, ** argv7;
	string path = "D:\\LessonProjects\\shudu\\";

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
	strcpy_s(argv6[4], 30, "20-55");

	strcpy_s(argv7[0], 30, "shudu.exe");
	strcpy_s(argv7[1], 30, "-n");
	strcpy_s(argv7[2], 30, "100");
	strcpy_s(argv7[3], 30, "-r");
	strcpy_s(argv7[4], 30, "20-55");
	strcpy_s(argv7[3], 30, "-u");

	InputHandler inputs;
	inputs.setAbsPath(path);


	// -c 100
	inputs.check(argc1, argv1);
	assert(inputs.GetNum() == 100, true);
	assert(inputs.GetType1() == 'c', true);

	// -s question.txt
	inputs.check(argc1, argv2);
	assert(inputs.GetType1() == 's', true);

	// -n 100
	inputs.check(argc1, argv3);
	bool abc = inputs.generator.generate(100, 18, 64, false);
	assert(inputs.GetType1() == 'n', true);
	assert(abc, true);

	// -n 100 -u
	inputs.check(argc2, argv4);
	assert(inputs.GetNum() == 10, true);
	assert(inputs.GetType1() == 'n', true);
	assert(inputs.GetType2() == 'u', true);
	bool a = inputs.generator.generate(inputs.GetNum(), 18, 64, true);
	assert(true, a);

	// -n 100 -r 20-55 -u
	inputs.check(argc4, argv7);
	assert(inputs.GetNum() == 100, true);
	assert(inputs.GetType1() == 'n', true);
	assert(inputs.GetType2() == 'u', true);
	assert(inputs.GetRange1() == 20, true);
	assert(inputs.GetRange2() == 55, true);

	//在这里多写几个指令，尽量占满所有的可运行指令

}

int main(int argc, char* argv[]) {
	InputHandler ih;
	cout << "请输入存储文件的绝对路径:" << endl;
	string abs;
	cin >> abs;
	// ih.setAbsPath(abs);
	// ih.check(argc, argv);
	UnitTest();
	return 0;
}
