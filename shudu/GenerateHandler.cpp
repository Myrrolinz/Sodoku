#include <iostream>
#include <fstream>
#include "GenerateHandler.h"
using namespace std;

void Generatehandler::generate(int num, int beginNum, int endNum, bool isUnion = false) {
	/*思路：从beginNum开始挖空，
	如果需要判断union：
	判断不成立后，重新迭代100次，
	超过100次则挖空数+1后重新生成
	直至endNum*/
	fstream infile(FinalPath, ios::in);
	fstream outfile(outputPath, ios::out);
	if (!outfile.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
	}
	cout << "---------------正在生成" << num << "个数独题目---------------" << endl;
	for (int i = 0; i < num; i++) {
		holenum = beginNum;
		for (int wakong = beginNum; wakong <= endNum; wakong++) {

		}
	}
	
}

void Generatehandler::holehole() {
	//先挖掉
}

void Generatehandler::input(fstream& f) {
	//获取一个终局，将其存入matrix数组
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			char val;
			f >> val;
			int num = val;
			if (val != '$') {
				val -= '0';
			}
			matrix[i][j]=
		}
	}
	// remove empty line
	f.get();
	f.get();
}

int Generatehandler::isNum(const string& s) {
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