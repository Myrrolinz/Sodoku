#include <iostream>
#include "InputHandler.h"
#include "FinalMaker.cpp"
#include <fstream>
#include "progress.h"
using namespace std;


void InputHandler::check(int argc, char** argv) {
	/*只有一个参数:
	-c num:生成num个终盘
	-s game.txt:从game.txt读取若干数独游戏，并给出解答，存储到shudu.txt中
	-n num:生成num个数独游戏，存储到game.txt中
	*/
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		if (parameter1 == "-c") {
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
				cout << "不满足0<n<=1000000！" << endl;
			else {
				// FianlMaker fm;
				// fm.make(n);
				getFinal(n);
				cout << "已生成" + parameter2 + "个数独终盘" << endl;
			}
		}
		/*else if (parameter1 == "-s") {
			ifstream in(parameter2);
			if (!in.is_open()) {
				cout << parameter2 + "无法打开！" << endl;
				return;
			}
			char ch[81];
			char c;
			int count = 0;
			SudokuSolver ss;
			FILE* out = fopen("sudoku.txt", "wt");
			while (in.get(c)) {	//in >> c 会忽略空白回车符
				if (isdigit(c)) {
					ch[count++] = c;
				}
				if (count == 81) {
					count = 0;
					fputs(ss.solve(ch), out);
				}
			}
			in.close();
			if (count != 0) {
				char* str = "存在错误格式！";
				fputs(str, out);
				cout << str << endl;
			}
			else
				cout << "已解出" + parameter2 + "里的数独" << endl;
			fclose(out);
		}*/
		else {
			cout << "输入有误！" << endl;
		}
	}
	else {
		cout << "输入有误！" << endl;
	}
	return;
}

int InputHandler::isNum(const string& s) {
	size_t size = s.size();
	if (size > 7)
		return 0;
	for (size_t i = 0; i < size; i++) {
		int ascii = int(s[i]);
		if (ascii >= 48 && ascii <= 57)
			continue;
		else
			return 0;
	}
	return stoi(s);
}

void InputHandler::getFinal(int num) {
	cout << "开始生成" << num << "个数独终盘！" << endl;

	//Initialize prgress bar
	milliseconds interval(1000);
	ProgressBar bar((unsigned int)num, interval);
	bar.show();

	//Open output file
	fstream outfile("final.txt", ios::out);
	if (!outfile.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
	}

	int head[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int offset[9] = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };
	while (true) {
		//change the order of line 3-5, 6 arrangements
		for (int i = 0; i < 6; i++) {
			//change the order of line 6-8, 6 arrangements
			for (int j = 0; j < 6; j++) {
				output(outfile, head, offset);
				bar.update();
				if ((--num) <= 0) {
					outfile.close();
					bar.show();
					cout << "生成完成！" << endl;
					return;
				}
				next_permutation(offset + 6, offset + 9);
			}
			next_permutation(offset + 3, offset + 6);
		}
		next_permutation(head, head + 9);
		if (num % 100 == 0) {
			bar.show();
		}
	}
}