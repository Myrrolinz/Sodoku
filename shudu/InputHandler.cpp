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
	/*ֻ��һ������:
	-c num:����num������
	-s game.txt:��game.txt��ȡ����������Ϸ����������𣬴洢��shudu.txt��
	-n num:����num��������Ϸ���洢��game.txt��
	-r �ڿգ�a-b
	*/
	generator.setAbsPath(absolatePath);
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		if (parameter1 == "-c") {//done
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
				cout << "������0<n<=1000000!" << endl;
			else {
				// FianlMaker fm;
				// fm.make(n);
				getFinal(n);
				cout << "������" << parameter2 << "����������" << endl;
			}
		}
		else if (parameter1 == "-s") {
			fstream infile(absolatePath+parameter2, ios::in);
			fstream outfile(absolatePath + AnsPath, ios::out);
			if (!infile.is_open()) {
				cout << "�ļ���ʧ��!" << endl;
				return;
			}
			cout << "������⣬���Ժ�..." << endl;
			int i = 1;
			while (infile.peek() != EOF) {
				board.input(infile);
				int result = board.solve();
				if (result == 0) {
					board.output(outfile);
				}
				else {
					cout << "��" << i << "�������޽�!" << endl;
					outfile << "No solution" << endl << endl;
				}
				i++;
				board.clean();
			}
			cout << "������!" << endl;
			infile.close();
			outfile.close();
		}
		else {
			cout << "��������!" << endl;
		}
	}
	else if (argc == 4) {
		string arg1 = argv[1];
		string arg2 = argv[2];
		string arg3 = argv[3];
		string parm1;
		if (arg2 == "-n" || arg1 == "-u") {
			parm1 = arg3;
		}
		else if (arg1 == "-n" || arg3 == "-u") {
			parm1 = arg2;
		}
		else {
			cout << "���������������������!" << endl;
			return;
		}
		int n = isNum(parm1);
		if (n <= 0 || n > 1000000) {
			cout << "������������������淶(0<n<1000000)!����������������" << endl;
			return;
		}
		generator.generate(n, 18, 64, true);
	}
	else if(argc==5){
		string arg1= argv[1];
		string parm1 = argv[2];
		string arg2 = argv[3];
		string param2 = argv[4];
		
		if (arg1 == "-n") {
			int n = isNum(parm1);
			if (n <= 0 || n > 1000000) {
				cout << "������������������淶(0<n<1000000)!����������������" << endl;
				return;
			}
			if (arg2 == "-r") {
				string begin, end;
				bool isBegin = true;
				//����Χ"a-b"תΪ��a  b
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
					cout << "[-r]��������淶��Ӧ����a-b��ʽ�Ĳ���������������!" << endl;
					return;
				}
				int begin_num = isNum(begin);
				int end_num = isNum(end);
				if (begin_num <= 0 || end_num <= 0|| begin_num > end_num) {
					cout << "[-r]��������淶��Ӧ����a-b��ʽ��������������������!" << endl;
					return;
				}
				else {
					generator.generate(n, begin_num, end_num,false);
					cout << "������" << parm1 << "��������Ϸ���ڿշ�Χ��["<<begin_num<<", "<<end_num<<"]֮��" << endl;
				}
			}
			else if (arg2 == "-m") {
				//ѡ���Ѷȵ�ʱ�򣬷�Ϊ3��
				/*��һ�����ڿ���5-18֮��(��˲���Ҫ��Ψһ��)
				  �ڶ������ڿ���18-32֮��
				  ���������ڿ���33-64֮��
				  */
				int level = isNum(param2);
				
				if (level == 1) {
					cout << "level:" << level << endl;
					generator.generate(n, 18, 32,false);
					cout << "生成结束！" << endl;
					return;
				}
				else if(level==2)
				{
					generator.generate(n, 32, 48,false);
					cout << "生成结束！" << endl;
					return;
				}
				else if (level == 3) {
					generator.generate(n, 48, 64,false);
					cout << "生成结束！" << endl;
					return;
				}
				else {
					cout << "������ѶȲ����Ϲ淶��ӦΪ1-3֮�������!" << endl;
					return;
				}
				
			}
			else {
				cout << "��������!����δ�����ѡ��" << endl;
				return;
			}
		}
	}
	else if (argc == 6) {
		//������Ҫȷ��-u��λ��
		int upos = 1;
		bool isUnion = false;
		string arg1, param1, arg2, param2;
		for (int i =0; i < 6; i++) {
			string p = argv[i];
			if (p == "-u") {
				upos = i;
				isUnion = true;
			}
		}
		if (!isUnion) {
			cout << "���������и�ʽ���󣬳��ֵ�����������δ����[-u]������������!" << endl;
			return;
		}
		if (upos == 1) {
			arg1 = argv[2];
			param1 = argv[3];
			arg2 = argv[4];
			param2 = argv[5];
		}
		else if (upos == 3) {
			arg1 = argv[1];
			param1 = argv[2];
			arg2 = argv[4];
			param2 = argv[5];
		}
		else if (upos == 5) {
			arg1 = argv[1];
			param1 = argv[2];
			arg2 = argv[3];
			param2 = argv[4];
		}
		else {
			cout << "���������и�ʽ��������������!" << endl;
			return;
		}
		if (arg1 == "-n" || arg2 == "-n") {
			if (arg2 == "-n") {//��������˳��
				string temp_argv = arg1;
				string temp_param = param1;
				arg1 = arg2;
				param1 = param2;
				arg2 = temp_argv;
				param2 = temp_param;
			}
			int n = isNum(param1);
			/*cout << "arg1" << arg1 << endl;
			cout << "param1:" << param1 << endl;
			cout << "arg2" << arg2 << endl;
			cout << "param2:" << param2 << endl;
			cout << n << endl;*/
			if (n <= 0 || n > 1000000) {
				cout << "������������������淶(0<n<1000000)!����������������" << endl;
				return;
			}
			if (arg2 == "-r") {
				string begin, end;
				bool isBegin = true;
				//����Χ"a-b"תΪ��a  b
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
					cout << "[-r]��������淶��Ӧ����a-b��ʽ�Ĳ���������������!" << endl;
					return;
				}
				int begin_num = isNum(begin);
				int end_num = isNum(end);
				if (begin_num <= 17 || end_num <= 0 || begin_num > end_num || begin_num>64) {
					cout << "����-r��淶���⣺����ԭ��1.��Χ��������2.�÷�Χ�޷�����Ψһ��(�뽫��Χ������18-64)" << endl;
					return;
				}
				else {
					generator.generate(n, begin_num, end_num, isUnion);
					cout << "������" << param1 << "������Ψһ��������Ϸ���ڿշ�Χ��[" << begin_num << "," << end_num << "]֮��" << endl;
				}
			}
			else if (arg2 == "-m") {
				//ѡ���Ѷȵ�ʱ�򣬷�Ϊ3��
				/*��һ�����ڿ���5-18֮��(��˲���Ҫ��Ψһ��)
				  �ڶ������ڿ���18-32֮��
				  ���������ڿ���33-64֮��
				  */
				int level = isNum(param2);

				if (level == 1) {
					generator.generate(n, 5, 17,true);
				}
				else if (level == 2)
				{
					generator.generate(n, 18, 32,true);
				}
				else if (level == 3) {
					generator.generate(n, 33, 64,true);
				}
				else {
					cout << "������ѶȲ����Ϲ淶��ӦΪ1-3֮�������!" << endl;
					return;
				}
			}
			else {
				cout << "��������!����δ�����ѡ��" << endl;
				return;
			}
		}
		else {
			cout << "���������и�ʽ��������������!" << endl;
			return;
		}
		
	}
	else {
		cout << "��������!" << endl;
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
	cout << "��ʼ����" << num << "����������!" << endl;

	//Initialize prgress bar
	milliseconds interval(1000);
	ProgressBar bar((unsigned int)num, interval);
	bar.show();

	//Open output file
	fstream outfile(absolatePath+FinalPath, ios::out);
	if (!outfile.is_open()) {
		cout << "�ļ���ʧ��!" << endl;
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
					cout << "�������!" << endl;
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

