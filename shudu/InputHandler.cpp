#include <iostream>
#include "InputHandler.h"
#include <fstream>
#include "progress.h"
#include <algorithm>
#include "SolveHandler.h"
using namespace std;

inline void output(fstream& f, int* line, int* offset) {
	for (int i = 0; i < 9; i++) {
		int start = offset[i];
		f << line[start];
		for (int j = start + 1; j < start + 9; j++) {
			f << " " << line[j % 9];
		}
		f << endl;
	}
	f << endl;
}

void InputHandler::check(int argc, char** argv) {
	/*只有一个参数:
	-c num:生成num个终盘
	-s game.txt:从game.txt读取若干数独游戏，并给出解答，存储到shudu.txt中
	-n num:生成num个数独游戏，存储到game.txt中
	-r 挖空：a-b
	*/
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		if (parameter1 == "-c") {//done
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
		else if (parameter1 == "-s") {
			fstream infile(parameter2, ios::in);
			fstream outfile("suduku.txt", ios::out);
			if (!infile.is_open()) {
				cout << "文件打开失败！" << endl;
				return;
			}
			cout << "正在求解，请稍候..." << endl;
			int i = 1;
			while (infile.peek() != EOF) {
				SolverHandler board;
				board.input(infile);
				int result = board.solve();
				if (result == 0) {
					board.output(outfile);
				}
				else {
					cout << "第" << i << "个数独无解！" << endl;
					outfile << "No solution" << endl << endl;
				}
			}
			infile.close();
			outfile.close();
		}
		else {
			cout << "输入有误！" << endl;
		}
	}
	else if(argc==5){
		string arg1= argv[1];
		string parm1 = argv[2];
		string arg2 = argv[3];
		string param2 = argv[4];
		if (arg1 == "-n") {
			int n = isNum(parm1);
			if (n <= 0 || n > 1000000) {
				cout << "生成数独题库数量不规范(0<n<1000000)！请重新输入生成数" << endl;
				return;
			}
			if (arg2 == "-r") {
				string begin, end;
				bool isBegin = true;
				//将范围"a-b"转为：a  b
				for (int i = 0; i < param2.length(); i++) {
					if (param2[i] == '-') {
						isBegin = false;
					}
					else {
						if (isBegin) {
							begin += param2[i];
						}
						else {
							end += param2[i];
						}
					}
				}
				if (begin.length() == 0 || end.length() == 0) {
					cout << "[-r]项参数不规范，应输入a-b形式的参数，请重新输入！" << endl;
					return;
				}
				int begin_num = isNum(begin);
				int end_num = isNum(end);
				if (begin_num <= 0 || end_num <= 0) {
					cout << "[-r]项参数不规范，应输入a-b形式的正整数，请重新输入！" << endl;
					return;
				}
				else {
					generator.generate(n, begin_num, end_num);
					cout << "已生成" + parm1 + "个数独游戏，挖空范围在["<<begin_num<<","<<end_num<<"]之间" << endl;
				}
			}
			else if (arg2 == "-m") {

			}
			else {
				cout << "输入有误！存在未定义的选项" << endl;
				return;
			}
		}
	}
	else if (argc == 6) {
		//首先需要确定-u的位置
		int upos = 1;
		bool isUnion = false;
		string arg1, param1, arg2, param2;
		for (int i =0; i < 6; i++) {
			if (argv[i] == "-u") {
				upos = i;
				isUnion = true;
				break;
			}
		}
		if (isUnion == false) {
			cout << "输入命令行格式错误，出现单数个参数但未出现[-u]，请重新输入！" << endl;
			return;
		}
		if (upos == 1) {
			arg1 = argv[2];
			param1 = argv[3];
			arg2 = argv[4];
			param1 = argv[5];
		}
		if (upos == 3) {
			arg1 = argv[1];
			param1 = argv[2];
			arg2 = argv[4];
			param1 = argv[5];
		}
		else if (upos == 5) {
			arg1 = argv[1];
			param1 = argv[2];
			arg2 = argv[3];
			param1 = argv[4];
		}
		else {
			cout << "输入命令行格式错误，请重新输入！" << endl;
			return;
		}
		if (arg1 == "-n" || arg2 == "-n") {
			if (arg1 == "-n") {
				int n = isNum(param1);
				if (n <= 0 || n > 1000000) {
					cout << "生成数独题库数量不规范(0<n<1000000)！请重新输入生成数" << endl;
					return;
				}
				if (arg2 == "-r") {
					string begin, end;
					bool isBegin = true;
					//将范围"a-b"转为：a  b
					for (int i = 0; i < param2.length(); i++) {
						if (param2[i] == '-') {
							isBegin = false;
						}
						else {
							if (isBegin) {
								begin += param2[i];
							}
							else {
								end += param2[i];
							}
						}
					}
					if (begin.length() == 0 || end.length() == 0) {
						cout << "[-r]项参数不规范，应输入a-b形式的参数，请重新输入！" << endl;
						return;
					}
					int begin_num = isNum(begin);
					int end_num = isNum(end);
					if (begin_num <= 0 || end_num <= 0) {
						cout << "[-r]项参数不规范，应输入a-b形式的正整数，请重新输入！" << endl;
						return;
					}
					else {
						generator.generate(n, begin_num, end_num, isUnion);
						cout << "已生成" + param1 + "个具有唯一解数独游戏，挖空范围在[" << begin_num << "," << end_num << "]之间" << endl;
					}
				}
				else if (arg2 == "-m") {

				}
				else {
					cout << "输入有误！存在未定义的选项" << endl;
					return;
				}
			}
			else {

			}
		}
		else {
			cout << "输入命令行格式错误，请重新输入！" << endl;
			return;
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
		return -1;
	for (size_t i = 0; i < size; i++) {
		int ascii = int(s[i]);
		if (ascii >= 48 && ascii <= 57)
			continue;
		else 
			return -1;
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

void InputHandler::getQues(int num, int begin_num, int end_num) {

}