/*
** (C) Copyright 2023 Yunmei Guan, Jiaqi Shi
** Description：Sudoku Game
** Author：GYM, SJQ
** Date:2023-6
** Modify Record:
*/
#include <iostream>
#include <string>
#include "InputHandler.h"
using namespace std;

int main(int argc, char* argv[]) {
	InputHandler ih;
	cout << "请输入存储文件的绝对路径:" << endl;
	string abs;
	cin >> abs;
	ih.setAbsPath(abs);
	ih.check(argc, argv);
	return 0;
}